#pragma once
#include <string>
#include <memory>
#include "date.h"
using namespace std;
enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation
{
    Or,
    And,
};

class Node
{
public:
    virtual bool Evaluate ( const Date& date,
                            const string& str ) = 0;
};

class LogicalOperationNode : public Node
{
public:
    template<typename T, typename U>
    LogicalOperationNode(LogicalOperation lo,
        T prev,
        U next)
        : lo_(lo), left_(prev), right_(next) {}
    template<typename T>
    LogicalOperationNode(LogicalOperation lo,
        T prev,
        T next)
        : lo_(lo), left_(prev), right_(next) {}

    bool Evaluate(const Date& date,
        const string& str) override;

private:
    const LogicalOperation lo_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(const Comparison &cmp, const string &value)
        : cmp_(cmp), value_(value) {}

    bool Evaluate(const Date& date,
        const string& str) override;
private:
    const Comparison cmp_;
    const string value_;
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date)
        : cmp_(cmp), date_(date) {}
    bool Evaluate(const Date& date,
        const string& str) override;
private:
    const Comparison cmp_;
    const Date date_;
};

class EmptyNode : public Node
{
public:
    bool Evaluate(const Date& date,
        const string& str) override;

};