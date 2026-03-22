#include "AstPrinter.h"


std::string AstPrinter::print(ExpressionNode& node) {
	return std::get<std::string>(node.accept(*this));

}

std::variant<double, int, std::string, std::nullptr_t, bool> AstPrinter::visitBinaryNode(BinaryNode& node) {
	std::vector<ExpressionNode*> expressionItems;
	expressionItems.push_back(node.left);
	expressionItems.push_back(node.right);
	return parenthesize(node.binaryOperator.lexeme,expressionItems);

}

std::variant<double, int, std::string, std::nullptr_t, bool> AstPrinter::visitGroupingNode(GroupingNode& node) {
	std::vector<ExpressionNode*> expressionItems;
	expressionItems.push_back(node.expression);
	return parenthesize("group", expressionItems);

}

std::variant<double, int, std::string, std::nullptr_t, bool> AstPrinter::visitLiteralNode(LiteralNode& node) {
	if (std::holds_alternative<std::nullptr_t>(node.value)) return "nil";
	return std::get<std::string>(node.value);

}

std::variant<double, int, std::string, std::nullptr_t, bool> AstPrinter::visitUnaryNode(UnaryNode& node) {
	std::vector<ExpressionNode*> expressionItems;
	expressionItems.push_back(node.right);
	return parenthesize(node.unaryOperator.lexeme, expressionItems);

}

std::variant<double, int, std::string, std::nullptr_t, bool> AstPrinter::parenthesize(const std::string& name,std::vector<ExpressionNode*>& nodes)
{
	std::string result = "";

	result += "(";
	result += name;
	for (ExpressionNode* & node : nodes) {
		result += " ";
		result += std::get<std::string>(node->accept(*this));
	}
	result += ")";


	return result;
}
