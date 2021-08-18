#pragma once
#include "date.h"

#include <string>
#include <memory>

using namespace std;

enum class LogicalOperation {
    And,
    Or,
};

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

class Node {
public:
    const string NodeType;
   
    Node(const string& type);
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& event) const;
};

class DateComparisonNode : public Node {
private:
    const Comparison cmp;
    const Date queryDate;
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) const;
};

class EventComparisonNode : public Node {
private:
    const Comparison cmp;
    const string queryEvent;
public:
    EventComparisonNode(const Comparison& cmp, const string& event);
    bool Evaluate(const Date& date, const string& event) const;
};

class LogicalOperationNode : public Node {
private:
    const LogicalOperation op;
    const shared_ptr<Node> lhs;
    const shared_ptr<Node> rhs;
public:
    LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node> lhs, const shared_ptr<Node> rhs);       
    bool Evaluate(const Date& date, const string& event) const;
};