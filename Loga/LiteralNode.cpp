#include "LiteralNode.h"
#include "Value.h"

Value LiteralNode::accept(ExpressionVisitor& visitor)
{
	return visitor.visitLiteralNode(*this);
}
