#pragma once
#include <string>
#include <variant>
#include "ExpressionNode.h"
#include "ExpressionVisitor.h"

class LiteralNode : public ExpressionNode
{
public:
	LiteralNode() :value() {}
	LiteralNode(std::variant<double, int, std::string, std::nullptr_t, bool> value) :value(value) {}
	std::variant<double, int, std::string, std::nullptr_t, bool> value;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor) override;


private:

};

