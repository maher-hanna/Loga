#pragma once


class ExpressionStatement;
class PrintStatement;


class StatementVisitor {
public:
	virtual void visitExpressionStatement(ExpressionStatement& statement) = 0;
	virtual void visitPrintStatement(PrintStatement& statement) = 0;
	virtual ~StatementVisitor() {} // Provide a definition

};