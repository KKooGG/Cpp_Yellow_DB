#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <algorithm>
#include "date.h"
#include "node.h"
using namespace std;
class Database
{
    map<Date, vector<string>> dbDateToString;
    map<Date, set<string>> dbDateToSetString;
public:
    Database();

    void Add(Date date, string eventStr);
    void Print(ostream& out);
    int RemoveIf(function<bool(const Date& date,
        const string& e)>fcnPrt);
    vector<string> FindIf(function<bool(const Date& date,
        const string& e)>fcnPrt);
    string Last(const Date& date);
};