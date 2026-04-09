#include "CallNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> CallNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitCallNode(*this);
}

