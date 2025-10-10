#pragma once

#include <string>
#include "TokenType.h"

class Token {
public:
    TokenType type;
    std::string lexeme;
    std::string literal;
    int line;

    Token(TokenType type, std::string lexeme, std::string literal, int line) {
        this->type = type;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;
    }

    std::string toString() {
        return enumToString(type) + " " + lexeme + " " + literal;
    }
};

