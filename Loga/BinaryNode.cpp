#include "BinaryNode.h"
#include <variant>

std::variant<double, int, std::string, std::nullptr_t, bool> BinaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitBinaryNode(*this);
}

