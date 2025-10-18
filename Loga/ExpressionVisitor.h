#pragma once
#include <string>

class BinaryNode;
class GroupingNode;
class LiteralNode;
class UnaryNode;

class ExpressionVisitor {
public:
	virtual std::string visitBinaryNode(BinaryNode &node) = 0;
	virtual std::string visitGroupingNode(GroupingNode &node) = 0;
	virtual std::string visitLiteralNode(LiteralNode &node) = 0;
	virtual std::string visitUnaryNode(UnaryNode &node) = 0;
	virtual ~ExpressionVisitor() {} // Provide a definition

};