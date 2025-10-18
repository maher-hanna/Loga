#pragma once
#include <string>
#include <vector>
#include "ExpressionNode.h"
#include "ExpressionVisitor.h"
#include "BinaryNode.h"
#include "UnaryNode.h"
#include "GroupingNode.h"
#include "LiteralNode.h"

class AstPrinter: public ExpressionVisitor {
public:
	std::string print(ExpressionNode &node);

	std::string visitBinaryNode(BinaryNode& node) override;
	std::string visitGroupingNode(GroupingNode& node) override;
	std::string visitLiteralNode(LiteralNode& node) override;
	std::string visitUnaryNode(UnaryNode& node) override;
	virtual ~AstPrinter() {} // Provide a definition

private:
	std::string parenthesize(const std::string &name,std::vector<ExpressionNode*>& nodes);

};