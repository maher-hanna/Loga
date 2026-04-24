#include "CallNode.h"
#include "Value.h"

Value CallNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitCallNode(*this);
}

