#pragma once
#include <string>
#include <variant>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Token.h"
#include "LogaCallable.h"

class VariableNode : public Expression
{
public:
	VariableNode() :value() {}
	VariableNode(Token name) :value(),name(name) {}
	VariableNode(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value) :value(value) {}
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> accept(ExpressionVisitor& visitor) override;

	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value;
	Token name;

private:

};

