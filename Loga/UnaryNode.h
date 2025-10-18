#pragma once
#include <string>
#include "ExpressionNode.h"
#include "Token.h"
#include "ExpressionVisitor.h"


class UnaryNode : public ExpressionNode
{
public:
	UnaryNode() :unaryOperator(),right(nullptr){}
	UnaryNode(Token unaryOperator,ExpressionNode* right) :unaryOperator(unaryOperator),right(right){}
	Token unaryOperator;
	ExpressionNode* right;
	std::string accept(ExpressionVisitor& visitor);


};

