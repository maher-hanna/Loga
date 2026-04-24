#pragma once
#include <variant>
#include "Expression.h"
#include "Token.h"
#include "Value.h"


class BinaryNode : public Expression
{
public:
	BinaryNode() :left(nullptr), binaryOperator(), right(nullptr) {}
	BinaryNode(Expression* left, Token binaryOperator, Expression* right) :left(left), binaryOperator(binaryOperator), right(right) {};
	Expression* left;
	Token binaryOperator;
	Expression* right;
	Value accept(ExpressionVisitor& visitor) override;

};

