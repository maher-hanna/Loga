#include "AstPrinter.h"


std::string AstPrinter::print(ExpressionNode& node) {
	return node.accept(*this);

}

std::string AstPrinter::visitBinaryNode(BinaryNode& node) {
	std::vector<ExpressionNode*> expressionItems;
	expressionItems.push_back(node.left);
	expressionItems.push_back(node.right);
	return parenthesize(node.binaryOperator.lexeme,expressionItems);

}

std::string AstPrinter::visitGroupingNode(GroupingNode& node) {
	std::vector<ExpressionNode*> expressionItems;
	expressionItems.push_back(node.expression);
	return parenthesize("group", expressionItems);

}

std::string AstPrinter::visitLiteralNode(LiteralNode& node) {
	if (node.value == "") return "nil";
	return node.value;

}

std::string AstPrinter::visitUnaryNode(UnaryNode& node) {
	std::vector<ExpressionNode*> expressionItems;
	expressionItems.push_back(node.right);
	return parenthesize(node.unaryOperator.lexeme, expressionItems);

}

std::string AstPrinter::parenthesize(const std::string& name,std::vector<ExpressionNode*>& nodes)
{
	std::string result = "";

	result += "(";
	result += name;
	for (ExpressionNode* & node : nodes) {
		result += " ";
		result += node->accept(*this);
	}
	result += ")";


	return result;
}
