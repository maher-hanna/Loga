#pragma once
#include "Expression.h"
#include "Token.h"
#include <variant>


class LogicalNode : public Expression
{
public:
	LogicalNode() :left(nullptr), logicalOperator(), right(nullptr) {}
	LogicalNode(Expression* left, Token logicalOperator, Expression* right) :left(left), logicalOperator(logicalOperator), right(right) {};
	Expression* left;
	Token logicalOperator;
	Expression* right;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor) override;

};

