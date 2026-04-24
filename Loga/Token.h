#pragma once

#include <string>
#include <variant>
#include "LogaCallable.h"
#include "TokenType.h"
#include "Value.h"

class Token {
public:
    TokenType type;
    std::string lexeme;
    Value literal;
    int line;

    Token(TokenType type, std::string lexeme, Value literal, int line) {
        this->type = type;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;
    }
    Token():line(1),type(TokenType::END_OF_FILE) {};

    std::string toString() {
        return enumToString(type) + " " + lexeme + " " + stringify(literal);
    }
private:


    std::string stringify(Value const& value) {
      
        if (double const* pval = std::get_if<double>(&value))
            return std::to_string(*pval);
        if (int const* pval = std::get_if<int>(&value))
            return std::to_string(*pval);
        if (bool const* pval = std::get_if<bool>(&value))
            return std::to_string(*pval);

        if (std::holds_alternative<nullptr_t>(value))
            return "nil";


        return std::get<std::string>(value);
    }

};

