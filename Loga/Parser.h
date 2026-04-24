#pragma once

#include <vector>
#include "Token.h"
#include "Expression.h"
#include "Statement.h"

class Parser {
private:
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;

    bool isAtEnd() {
        return peek().type == TokenType::END_OF_FILE;
    }

    Token peek() {
        return tokens[current];
    }

    Token previous() {
        return tokens[current - 1];
    }

    bool check(TokenType type) {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    Token advance() {
        if (!isAtEnd()) current++;
        return previous();
    }



    Token consume(TokenType type, std::string message);
    void synchronize();


    bool match(const std::vector<TokenType> &types);

    Expression * comparison();

    Expression* equality();

    Expression* expression() {
        return assignment();
    }
    Expression* term();
    Expression* factor();
    Expression* unary();
    Expression* primary();
    Expression* assignment();
    Expression* orExpression();
    Expression* andExpression();
    Expression* call();
    Expression* finishCall(Expression* callee);
	Statement * statement();
	Statement * printStatement();
	Statement * expressionStatement();
	Statement * ifStatement();
	Statement * whileStatement();
	Statement * forStatement();
	Statement * returnStatement();
    Statement* declaration();
    Statement* varDeclaration();
    Statement* function(std::string kind);
    Statement* classDeclaration();
    std::vector<Statement*> block();

public:

    Parser(std::vector<Token> tokens) {
        this->tokens = tokens;
       
    }

    std::vector<Statement*> parse();

};