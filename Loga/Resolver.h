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
#include "LogaCallable.h"
#include "Interpreter.h"
#include "FunctionType.h"

class Resolver: public ExpressionVisitor, public StatementVisitor {
public:
	Resolver(Interpreter* interpreter): interpreter(interpreter),scopes() {}
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitBinaryNode(BinaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitGroupingNode(GroupingNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitLiteralNode(LiteralNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitUnaryNode(UnaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitVariableNode(VariableNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitAssignNode(AssignNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitLogicalNode(LogicalNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitCallNode(CallNode& node) override;

	void visitExpressionStatement(ExpressionStatement& statement) override;
	void visitPrintStatement(PrintStatement& statement) override;
	void visitVariableStatement(VariableStatement& statement) override;
	void visitBlockStatement(BlockStatement& statement) override;
	void visitIfStatement(IfStatement& statement) override;
	void visitWhileStatement(WhileStatement& statement) override;
	void visitFunctionStatement(FunctionStatement& statement) override;
	void visitReturnStatement(ReturnStatement& statement) override;

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


};