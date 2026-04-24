#include "UnaryNode.h"
#include "Value.h"

Value UnaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitUnaryNode(*this);
}