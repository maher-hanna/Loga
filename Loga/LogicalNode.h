#pragma once
#include <variant>
#include "Expression.h"
#include "Token.h"
#include "LogaCallable.h"
#include "Value.h"


class LogicalNode : public Expression
{
public:
	LogicalNode() :left(nullptr), logicalOperator(), right(nullptr) {}
	LogicalNode(Expression* left, Token logicalOperator, Expression* right) :left(left), logicalOperator(logicalOperator), right(right) {};
	Expression* left;
	Token logicalOperator;
	Expression* right;
	Value accept(ExpressionVisitor& visitor) override;

};

