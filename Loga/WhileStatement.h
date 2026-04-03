#pragma once
#include "Statement.h"
#include "Expression.h"

class WhileStatement : public Statement
{
public:
	WhileStatement(Expression* condition) :condition(condition),body(nullptr) {}
	WhileStatement(Expression* condition, Statement* body) :condition(condition), body(body) {}
	void accept(StatementVisitor& visitor) override;

	Expression* condition;
	Statement* body;

};

