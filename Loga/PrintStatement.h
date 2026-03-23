#pragma once
#include "Statement.h"
#include "Expression.h"

class PrintStatement : public Statement
{
public:
	PrintStatement(Expression* expr) :expression(expr) {}
	void accept(StatementVisitor& visitor) override;
	Expression* expression;

};

