#pragma once
#include <string>
#include <vector>
#include <map>

#include "ExpressionVisitor.h"
#include "StatementVisitor.h"
#include "BinaryNode.h"
#include "UnaryNode.h"
#include "GroupingNode.h"
#include "LiteralNode.h"
#include "VariableNode.h"
#include "AssignNode.h"
#include "LogicalNode.h"
#include "CallNode.h"
#include "GetNode.h"
#include "SetNode.h"
#include "ThisNode.h"
#include "Interpreter.h"
#include "FunctionType.h"
#include "ClassType.h"
#include "ClassStatement.h"

class Resolver: public ExpressionVisitor, public StatementVisitor {
public:
	Resolver(Interpreter* interpreter): interpreter(interpreter),scopes() {}
	Value visitBinaryNode(BinaryNode& node) override;
	Value visitGroupingNode(GroupingNode& node) override;
	Value visitLiteralNode(LiteralNode& node) override;
	Value visitUnaryNode(UnaryNode& node) override;
	Value visitVariableNode(VariableNode& node) override;
	Value visitAssignNode(AssignNode& node) override;
	Value visitLogicalNode(LogicalNode& node) override;
	Value visitCallNode(CallNode& node) override;
	Value visitGetNode(GetNode& node) override;
	Value visitSetNode(SetNode& node) override;
	Value visitThisNode(ThisNode& node) override;

	void visitExpressionStatement(ExpressionStatement& statement) override;
	void visitPrintStatement(PrintStatement& statement) override;
	void visitVariableStatement(VariableStatement& statement) override;
	void visitBlockStatement(BlockStatement& statement) override;
	void visitIfStatement(IfStatement& statement) override;
	void visitWhileStatement(WhileStatement& statement) override;
	void visitFunctionStatement(FunctionStatement& statement) override;
	void visitReturnStatement(ReturnStatement& statement) override;
	void visitClassStatement(ClassStatement& statement) override;

	void resolve(std::vector<Statement*> statements);
	void resolve(Statement* statement);
	void resolve(Expression* expression);
	void beginScope();
	void endScope();
	void declare(Token name);
	void define(Token name);
	void resolveLocal(Expression* expr, Token name);
	void resolveFunction(FunctionStatement& function,FunctionType functionType);
	virtual ~Resolver() {} // Provide a definition

private:
	Interpreter* interpreter;
	std::vector<std::map<std::string, bool>> scopes;
	FunctionType currentFunction = FunctionType::NONE;
	ClassType currentClass = ClassType::NONE;


};