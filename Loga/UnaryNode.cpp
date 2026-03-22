#include "UnaryNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool> UnaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitUnaryNode(*this);
}