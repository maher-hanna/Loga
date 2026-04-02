#pragma once
#include "Statement.h"
#include "Expression.h"

class IfStatement : public Statement
{
public:
	IfStatement(Expression* condition, Statement* thenBranch, Statement* elseBranch) :condition(condition),
		thenBranch(thenBranch), elseBranch(elseBranch) {
	}
	void accept(StatementVisitor& visitor) override;

	Expression* condition;
	Statement* thenBranch;
	Statement* elseBranch;


};

