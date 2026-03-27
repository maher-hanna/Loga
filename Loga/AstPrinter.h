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

class AstPrinter: public ExpressionVisitor {
public:
	std::string print(Expression &node);

	std::variant<double, int, std::string, std::nullptr_t, bool> visitBinaryNode(BinaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitGroupingNode(GroupingNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitLiteralNode(LiteralNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitUnaryNode(UnaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool> visitVariableNode(VariableNode& node) override;
	virtual ~AstPrinter() {} // Provide a definition

private:
	std::variant<double, int, std::string, std::nullptr_t, bool> parenthesize(const std::string &name,std::vector<Expression*>& nodes);

};