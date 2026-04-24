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
#include "GetNode.h"
#include "SetNode.h"
#include "CallNode.h"
#include "ThisNode.h"
#include "RuntimeError.h"
#include "Errors.h"
#include "StatementVisitor.h"
#include "ExpressionStatement.h"
#include "IfStatement.h"
#include "WhileStatement.h"
#include "PrintStatement.h"
#include "FunctionStatement.h"
#include "ClassStatement.h"
#include "Environment.h"
#include "LogaCallable.h"

class Interpreter : public ExpressionVisitor, StatementVisitor {
public:
	Interpreter() :globals(new Environment),environment(globals) {
		globals->define("clock", new EmptyFunctionCall);
	}

	Environment* globals;
	std::unordered_map<Expression*, int> locals;


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
	void resolve(Expression* expr, int depth);
	Value lookUpVariable(Token name, Expression* expr);

	std::string stringify(Value value);

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


	Value evaluate(Expression& node);

	bool isTruthy(Value value) {
		if (std::holds_alternative<nullptr_t>(value)) return false;
		if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
		return true;
	}

	bool isEqual(Value  a,
		Value  b) {
		if (std::holds_alternative<nullptr_t>(a) && std::holds_alternative<nullptr_t>(b)) return true;
		if (std::holds_alternative<nullptr_t>(a)) return false;

		return a == b;
	}

	void checkNumberOperand(Token opr, Value operand) {
		if (std::holds_alternative<double>(operand)) return;
		throw RuntimeError(opr, "Operand must be a number.");
	}
	void checkNumberOperands(Token opr, Value left,
		Value right) {
		if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) return;

		throw RuntimeError(opr, "Operands must be a numbers.");
	}

};
