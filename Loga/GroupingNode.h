#pragma once
#include <string>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Value.h"

class GroupingNode : public Expression
{
public:
	GroupingNode() :expression(nullptr) {}
	GroupingNode(Expression* node) :expression(node) {}
	Expression *expression;
	Value accept(ExpressionVisitor& visitor);


private:

};

