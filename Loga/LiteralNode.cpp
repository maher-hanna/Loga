#include "LiteralNode.h"

std::string LiteralNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLiteralNode(*this);
}
