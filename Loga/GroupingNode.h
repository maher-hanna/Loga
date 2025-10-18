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
	std::string accept(ExpressionVisitor& visitor);


private:

};

