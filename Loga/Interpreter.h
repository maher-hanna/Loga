#pragma once

#include <variant>
#include <vector>
#include <unordered_map>
#include "ExpressionVisitor.h"
#include "BinaryNode.h"
#include "UnaryNode.h"
#include "GroupingNode.h"
#include "LiteralNode.h"
#include "VariableNode.h"
#include "AssignNode.h"
#include "LogicalNode.h"
#include "CallNode.h"
#include "RuntimeError.h"
#include "Errors.h"
#include "StatementVisitor.h"
#include "ExpressionStatement.h"
#include "IfStatement.h"
#include "WhileStatement.h"
#include "PrintStatement.h"
#include "FunctionStatement.h"
#include "Environment.h"
#include "LogaCallable.h"

class Interpreter : public ExpressionVisitor, StatementVisitor {
public:
	Interpreter() :globals(new Environment),environment(globals) {
		globals->define("clock", new EmptyFunctionCall);
	}

	Environment* globals;
	std::unordered_map<Expression*, int> locals;


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
	void resolve(Expression* expr, int depth);
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> lookUpVariable(Token name, Expression* expr);

	std::string stringify(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value);

	void execute(Statement* stmt) {
		stmt->accept(*this);
	}
	void executeBlock(std::vector<Statement*> statements,
		Environment * environment);

	void interpret(std::vector<Statement*> statements) {
		try {
			for (auto &statement : statements) {
				execute(statement);
			}
		}
		catch (RuntimeError& err) {
			error(err);
		}

	}

private:
	Environment * environment = const_cast<Environment*>(globals);


	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> evaluate(Expression& node);

	bool isTruthy(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value) {
		if (std::holds_alternative<nullptr_t>(value)) return false;
		if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
		return true;
	}

	bool isEqual(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>  a,
		std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>  b) {
		if (std::holds_alternative<nullptr_t>(a) && std::holds_alternative<nullptr_t>(b)) return true;
		if (std::holds_alternative<nullptr_t>(a)) return false;

		return a == b;
	}

	void checkNumberOperand(Token opr, std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> operand) {
		if (std::holds_alternative<double>(operand)) return;
		throw RuntimeError(opr, "Operand must be a number.");
	}
	void checkNumberOperands(Token opr, std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> left,
		std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> right) {
		if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) return;

		throw RuntimeError(opr, "Operands must be a numbers.");
	}

};
