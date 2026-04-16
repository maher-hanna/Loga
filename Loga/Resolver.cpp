#include <variant>
#include <string>
#include "Resolver.h"
#include "BlockStatement.h"
#include "VariableStatement.h"
#include "ReturnStatement.h"
#include "FunctionType.h"


std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitBinaryNode(BinaryNode& node) {
	resolve(node.left);
	resolve(node.right);
	return nullptr;

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitGroupingNode(GroupingNode& node) {
	resolve(node.expression);
	return nullptr;

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitLiteralNode(LiteralNode& node) {
	return nullptr;

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitUnaryNode(UnaryNode& node) {
	resolve(node.right);
	return nullptr;

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitVariableNode(VariableNode& node)
{
	if (!scopes.empty()) {
		if (scopes.back().contains(node.name.lexeme) && scopes.back()[node.name.lexeme] == false) {
			error(node.name,
				"Can't read local variable in its own initializer.");
		}
		
	}

	resolveLocal(&node, node.name);
	return nullptr;
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitAssignNode(AssignNode& node)
{
	resolve(node.value);
	resolveLocal(&node, node.name);
	return nullptr;
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitLogicalNode(LogicalNode& node)
{
	resolve(node.left);
	resolve(node.right);
	return nullptr;
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Resolver::visitCallNode(CallNode& node)
{
	resolve(node.callee);

	for (Expression* argument : node.arguments) {
		resolve(argument);
	}

	return nullptr;
}

void Resolver::visitExpressionStatement(ExpressionStatement& statement)
{
	resolve(statement.expression);
	return;
}

void Resolver::visitPrintStatement(PrintStatement& statement)
{
	resolve(statement.expression);
	return;
}

void Resolver::visitVariableStatement(VariableStatement& statement)
{
	declare(statement.name);
	if (statement.expression != nullptr) {
		resolve(statement.expression);
	}
	define(statement.name);
	return;
}

void Resolver::visitBlockStatement(BlockStatement& statement)
{
	beginScope();
	resolve(statement.statements);
	endScope();
	return;
}

void Resolver::visitIfStatement(IfStatement& statement)
{
	resolve(statement.condition);
	resolve(statement.thenBranch);
	if (statement.elseBranch != nullptr) resolve(statement.elseBranch);
	return;
}

void Resolver::visitWhileStatement(WhileStatement& statement)
{
	resolve(statement.condition);
	resolve(statement.body);
	return;
}

void Resolver::visitFunctionStatement(FunctionStatement& statement)
{
	declare(statement.name);
	define(statement.name);

	resolveFunction(statement, FunctionType::FUNCTION);
	return;
}

void Resolver::visitReturnStatement(ReturnStatement& statement)
{
	if (currentFunction == FunctionType::NONE) {
		error(statement.keyword, "Can't return from top-level code.");
	}
	if (statement.value != nullptr) {
		resolve(statement.value);
	}

	return;
}

void Resolver::resolve(std::vector<Statement*> statements)
{
	for (Statement* statement : statements) {
		resolve(statement);
	}
}

void Resolver::resolve(Statement* statement)

{
	statement->accept(*this);

}

void Resolver::resolve(Expression* expression)
{
	expression->accept(*this);
}

void Resolver::beginScope()
{
	scopes.push_back(std::map<std::string, bool>());

}

void Resolver::endScope()
{
	scopes.pop_back();
}

void Resolver::declare(Token name)
{
	if (scopes.empty()) return;

	std::map<std::string, bool>& scope = scopes.back();
	if (scope.contains(name.lexeme)) {
		error(name,
			"Already a variable with this name in this scope.");
	}
	scope[name.lexeme] = false;
}

void Resolver::define(Token name)
{
	if (scopes.empty()) return;

	std::map<std::string, bool>& scope = scopes.back();
	scope[name.lexeme] = true;
}

void Resolver::resolveLocal(Expression* expr, Token name)
{
	for (int i = scopes.size() - 1; i >= 0; i--) {
		if (scopes[i].contains(name.lexeme)) {
			interpreter->resolve(expr, scopes.size() - 1 - i);
			return;
		}
	}
}

void Resolver::resolveFunction(FunctionStatement& function, FunctionType functionType)
{
	FunctionType enclosingFunction = currentFunction;
	currentFunction = functionType;

	beginScope();
	for (Token param : function.params) {
		declare(param);
		define(param);
	}
	resolve(function.body);
	endScope();
	currentFunction = enclosingFunction;

}

