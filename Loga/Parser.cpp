#include <memory>
#include "Parser.h"
#include "BinaryNode.h"
#include "TokenType.h"
#include "UnaryNode.h"
#include "LiteralNode.h"
#include "GroupingNode.h"
#include "VariableNode.h"
#include "AssignNode.h"
#include "Errors.h"
#include "PrintStatement.h"
#include "ExpressionStatement.h"
#include "VariableStatement.h"
#include "BlockStatement.h"
#include "ParseError.h"

Expression* Parser::equality() {
	Expression* expr = comparison();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::BANG_EQUAL);
	arr.push_back(TokenType::EQUAL_EQUAL);

	while (match(arr)) {
		Token opr = previous();
		Expression* right =
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


Expression* Parser::term() {
	Expression* expr = factor();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::MINUS);
	arr.push_back(TokenType::PLUS);

	while (match(arr)) {
		Token opr = previous();
		Expression* right = factor();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;

}

Expression* Parser::factor() {
	Expression* expr = unary();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::SLASH);
	arr.push_back(TokenType::STAR);

	while (match(arr)) {
		Token opr = previous();
		Expression* right = unary();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;

}

Expression* Parser::unary() {
	std::vector<TokenType> arr;
	arr.push_back(TokenType::BANG);
	arr.push_back(TokenType::MINUS);

	if (match(arr)) {
		Token opr = previous();
		Expression* right = unary();
		return new UnaryNode(opr, right);
	}

	return primary();

}

Expression* Parser::primary() {
	std::vector<TokenType> arr;
	arr.push_back(TokenType::BANG);

	if (match({ TokenType::FALSE })) return new LiteralNode("false");
	if (match({ TokenType::TRUE })) return new LiteralNode("true");
	if (match({ TokenType::NIL })) return new LiteralNode("null");

	if (match({ TokenType::NUMBER, TokenType::STRING })) {
		return new LiteralNode(previous().literal);
	}
	if (match({ TokenType::IDENTIFIER })) {
		return new VariableNode(previous());
	}

	if (match({ TokenType::LEFT_PAREN })) {
		Expression* expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return new GroupingNode(expr);
	}
	error(peek(), "Expect expression.");
	return nullptr;


}

Expression* Parser::assignment()
{
	Expression * expr = equality();

	if (match({ TokenType::EQUAL })) {
		Token equals = previous();
		Expression * value = assignment();
		
		if (dynamic_cast<VariableNode*>(expr)) {
			
			Token name = (dynamic_cast<VariableNode*>(expr))->name;
			return new AssignNode(name, value);
		}

		error(equals, "Invalid assignment target.");
	}

	return expr;
}

Statement * Parser::statement()
{
	if (match({ TokenType::PRINT })) return printStatement();
	if (match({ TokenType::LEFT_BRACE })) return new BlockStatement(block());

	return expressionStatement();
}

Statement * Parser::printStatement()
{
	Expression *value = expression();
	consume(TokenType::SEMICOLON, "Expect ';' after value.");
	return new PrintStatement(value);
}

Statement * Parser::expressionStatement()
{
	Expression*  expr = expression();
	consume(TokenType::SEMICOLON, "Expect ';' after expression.");
	return new ExpressionStatement(expr);
}

Statement* Parser::declaration()
{

		try {
			if (match({ TokenType::VAR })) return varDeclaration();

			return statement();
		}
		catch (ParseError &error) {
			synchronize();
			return nullptr;
		}
	
}

Statement* Parser::varDeclaration()
{
	Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

	Expression * initializer = nullptr;
	if (match({ TokenType::EQUAL })) {
		initializer = expression();
	}

	consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
	return new VariableStatement(name, initializer);
}

std::vector<Statement*> Parser::block()
{
	std::vector<Statement*> statements;

	while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
		statements.push_back(declaration());
	}

	consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
	return statements;
}

Expression* Parser::comparison() {
	Expression* expr = term();
	std::vector<TokenType> arr;
	arr.push_back(TokenType::GREATER);
	arr.push_back(TokenType::GREATER_EQUAL);
	arr.push_back(TokenType::LESS);
	arr.push_back(TokenType::LESS_EQUAL);

	while (match(arr)) {
		Token opr = previous();
		Expression* right = term();
		expr = new BinaryNode(expr, opr, right);
	}

	return expr;
}

Token Parser::consume(TokenType type, std::string message) {
	if (check(type)) return advance();

	error(peek(), message);
	synchronize();
	return Token();
}

void Parser::synchronize() {
	advance();

	while (!isAtEnd()) {
		if (previous().type == TokenType::SEMICOLON) return;

		switch (peek().type) {
		case TokenType::CLASS:
		case TokenType::FUN:
		case TokenType::VAR:
		case TokenType::FOR:
		case TokenType::IF:
		case TokenType::WHILE:
		case TokenType::PRINT:
		case TokenType::RETURN:
			return;
		default:
			break;
		}

		advance();
	}
}

std::vector<Statement*> Parser::parse() {
	std::vector<Statement*> statements;
	while (!isAtEnd()) {
		statements.push_back(declaration());
	}

	return statements;


}