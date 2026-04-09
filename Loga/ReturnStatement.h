#pragma once
#include "Statement.h"
#include "Expression.h"
#include "Token.h"

class ReturnStatement : public Statement
{
public:
	ReturnStatement(Token keyword,Expression* value) :keyword(keyword), value(value) {}
	void accept(StatementVisitor& visitor) override;
	Token keyword;
	Expression* value;

};

