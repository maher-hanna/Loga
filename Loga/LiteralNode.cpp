#include "LiteralNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool> LiteralNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLiteralNode(*this);
}
