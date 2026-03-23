#pragma once
#include <string>
#include <variant>
#include "Expression.h"
#include "ExpressionVisitor.h"

class LiteralNode : public Expression
{
public:
	LiteralNode() :value() {}
	LiteralNode(std::variant<double, int, std::string, std::nullptr_t, bool> value) :value(value) {}
	std::variant<double, int, std::string, std::nullptr_t, bool> value;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor) override;


private:

};

