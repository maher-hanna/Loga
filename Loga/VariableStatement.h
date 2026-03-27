#pragma once
#include "Statement.h"
#include "Expression.h"
#include "Token.h"

class VariableStatement : public Statement
{
public:
	VariableStatement(Expression* expr) :expression(expr) {}
	VariableStatement(Token name,Expression* expr) :name(name),expression(expr) {}
	void accept(StatementVisitor& visitor) override;

	Expression* expression;
	Token name;
	

};

