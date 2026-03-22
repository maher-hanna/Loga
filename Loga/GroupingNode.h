#pragma once
#include <string>
#include "ExpressionNode.h"
#include "ExpressionVisitor.h"
#include "Token.h"

class GroupingNode : public ExpressionNode
{
public:
	GroupingNode() :expression(nullptr) {}
	GroupingNode(ExpressionNode* node) :expression(node) {}
	ExpressionNode *expression;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor);


private:

};

