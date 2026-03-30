#pragma once


class ExpressionStatement;
class PrintStatement;
class VariableStatement;
class BlockStatement;


class StatementVisitor {
public:
	virtual void visitExpressionStatement(ExpressionStatement& statement) = 0;
	virtual void visitPrintStatement(PrintStatement& statement) = 0;
	virtual void visitVariableStatement(VariableStatement& statement) = 0;
	virtual void visitBlockStatement(BlockStatement& statement) = 0;
	virtual ~StatementVisitor() {} // Provide a definition

};