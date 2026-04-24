#pragma once
#include <string>
#include <vector>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "BinaryNode.h"
#include "UnaryNode.h"
#include "GroupingNode.h"
#include "LiteralNode.h"
#include "VariableNode.h"
#include "AssignNode.h"
#include "LogicalNode.h"
#include "CallNode.h"
#include "Value.h"

class AstPrinter: public ExpressionVisitor {
public:
	std::string print(Expression &node);

	Value visitBinaryNode(BinaryNode& node) override;
	Value visitGroupingNode(GroupingNode& node) override;
	Value visitLiteralNode(LiteralNode& node) override;
	Value visitUnaryNode(UnaryNode& node) override;
	Value visitVariableNode(VariableNode& node) override;
	Value visitAssignNode(AssignNode& node) override;
	Value visitLogicalNode(LogicalNode& node) override;
	Value visitCallNode(CallNode& node) override;
	virtual ~AstPrinter() {} // Provide a definition

private:
	Value parenthesize(const std::string &name,std::vector<Expression*>& nodes);

};