#include "LiteralNode.h"
#include "LogaCallable.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> LiteralNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLiteralNode(*this);
}
