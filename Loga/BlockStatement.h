#pragma once
#include <vector>
#include "Statement.h"
#include "Expression.h"

class BlockStatement : public Statement
{
public:
	BlockStatement(std::vector<Statement*> statements) :statements(statements) {}
	void accept(StatementVisitor& visitor) override;

	std::vector<Statement*> statements;


};

