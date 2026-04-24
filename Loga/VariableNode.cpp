#include "VariableNode.h"
#include "Value.h"

Value VariableNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitVariableNode(*this);
}
