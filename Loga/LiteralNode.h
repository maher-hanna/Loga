#pragma once
#include <string>
#include "ExpressionNode.h"
#include "ExpressionVisitor.h"

class LiteralNode : public ExpressionNode
{
public:
	LiteralNode() :value("") {}
	LiteralNode(std::string value) :value(value) {}
	std::string value;
	std::string accept(ExpressionVisitor& visitor) override;


private:

};

