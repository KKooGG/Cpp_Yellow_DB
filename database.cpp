#include "database.h"

Database::Database(){}

void Database::Add(Date date, string eventStr)
{
    if(find(dbDateToString[date].begin(), dbDateToString[date].end(), eventStr) == dbDateToString[date].end())
        dbDateToString[date].push_back(eventStr);
    dbDateToSetString[date].insert(eventStr);
}

void Database::Print(ostream& out)
{
    for(const auto& now : dbDateToString)
    {
        for (const auto& e : now.second)
        {
            out << now.first << ' '
                << e << endl;
        }
    }
}

vector<string> Database::FindIf(function<bool(const Date& date,
    const string& e)>fcnPrt)
{
    vector<string> countStr;
    for(const auto& now : dbDateToString)
    {
        for (const auto& e : now.second)
        {
            if (fcnPrt(now.first, e))
            {
                stringstream ss;
                ss << now.first << ' '
                    << e;
                countStr.push_back(ss.str());
            }
        }
    }
    return countStr;
}

string Database::Last(const Date& date)
{
    auto range = dbDateToString.upper_bound(date);
    if (range == dbDateToString.begin())
    {
        throw invalid_argument("Too old");
    }
    --range;
    stringstream ss;
    ss << range->first << ' ' << *(--range->second.end());
    return ss.str();
}

int Database::RemoveIf(function<bool
        (const Date& date, const string& e)>fcnPrt)
{
    vector<Date> forDel;
    int count = 0;
    for (auto now = dbDateToString.begin(); now != dbDateToString.end(); ++now)
    {
        for (vector<string>::const_iterator it = now->second.begin(); it != now->second.end(); ) {
            if (fcnPrt(now->first, *it)) {
                it = now->second.erase(it);
                ++count;
            }
            else {
                ++it;
            }
        }
        if (now->second.empty())
        {
            forDel.push_back(now->first);
        }
    }

    for (const auto& now : forDel)
    {
        dbDateToString.erase(now);
    }
    
    return count;
}