#include "Parser.h"
#include "BinaryNode.h"
#include "TokenType.h"
#include "UnaryNode.h"
#include "LiteralNode.h"
#include "GroupingNode.h"
#include "ParseError.h"

ExpressionNode* Parser::equality() {
	ExpressionNode* expr = comparison();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::BANG_EQUAL);
	arr.push_back(TokenType::EQUAL_EQUAL);

	while (match(arr)) {
		Token opr = previous();
		ExpressionNode* right =
			comparison();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;
}

bool Parser::match(const std::vector<TokenType>& types) {
	for (TokenType type : types) {
		if (check(type)) {
			advance();
			return true;
		}
	}

	return false;
}


ExpressionNode* Parser::term() {
	ExpressionNode* expr = factor();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::MINUS);
	arr.push_back(TokenType::PLUS);

	while (match(arr)) {
		Token opr = previous();
		ExpressionNode* right = factor();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;

}

ExpressionNode* Parser::factor() {
	ExpressionNode* expr = unary();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::SLASH);
	arr.push_back(TokenType::STAR);

	while (match(arr)) {
		Token opr = previous();
		ExpressionNode* right = unary();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;

}

ExpressionNode* Parser::unary() {
	std::vector<TokenType> arr;
	arr.push_back(TokenType::BANG);
	arr.push_back(TokenType::MINUS);

	if (match(arr)) {
		Token opr = previous();
		ExpressionNode* right = unary();
		return new UnaryNode(opr, right);
	}

	return primary();

}

ExpressionNode* Parser::primary() {
	std::vector<TokenType> arr;
	arr.push_back(TokenType::BANG);

	if (match({ TokenType::FALSE })) return new LiteralNode("false");
	if (match({ TokenType::TRUE })) return new LiteralNode("true");
	if (match({ TokenType::NIL })) return new LiteralNode("null");

	if (match({ TokenType::NUMBER, TokenType::STRING })) {
		return new LiteralNode(previous().literal);
	}

	if (match({ TokenType::LEFT_PAREN })) {
		ExpressionNode* expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return new GroupingNode(expr);
	}
	error(peek(), "Expect expression.");


}

ExpressionNode* Parser::comparison() {
	ExpressionNode* expr = term();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::GREATER);
	arr.push_back(TokenType::GREATER_EQUAL);
	arr.push_back(TokenType::LESS);
	arr.push_back(TokenType::LESS_EQUAL);

	while (match(arr)) {
		Token opr = previous();
		ExpressionNode* right = term();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;
}

Token Parser::consume(TokenType type, std::string message) {
	if (check(type)) return advance();

	error(peek(), message);
}

ExpressionNode* Parser::parse() {
	return expression();


}