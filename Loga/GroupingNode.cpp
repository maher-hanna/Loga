#include "GroupingNode.h"
#include "Value.h"

Value GroupingNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitGroupingNode(*this);
}