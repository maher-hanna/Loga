#include "LogicalNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool> LogicalNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLogicalNode(*this);
}

