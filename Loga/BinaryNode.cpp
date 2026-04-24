#include "BinaryNode.h"
#include "Value.h"


Value BinaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitBinaryNode(*this);
}

