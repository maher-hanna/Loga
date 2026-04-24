#include "AssignNode.h"
#include "Value.h"


Value AssignNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitAssignNode(*this);
}

