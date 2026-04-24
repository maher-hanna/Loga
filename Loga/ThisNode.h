#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"
#include "Value.h"


class ThisNode : public Expression
{
public:
	ThisNode() :keyword(){}
	ThisNode(Token keyword) :keyword(keyword){}
	ThisNode(Token keyword,Expression* right) :keyword(keyword){}
	Token keyword;
	Value accept(ExpressionVisitor& visitor);


};

