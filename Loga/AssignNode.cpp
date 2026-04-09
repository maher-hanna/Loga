#include "AssignNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AssignNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitAssignNode(*this);
}

