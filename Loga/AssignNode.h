#pragma once

#include <variant>
#include "LogaCallable.h"
#include "Expression.h"
#include "Value.h"
#include "Token.h"


class AssignNode : public Expression
{
public:
	AssignNode() : name(), value(nullptr) {}
	AssignNode(Token name, Expression* value) : name(name),value(value){};
	Token name;
	Expression* value;
	Value accept(ExpressionVisitor& visitor) override;

};

