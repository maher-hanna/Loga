#include "BinaryNode.h"

std::string BinaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitBinaryNode(*this);
}

