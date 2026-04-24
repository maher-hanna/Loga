#pragma once
#include <string>
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"
#include "Value.h"


class UnaryNode : public Expression
{
public:
	UnaryNode() :unaryOperator(),right(nullptr){}
	UnaryNode(Token unaryOperator,Expression* right) :unaryOperator(unaryOperator),right(right){}
	Token unaryOperator;
	Expression* right;
	Value accept(ExpressionVisitor& visitor);


};

