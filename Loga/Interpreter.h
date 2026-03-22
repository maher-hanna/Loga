#pragma once

#include <variant>
#include <iostream>
#include "ExpressionVisitor.h"
#include "BinaryNode.h"
#include "UnaryNode.h"
#include "GroupingNode.h"
#include "LiteralNode.h"
#include "RuntimeError.h"
#include "Errors.h"

class Interpreter : public ExpressionVisitor {
public:

	std::variant<double, int, std::string, std::nullptr_t, bool> visitBinaryNode(BinaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitGroupingNode(GroupingNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitLiteralNode(LiteralNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitUnaryNode(UnaryNode& node) override;

	std::string stringify(std::variant<double, int, std::string, std::nullptr_t, bool> value);

	void interpret(ExpressionNode& expression) {
		try {
			std::variant<double, int, std::string, std::nullptr_t, bool> value = evaluate(expression);
			std::cout << stringify(value) << std::endl;
		}
		catch (RuntimeError &err) {
			error(err);
		}
	}

private:
	std::variant<double, int, std::string, std::nullptr_t, bool> evaluate(ExpressionNode& node) ;

	bool isTruthy(std::variant<double, int, std::string, std::nullptr_t, bool> value) {
		if (std::holds_alternative<nullptr_t>(value)) return false;
		if (std::holds_alternative<nullptr_t>(value)) return std::get<bool>(value);
		return true;
	}

	bool isEqual(std::variant<double, int, std::string, std::nullptr_t, bool>  a,
		std::variant<double, int, std::string, std::nullptr_t, bool>  b) {
		if (std::holds_alternative<nullptr_t>(a) && std::holds_alternative<nullptr_t>(b)) return true;
		if (std::holds_alternative<nullptr_t>(a)) return false;

		return a == b;
	}

	void checkNumberOperand(Token opr, std::variant<double, int, std::string, std::nullptr_t, bool> operand) {
		if (std::holds_alternative<double>(operand)) return;
		throw RuntimeError(opr, "Operand must be a number.");
	}
	void checkNumberOperands(Token opr, std::variant<double, int, std::string, std::nullptr_t, bool> left,
		std::variant<double, int, std::string, std::nullptr_t, bool> right) {
		if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) return;

		throw RuntimeError(opr, "Operands must be a numbers.");
	}

};
