#pragma once

#include <vector>
#include "Statement.h"
#include "Token.h"

class FunctionStatement : public Statement
{
public:
	FunctionStatement(Token name, std::vector<Token> params, std::vector<Statement*> body) :name(name),
		params(params), body(body) {
	}
	void accept(StatementVisitor& visitor) override;

	Token name;
	std::vector<Token> params;
	std::vector<Statement*> body;


};

