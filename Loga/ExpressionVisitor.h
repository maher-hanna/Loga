#pragma once
#include "Value.h"


class BinaryNode;
class GroupingNode;
class LiteralNode;
class UnaryNode;
class VariableNode;
class AssignNode;
class LogicalNode;
class CallNode;
class GetNode;
class SetNode;
class ThisNode;
class LogaCallable;


class ExpressionVisitor {
public:
	virtual Value visitBinaryNode(BinaryNode& node) = 0;
	virtual Value visitGroupingNode(GroupingNode& node) = 0;
	virtual Value visitLiteralNode(LiteralNode& node) = 0;
	virtual Value visitUnaryNode(UnaryNode& node) = 0;
	virtual Value visitVariableNode(VariableNode& node) = 0;
	virtual Value visitAssignNode(AssignNode& node) = 0;
	virtual Value visitLogicalNode(LogicalNode& node) = 0;
	virtual Value visitCallNode(CallNode& node) = 0;
	virtual Value visitGetNode(GetNode& node) = 0;
	virtual Value visitSetNode(SetNode& node) = 0;
	virtual Value visitThisNode(ThisNode& node) = 0;
	virtual ~ExpressionVisitor() {} // Provide a definition

};