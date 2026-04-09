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
#include "LogaCallable.h"

class AstPrinter: public ExpressionVisitor {
public:
	std::string print(Expression &node);

	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitBinaryNode(BinaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitGroupingNode(GroupingNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitLiteralNode(LiteralNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitUnaryNode(UnaryNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitVariableNode(VariableNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitAssignNode(AssignNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitLogicalNode(LogicalNode& node) override;
	std::variant<double, int, std::string, std::nullptr_t, bool,LogaCallable*> visitCallNode(CallNode& node) override;
	virtual ~AstPrinter() {} // Provide a definition

private:
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> parenthesize(const std::string &name,std::vector<Expression*>& nodes);

};