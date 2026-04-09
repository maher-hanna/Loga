#pragma once
#include <string>
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"
#include "LogaCallable.h"


class UnaryNode : public Expression
{
public:
	UnaryNode() :unaryOperator(),right(nullptr){}
	UnaryNode(Token unaryOperator,Expression* right) :unaryOperator(unaryOperator),right(right){}
	Token unaryOperator;
	Expression* right;
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> accept(ExpressionVisitor& visitor);


};

