#pragma once
#include <string>
#include <variant>

class BinaryNode;
class GroupingNode;
class LiteralNode;
class UnaryNode;
class VariableNode;


class ExpressionVisitor {
public:
	virtual std::variant<double, int, std::string, std::nullptr_t, bool> visitBinaryNode(BinaryNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool> visitGroupingNode(GroupingNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool> visitLiteralNode(LiteralNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool> visitUnaryNode(UnaryNode& node) = 0;
	virtual std::variant<double, int, std::string, std::nullptr_t, bool> visitVariableNode(VariableNode& node) = 0;
	virtual ~ExpressionVisitor() {} // Provide a definition

};