#include "date.h"
using namespace std;
Date::Date(int year, int month, int day) :
    year_(year), month_(month), day_(day) {}

time_t Date::AsTimestamp() const {
    tm t;
    t.tm_mday = day_;
    t.tm_mon = month_ - 1;
    t.tm_year = year_ - 1900;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_isdst = 0;
    return mktime(&t);
}

Date ParseDate(istream& in)
{
    int year, month, day;
    char ch1, ch2;
    in >> year >> ch1 >> month >> ch2 >> day;
    if (in.fail() || ch1 != '-' || ch1 != ch2)
    {
        throw logic_error("Date format error");
    }
    return { year, month, day };
}

ostream& operator<<(ostream& out, const Date& d)
{
    out << setw(4) << setfill('0') << d.year_ << '-';
    out << setw(2) << setfill('0') << d.month_ << '-';
    out << setw(2) << setfill('0') << d.day_;
    return out;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return lhs.AsTimestamp() < rhs.AsTimestamp();
}
bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.AsTimestamp() == rhs.AsTimestamp();
}
bool operator>(const Date& lhs, const Date& rhs)
{
    return lhs.AsTimestamp() > rhs.AsTimestamp();
}