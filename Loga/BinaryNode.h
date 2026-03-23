#pragma once
#include "Expression.h"
#include "Token.h"
#include <variant>


class BinaryNode : public Expression
{
public:
	BinaryNode() :left(nullptr), binaryOperator(), right(nullptr) {}
	BinaryNode(Expression* left, Token binaryOperator, Expression* right) :left(left), binaryOperator(binaryOperator), right(right) {};
	Expression* left;
	Token binaryOperator;
	Expression* right;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor) override;

};

