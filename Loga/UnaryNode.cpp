#include "UnaryNode.h"

std::string UnaryNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitUnaryNode(*this);
}