#pragma once
#include "Statement.h"
#include "Expression.h"

class ExpressionStatement : public Statement
{
public:
	ExpressionStatement(Expression* expr) :expression(expr) {}
	void accept(StatementVisitor& visitor) override;

	Expression* expression;
	

};

