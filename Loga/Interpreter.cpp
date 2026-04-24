#include <iostream>
#include <string>
#include <unordered_map>
#include "Interpreter.h"
#include "ExpressionStatement.h"
#include "PrintStatement.h"
#include "VariableStatement.h"
#include "BlockStatement.h"
#include "IfStatement.h"
#include "LogaCallable.h"
#include "LogaFunction.h"
#include "ReturnStatement.h"
#include "ReturnValue.h"
#include "LogaClass.h"
#include "LogaFunction.h"
#include "Value.h"

Value Interpreter::visitLiteralNode(LiteralNode& node)
{
	return node.value;
}

Value Interpreter::visitUnaryNode(UnaryNode& node)
{
	Value right = evaluate(*node.right);

	switch (node.unaryOperator.type) {
	case TokenType::BANG:
		return !isTruthy(right);
	case TokenType::MINUS:
		checkNumberOperand(node.unaryOperator, right);
		return -std::get<double>(right);
	}

	// Unreachable.
	return nullptr;
}

Value Interpreter::visitVariableNode(VariableNode& node)
{
	return lookUpVariable(node.name, &node);


}

Value Interpreter::visitAssignNode(AssignNode& node)
{
	Value value = evaluate(*(node.value));
	int distance = locals[&node];
	if (distance != 0) {
		environment->assignAt(distance, node.name, value);
	}
	else {
		globals->assign(node.name, value);
	}
	return value;
}

Value Interpreter::visitLogicalNode(LogicalNode& node)
{
	Value left = evaluate(*(node.left));

	if (node.logicalOperator.type == TokenType::OR) {
		if (isTruthy(left)) return left;
	}
	else {
		if (!isTruthy(left)) return left;
	}

	return evaluate(*(node.right));
}

Value Interpreter::visitCallNode(CallNode& node)
{
	Value callee = evaluate(*(node.callee));

	std::vector<Value> arguments;
	for (Expression* argument : node.arguments) {
		arguments.push_back(evaluate(*argument));
	}
	if (!(std::holds_alternative<LogaCallable*>)(callee)) {
		throw RuntimeError(node.paren,
			"Can only call functions and classes.");
	}
	LogaCallable* function = std::get<LogaCallable*>(callee);

	if (arguments.size() != function->getNumberOfArguments()) {
		std::string errorMessage = "Expected " + std::to_string(function->getNumberOfArguments()) + " arguments but got " + std::to_string(arguments.size()) + ".";
		throw new RuntimeError(node.paren, errorMessage);
	}

	return function->call(this, arguments);
}

Value Interpreter::visitGetNode(GetNode& node)
{
	Value object = evaluate(*(node.object));
	if (std::holds_alternative<LogaInstance*>(object)) {
		return (std::get<LogaInstance*>(object))->get(node.name);
	}

	throw RuntimeError(node.name,
		"Only instances have properties.");
}

Value Interpreter::visitSetNode(SetNode& node)
{
	Value object = evaluate(*(node.object));

	if (!(std::holds_alternative<LogaInstance*>(object))) {
		throw RuntimeError(node.name,
			"Only instances have fields.");
	}

	Value value = evaluate(*(node.value));
	(std::get<LogaInstance*>(object))->set(node.name, value);
	return value;
}

Value Interpreter::visitThisNode(ThisNode& node)
{
	return lookUpVariable(node.keyword, &node);
}

void Interpreter::visitExpressionStatement(ExpressionStatement& statement)
{
	evaluate(*(statement.expression));
	return;
}

void Interpreter::visitPrintStatement(PrintStatement& statement)
{
	Value value = evaluate(*(statement.expression));
	std::cout << stringify(value) << std::endl;
	return;
}

void Interpreter::visitVariableStatement(VariableStatement& statement)
{
	Value value = nullptr;
	if (statement.expression != nullptr) {
		value = evaluate(*(statement.expression));
	}

	environment->define(statement.name.lexeme, value);
	return;
}

void Interpreter::visitBlockStatement(BlockStatement& statement)
{
	Environment *blockEnvironment = new Environment();
	blockEnvironment->enclosing = environment;
	executeBlock(statement.statements, blockEnvironment);
	return;
}

void Interpreter::visitIfStatement(IfStatement& statement)
{
	if (isTruthy(evaluate(*(statement.condition)))) {
		execute(statement.thenBranch);
	}
	else if (statement.elseBranch != nullptr) {
		execute(statement.elseBranch);
	}
	return;
}

void Interpreter::visitWhileStatement(WhileStatement& statement)
{
	while (isTruthy(evaluate(*(statement.condition)))) {
		execute(statement.body);
	}
	return;
}

void Interpreter::visitFunctionStatement(FunctionStatement& statement)
{
	LogaFunction * function = new LogaFunction(statement, environment,false);
	environment->define(statement.name.lexeme, function);
	return;
}

void Interpreter::visitReturnStatement(ReturnStatement& statement)
{
	Value value = nullptr;
	if (statement.value != nullptr) value = evaluate(*(statement.value));

	// Throw by value, not pointer:
	throw ReturnValue(value);
}

void Interpreter::visitClassStatement(ClassStatement& statement)
{
	environment->define(statement.name.lexeme, nullptr);
	std::unordered_map<std::string, LogaFunction*> methods;
	for (FunctionStatement* method : statement.methods) {
		LogaFunction* function = new LogaFunction(*method, environment, method->name.lexeme == "init");
		methods[method->name.lexeme] = function;
	}

	LogaClass* klass = new LogaClass(statement.name.lexeme, methods);
	environment->assign(statement.name, klass);
	return;
}

void Interpreter::resolve(Expression* expr, int depth)
{
	locals[expr] =  depth;

}

Value Interpreter::lookUpVariable(Token name, Expression* expr)
{
	if (locals.contains(expr)) {
		int distance = locals[expr];
		return environment->getAt(distance, name.lexeme);
	}
	else {
		return globals->get(name);
	}
}

std::string Interpreter::stringify(Value value)
{
	if (std::holds_alternative<std::nullptr_t>(value)) return "nil";
	if (std::holds_alternative<double>(value)) { /* existing code */ }
	if (std::holds_alternative<int>(value)) return std::to_string(std::get<int>(value));
	if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? "true" : "false";
	if (std::holds_alternative<std::string>(value)) return std::get<std::string>(value);
	if (std::holds_alternative<LogaCallable*>(value)) return std::get<LogaCallable*>(value)->toString();
	if (std::holds_alternative<LogaInstance*>(value)) return std::get<LogaInstance*>(value)->toString();
	return "<unknown>";


}

void Interpreter::executeBlock(std::vector<Statement*> statements, Environment * env)
{
	Environment *previous = this->environment;
	try {
		this->environment = env;

		for (Statement * statement : statements) {
			execute(statement);
		}
	}
	catch(...) {
		this->environment = previous;
		throw;
	}
	this->environment = previous;

}

Value Interpreter::evaluate(Expression& node)
{
	return node.accept(*this);
}


Value Interpreter::visitBinaryNode(BinaryNode& node)
{
	Value left = evaluate(*node.left);
	Value right = evaluate(*node.right);

	switch (node.binaryOperator.type) {
	case TokenType::MINUS:
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) - std::get<double>(right);
	case TokenType::SLASH:
		checkNumberOperands(node.binaryOperator, left, right);
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) / std::get<double>(right);
	case TokenType::STAR:
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) * std::get<double>(right);
	case TokenType::PLUS:
		if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
			return std::get<double>(left) + std::get<double>(right);
		}

		if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
			return std::get<std::string>(left) + std::get<std::string>(right);
		}
		throw RuntimeError(node.binaryOperator,
			"Operands must be two numbers or two strings.");
	case TokenType::GREATER:
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) > std::get<double>(right);
	case TokenType::GREATER_EQUAL:
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) >= std::get<double>(right);
	case TokenType::LESS:
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) < std::get<double>(right);
	case TokenType::LESS_EQUAL:
		checkNumberOperands(node.binaryOperator, left, right);
		return std::get<double>(left) <= std::get<double>(right);

	case TokenType::BANG_EQUAL: return !isEqual(left, right);
	case TokenType::EQUAL_EQUAL: return isEqual(left, right);
	}

	// Unreachable.
	return nullptr;
}

Value Interpreter::visitGroupingNode(GroupingNode& node)
{
	return evaluate(*node.expression);
}