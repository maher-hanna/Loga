#pragma once

#include <variant>
#include <vector>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Token.h"
#include "Value.h"


class CallNode : public Expression
{
public:
	CallNode() :callee(nullptr), paren(), arguments() {}
	CallNode(Expression* left, Token paren, std::vector<Expression*> arguments)
    : callee(left), paren(paren), arguments(arguments) {}
	Expression* callee;
	Token paren;
	std::vector<Expression*> arguments;
	Value accept(ExpressionVisitor& visitor) override;

};

