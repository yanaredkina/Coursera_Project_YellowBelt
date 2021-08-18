#include "node.h"

using namespace std;

Node::Node(const string& type) : NodeType(type){
}

EmptyNode::EmptyNode() : Node("EmptyNode") {
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : Node("DateComparisonNode"), cmp(cmp), queryDate(date) {
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    if (cmp == Comparison::Less) {
        return date < queryDate;
    } else if (cmp == Comparison::LessOrEqual) {
        return date <= queryDate;
    } else if (cmp == Comparison::Greater) {
        return date > queryDate;
    } else if (cmp == Comparison::GreaterOrEqual) {
        return date >= queryDate;
    } else if (cmp == Comparison::Equal) {
        return date == queryDate;
    } else if (cmp == Comparison::NotEqual) {
        return date != queryDate;
    } else {
        throw runtime_error("Error in Evaluate Function");
    }
}

// bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
//     if (cmp == Comparison::Less) {
//         return dateComparator(date, queryDate, "<");
//     } else if (cmp == Comparison::LessOrEqual) {
//         return dateComparator(date, queryDate, "<=");
//     } else if (cmp == Comparison::Greater) {
//         return dateComparator(date, queryDate, ">");
//     } else if (cmp == Comparison::GreaterOrEqual) {
//         return dateComparator(date, queryDate, ">=");
//     } else if (cmp == Comparison::Equal) {
//         return dateComparator(date, queryDate, "==");
//     } else if (cmp == Comparison::NotEqual) {
//         return dateComparator(date, queryDate, "!=");
//     } else {
//         throw runtime_error("Error in Evaluate Function");
//     }
// }


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) : Node("EventComparisonNode"), cmp(cmp), queryEvent(event) {
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    if (cmp == Comparison::Less) {
        return event < queryEvent;
    } else if (cmp == Comparison::LessOrEqual) {
        return event <= queryEvent;
    } else if (cmp == Comparison::Greater) {
        return event > queryEvent;
    } else if (cmp == Comparison::GreaterOrEqual) {
        return event >= queryEvent;
    } else if (cmp == Comparison::Equal) {
        return event == queryEvent;
    } else if (cmp == Comparison::NotEqual) {
        return event != queryEvent;
    } else {
        throw runtime_error("Error in Evaluate Function");
    }
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node> lhs, const shared_ptr<Node> rhs) : 
    Node("LogicalOperationNode"), op(op), lhs(lhs), rhs(rhs) {
    }
    
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    if (op == LogicalOperation::And) {
        return lhs->Evaluate(date, event) && rhs->Evaluate(date, event);
    } else if (op == LogicalOperation::Or) {
        return lhs->Evaluate(date, event) || rhs->Evaluate(date, event);
    } else {
        throw runtime_error("Error in Evaluate Function");
    }
}