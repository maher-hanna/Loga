#include "Interpreter.h"
#include "ExpressionStatement.h"
#include "PrintStatement.h"
#include "VariableStatement.h"
#include "BlockStatement.h"

std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::visitLiteralNode(LiteralNode& node)
{
	return node.value;
}

std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::visitUnaryNode(UnaryNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool> right = evaluate(*node.right);

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

std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::visitVariableNode(VariableNode& node)
{
	return environment.get(node.name);

}

std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::visitAssignNode(AssignNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool> value = evaluate(*(node.value));
	environment.assign(node.name, value);
	return value;
}

void Interpreter::visitExpressionStatement(ExpressionStatement& statement)
{
	evaluate(*(statement.expression));
	return;
}

void Interpreter::visitPrintStatement(PrintStatement& statement)
{
	std::variant<double, int, std::string, std::nullptr_t, bool> value = evaluate(*(statement.expression));
	std::cout << stringify(value) << std::endl;
	return;
}

void Interpreter::visitVariableStatement(VariableStatement& statement)
{
	std::variant<double, int, std::string, std::nullptr_t, bool> value = nullptr;
	if (statement.expression != nullptr) {
		value = evaluate(*(statement.expression));
	}

	environment.define(statement.name.lexeme, value);
	return;
}

void Interpreter::visitBlockStatement(BlockStatement& statement)
{
	executeBlock(statement.statements, new Environment(environment));
	return;
}

std::string Interpreter::stringify(std::variant<double, int, std::string, std::nullptr_t, bool> value)
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

void Interpreter::executeBlock(std::vector<Statement*> statements, Environment * environment)
{
	Environment previous = this->environment;
	try {
		this->environment = environment;

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

std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::evaluate(Expression& node)
{
	return node.accept(*this);
}


std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::visitBinaryNode(BinaryNode& node)
{
	std::variant<double, int, std::string, std::nullptr_t, bool> left = evaluate(*node.left);
	std::variant<double, int, std::string, std::nullptr_t, bool> right = evaluate(*node.right);

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

std::variant<double, int, std::string, std::nullptr_t, bool> Interpreter::visitGroupingNode(GroupingNode& node)
{
	return evaluate(*node.expression);
}