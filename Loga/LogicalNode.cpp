#include "LogicalNode.h"
#include "LogaCallable.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> LogicalNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLogicalNode(*this);
}

