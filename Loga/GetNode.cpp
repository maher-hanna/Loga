#include "GetNode.h"
#include "Value.h"

Value GetNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitGetNode(*this);
}