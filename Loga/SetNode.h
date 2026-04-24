#pragma once
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Value.h"
#include "Token.h"

class SetNode : public Expression
{
public:
	SetNode() :object(nullptr), name(Token()), value(nullptr) {}
	SetNode(Expression* node,Token name,Expression * value) :object(node), name(name), value(value) {}
		
	Expression *object;
	Token name;
	Expression* value;

	Value accept(ExpressionVisitor& visitor);


private:

};

