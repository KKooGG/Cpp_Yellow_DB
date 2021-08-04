#include "node.h"
using namespace std;

bool EmptyNode::Evaluate(const Date & date, const string & str)
{
    return true;
}

bool DateComparisonNode::Evaluate(const Date & date,
    const string & str)
{
    bool result = false;
    switch (this->cmp_)
    {
        case Comparison::Equal :
        {
            result = (date_ == date);
            break;
        }
        case Comparison::NotEqual :
        {
            result = (!(date_ == date));
            break;
        }
        case Comparison::GreaterOrEqual :
        {
            result+= (date_ == date);
        }
        case Comparison::Greater :
        {
            result += (date_ < date);
            break;
        }
        case Comparison::LessOrEqual :
        {
            result = (date_ == date);
        }
        case Comparison::Less :
        {
            result += (date_ > date);
            break;
        }
    }
    return result;
}

bool EventComparisonNode::Evaluate(const Date & date,
                    const string & str)
{
    bool result = false;
    switch (this->cmp_)
    {
    case Comparison::Equal :
    {
        result = value_ == str;
        break;
    }
    case Comparison::NotEqual :
    {
        result = !(value_ == str);
        break;
    }
    case Comparison::GreaterOrEqual :
    {
        result = value_ == str;
    }
    case Comparison::Greater :
    {
        result += value_ < str;
        break;
    }
    case Comparison::LessOrEqual :
    {
        result = value_ == str;
    }
    case Comparison::Less :
    {
        result += value_ > str;
        break;
    }
    }
    return result;
}

bool LogicalOperationNode::Evaluate(const Date & date,
                                    const string & str)
{
    bool result = false;
    if (this->lo_ == LogicalOperation::And)
    {
        result = this->left_->Evaluate(date, str) &&
                 this->right_->Evaluate(date, str);
    }
    else if (this->lo_ == LogicalOperation::Or)
    {
        result = this->left_->Evaluate(date, str) ||
            this->right_->Evaluate(date, str);
    }
    return result;
}
