#pragma once
#include <string>
#include <variant>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Token.h"
#include "Value.h"

class VariableNode : public Expression
{
public:
	VariableNode() :value() {}
	VariableNode(Token name) :value(),name(name) {}
	VariableNode(Value value) :value(value) {}
	Value accept(ExpressionVisitor& visitor) override;

	Value value;
	Token name;

private:

};

