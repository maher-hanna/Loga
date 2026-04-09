#pragma once
#include <string>
#include <variant>


class BinaryNode;
class GroupingNode;
class LiteralNode;
class UnaryNode;
class VariableNode;
class AssignNode;
class LogicalNode;
class CallNode;
class LogaCallable;


class ExpressionVisitor {
public:
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitBinaryNode(BinaryNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitGroupingNode(GroupingNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitLiteralNode(LiteralNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitUnaryNode(UnaryNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitVariableNode(VariableNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitAssignNode(AssignNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitLogicalNode(LogicalNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitCallNode(CallNode& node) = 0;
	virtual ~ExpressionVisitor() {} // Provide a definition

};