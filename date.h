#pragma once
#include <chrono>
#include <string>
#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;
class Date
{
public:
    Date(int year, int month, int day);

    time_t AsTimestamp() const;
    friend ostream& operator<<(ostream& out, const Date& d);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);

private:
    const int year_;
    const int month_;
    const int day_;
};

Date ParseDate(std::istream& in);