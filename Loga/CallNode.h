#pragma once

#include <variant>
#include <vector>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Token.h"
#include "LogaCallable.h"


class CallNode : public Expression
{
public:
	CallNode() :callee(nullptr), paren(), arguments() {}
	CallNode(Expression* left, Token paren, std::vector<Expression*> arguments)
    : callee(left), paren(paren), arguments(arguments) {}
	Expression* callee;
	Token paren;
	std::vector<Expression*> arguments;
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> accept(ExpressionVisitor& visitor) override;

};

