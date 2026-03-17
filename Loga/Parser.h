#pragma once

#include <vector>
#include "Token.h"
#include "ExpressionNode.h"
#include "ParseError.h"
#include "Errors.h"

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


    bool match(const std::vector<TokenType> &types);

    ExpressionNode * comparison();

    ExpressionNode* equality();

    ExpressionNode* expression() {
        return equality();
    }
    ExpressionNode* term();
    ExpressionNode* factor();
    ExpressionNode* unary();
    ExpressionNode* primary();


public:

    Parser(std::vector<Token> tokens) {
        this->tokens = tokens;
       
    }

    ExpressionNode* parse();

};