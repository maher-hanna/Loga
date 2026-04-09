#include "AstPrinter.h"
#include <variant>
#include <string>


std::string AstPrinter::print(Expression& node) {
	return std::get<std::string>(node.accept(*this));

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitBinaryNode(BinaryNode& node) {
	std::vector<Expression*> expressionItems;
	expressionItems.push_back(node.left);
	expressionItems.push_back(node.right);
	return parenthesize(node.binaryOperator.lexeme,expressionItems);

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitGroupingNode(GroupingNode& node) {
	std::vector<Expression*> expressionItems;
	expressionItems.push_back(node.expression);
	return parenthesize("group", expressionItems);

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitLiteralNode(LiteralNode& node) {
	if (std::holds_alternative<std::nullptr_t>(node.value)) return "nil";
	return std::get<std::string>(node.value);

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitUnaryNode(UnaryNode& node) {
	std::vector<Expression*> expressionItems;
	expressionItems.push_back(node.right);
	return parenthesize(node.unaryOperator.lexeme, expressionItems);

}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitVariableNode(VariableNode& node)
{
	return std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>();
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitAssignNode(AssignNode& node)
{
	return std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>();
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitLogicalNode(LogicalNode& node)
{
	return std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>();
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::visitCallNode(CallNode& node)
{
	return std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>();
}

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> AstPrinter::parenthesize(const std::string& name,std::vector<Expression*>& nodes)
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
