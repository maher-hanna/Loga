#include "GroupingNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool> GroupingNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitGroupingNode(*this);
}