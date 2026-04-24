#pragma once

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Value.h"

class LiteralNode : public Expression
{
public:
	LiteralNode() :value() {}
	LiteralNode(Value value) :value(value) {}
	Value value;
	Value accept(ExpressionVisitor& visitor) override;


private:

};

