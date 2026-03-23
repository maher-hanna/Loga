#pragma once
#include <string>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Token.h"

class GroupingNode : public Expression
{
public:
	GroupingNode() :expression(nullptr) {}
	GroupingNode(Expression* node) :expression(node) {}
	Expression *expression;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor);


private:

};

