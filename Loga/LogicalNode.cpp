#include "LogicalNode.h"
#include "Value.h"

Value LogicalNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLogicalNode(*this);
}

