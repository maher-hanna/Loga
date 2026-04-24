#include "AstPrinter.h"
#include <variant>
#include <string>


std::string AstPrinter::print(Expression& node) {
	return std::get<std::string>(node.accept(*this));

}

Value AstPrinter::visitBinaryNode(BinaryNode& node) {
	std::vector<Expression*> expressionItems;
	expressionItems.push_back(node.left);
	expressionItems.push_back(node.right);
	return parenthesize(node.binaryOperator.lexeme,expressionItems);

}

Value AstPrinter::visitGroupingNode(GroupingNode& node) {
	std::vector<Expression*> expressionItems;
	expressionItems.push_back(node.expression);
	return parenthesize("group", expressionItems);

}

Value AstPrinter::visitLiteralNode(LiteralNode& node) {
	if (std::holds_alternative<std::nullptr_t>(node.value)) return "nil";
	return std::get<std::string>(node.value);

}

Value AstPrinter::visitUnaryNode(UnaryNode& node) {
	std::vector<Expression*> expressionItems;
	expressionItems.push_back(node.right);
	return parenthesize(node.unaryOperator.lexeme, expressionItems);

}

Value AstPrinter::visitVariableNode(VariableNode& node)
{
	return Value();
}

Value AstPrinter::visitAssignNode(AssignNode& node)
{
	return Value();
}

Value AstPrinter::visitLogicalNode(LogicalNode& node)
{
	return Value();
}

Value AstPrinter::visitCallNode(CallNode& node)
{
	return Value();
}

Value AstPrinter::parenthesize(const std::string& name,std::vector<Expression*>& nodes)
{
	std::string result = "";

	result += "(";
	result += name;
	for (Expression* & node : nodes) {
		result += " ";
		result += std::get<std::string>(node->accept(*this));
	}
	result += ")";


	return result;
}
