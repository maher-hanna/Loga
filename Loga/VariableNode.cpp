#include "VariableNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> VariableNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitVariableNode(*this);
}
