#pragma once

#include <variant>
#include "LogaCallable.h"
#include "Expression.h"
#include "Token.h"


class AssignNode : public Expression
{
public:
	AssignNode() : name(), value(nullptr) {}
	AssignNode(Token name, Expression* value) : name(name),value(value){};
	Token name;
	Expression* value;
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> accept(ExpressionVisitor& visitor) override;

};

