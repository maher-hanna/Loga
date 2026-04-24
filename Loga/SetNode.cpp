#include "SetNode.h"
#include "Value.h"

Value SetNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitSetNode(*this);
}