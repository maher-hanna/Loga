#include "Value.h"
#include <string>
#include "Resolver.h"
#include "BlockStatement.h"
#include "VariableStatement.h"
#include "ReturnStatement.h"
#include "FunctionType.h"


Value Resolver::visitBinaryNode(BinaryNode& node) {
	resolve(node.left);
	resolve(node.right);
	return nullptr;

}

Value Resolver::visitGroupingNode(GroupingNode& node) {
	resolve(node.expression);
	return nullptr;

}

Value Resolver::visitLiteralNode(LiteralNode& node) {
	return nullptr;

}

Value Resolver::visitUnaryNode(UnaryNode& node) {
	resolve(node.right);
	return nullptr;

}

Value Resolver::visitVariableNode(VariableNode& node)
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

Value Resolver::visitAssignNode(AssignNode& node)
{
	resolve(node.value);
	resolveLocal(&node, node.name);
	return nullptr;
}

Value Resolver::visitLogicalNode(LogicalNode& node)
{
	resolve(node.left);
	resolve(node.right);
	return nullptr;
}

Value Resolver::visitCallNode(CallNode& node)
{
	resolve(node.callee);

	for (Expression* argument : node.arguments) {
		resolve(argument);
	}

	return nullptr;
}

Value Resolver::visitGetNode(GetNode& node)
{
	resolve(node.object);
	return nullptr;
}

Value Resolver::visitSetNode(SetNode& node)
{
	resolve(node.value);
	resolve(node.object);
	return nullptr;
}

Value Resolver::visitThisNode(ThisNode& node)
{
	if (currentClass == ClassType::NONE) {
		error(node.keyword,
			"Can't use 'this' outside of a class.");
		return nullptr;
	}
	resolveLocal(&node, node.keyword);
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
		if (currentFunction == FunctionType::INITIALIZER) {
			error(statement.keyword,
				"Can't return a value from an initializer.");
		}
		resolve(statement.value);
	}

	return;
}

void Resolver::visitClassStatement(ClassStatement& statement)
{
	ClassType enclosingClass = currentClass;
	currentClass = ClassType::CLASS;
	declare(statement.name);
	define(statement.name);
	beginScope();
	scopes.back().insert({"this", true});
	for (FunctionStatement* method : statement.methods) {
		FunctionType declaration = FunctionType::METHOD;
		if (method->name.lexeme == "init") {
			declaration = FunctionType::INITIALIZER;
		}
		resolveFunction(*method, declaration);
	}
	endScope();
	currentClass = enclosingClass;

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

