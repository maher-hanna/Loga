#pragma once
#include <vector>
#include "FunctionStatement.h"
#include "Expression.h"
#include "Token.h"

class ClassStatement : public Statement
{
public:
	ClassStatement(Token name,std::vector<FunctionStatement*> methods) :name(name), methods(methods) {}
	void accept(StatementVisitor& visitor) override;

	Token name;
	std::vector<FunctionStatement*> methods;


};

