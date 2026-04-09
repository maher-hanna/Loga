#include "BinaryNode.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> BinaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitBinaryNode(*this);
}

