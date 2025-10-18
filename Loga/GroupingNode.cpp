#include "GroupingNode.h"

std::string GroupingNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitGroupingNode(*this);
}