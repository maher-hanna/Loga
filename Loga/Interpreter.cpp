#include <iostream>
#include <string>
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

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitLiteralNode(LiteralNode& node)
{
	return node.value;
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitUnaryNode(UnaryNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> right = evaluate(*node.right);

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

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitVariableNode(VariableNode& node)
{
	return environment->get(node.name);

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitAssignNode(AssignNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value = evaluate(*(node.value));
	environment->assign(node.name, value);
	return value;
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitLogicalNode(LogicalNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> left = evaluate(*(node.left));

	if (node.logicalOperator.type == TokenType::OR) {
		if (isTruthy(left)) return left;
	}
	else {
		if (!isTruthy(left)) return left;
	}

	return evaluate(*(node.right));
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitCallNode(CallNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> callee = evaluate(*(node.callee));

	std::vector<std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> arguments;
	for (Expression* argument : node.arguments) {
		arguments.push_back(evaluate(*argument));
	}
	if (!(std::holds_alternative<LogaCallable*>)(callee)) {
		throw new RuntimeError(node.paren,
			"Can only call functions and classes.");
	}
	LogaCallable* function = std::get<LogaCallable*>(callee);

	if (arguments.size() != function->getNumberOfArguments()) {
		std::string errorMessage = "Expected " + std::to_string(function->getNumberOfArguments()) + " arguments but got " + std::to_string(arguments.size()) + ".";
		throw new RuntimeError(node.paren, errorMessage);
	}

	return function->call(this, arguments);
}

void Interpreter::visitExpressionStatement(ExpressionStatement& statement)
{
	evaluate(*(statement.expression));
	return;
}

void Interpreter::visitPrintStatement(PrintStatement& statement)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value = evaluate(*(statement.expression));
	std::cout << stringify(value) << std::endl;
	return;
}

void Interpreter::visitVariableStatement(VariableStatement& statement)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value = nullptr;
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
	LogaFunction * function = new LogaFunction(statement, environment);
	environment->define(statement.name.lexeme, function);
	return;
}

void Interpreter::visitReturnStatement(ReturnStatement& statement)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value = nullptr;
	if (statement.value != nullptr) value = evaluate(*(statement.value));

	// Throw by value, not pointer:
	throw ReturnValue(value);
}

std::string Interpreter::stringify(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value)
{
	if (std::holds_alternative<nullptr_t>(value)) return "nil";

	if (std::holds_alternative<double>(value)) {
		std::string text = std::to_string(std::get<double>(value));
		if (text.ends_with(".0")) {
			text = text.substr(0, text.length() - 2);
		}
		return text;
	}
	if (std::holds_alternative<bool>(value)) {
		bool boolValue = std::get<bool>(value);
		return boolValue ? "true" : "false";
		
		
	}

	return std::get<std::string>(value);

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

std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> Interpreter::evaluate(Expression& node)
{
	return node.accept(*this);
}


std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitBinaryNode(BinaryNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> left = evaluate(*node.left);
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> right = evaluate(*node.right);

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

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> Interpreter::visitGroupingNode(GroupingNode& node)
{
	return evaluate(*node.expression);
}