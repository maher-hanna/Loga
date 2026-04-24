#pragma once
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Value.h"
#include "Token.h"

class GetNode : public Expression
{
public:
	GetNode() :object(nullptr) {}
	GetNode(Expression* node,Token name) :object(node), name(name) {}
		
	Expression *object;
	Token name;
	Value accept(ExpressionVisitor& visitor);


private:

};

