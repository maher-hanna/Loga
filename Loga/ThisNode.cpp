#include "ThisNode.h"
#include "Value.h"

Value ThisNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitThisNode(*this);
}