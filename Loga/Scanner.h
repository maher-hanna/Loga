#pragma once

#include <string>
#include <vector>
#include <map>
#include "Token.h"
#include "Errors.h"
#include "LogaCallable.h"

class Scanner {
private :
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;
    std::map<std::string, TokenType> keywords;
public:

    Scanner(std::string source) {
        this->source = source;
        keywords["and"] =  TokenType::AND;
        keywords["class"] = TokenType::CLASS;
        keywords["else"] = TokenType::ELSE;
        keywords["false"] = TokenType::FALSE;
        keywords["for"] = TokenType::FOR;
        keywords["fun"] = TokenType::FUN;
        keywords["if"] = TokenType::IF;
        keywords["nil"] = TokenType::NIL;
        keywords["or"] = TokenType::OR;
        keywords["print"] = TokenType::PRINT;
        keywords["return"] = TokenType::RETURN;
        keywords["super"] = TokenType::SUPER;
        keywords["this"] = TokenType::THIS;
        keywords["true"] = TokenType::TRUE;
        keywords["var"] = TokenType::VAR;
        keywords["while"] = TokenType::WHILE;
    }

    std::vector<Token> scanTokens() {
        while (!isAtEnd()) {
            // We are at the beginning of the next lexeme.
            start = current;
            scanToken();
        }

        tokens.push_back(Token(TokenType::END_OF_FILE, "", "", line));
        return tokens;

    }

    bool isAtEnd() {
        return current >= source.length();
    }

    void scanToken();

    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
    }

    void identifier() {
        while (isAlphaNumeric(peek()))
            advance();

        std::string text = source.substr(start, current - start);

        if (keywords.find(text) != keywords.end())
            addToken(keywords[text]);
        else
            addToken(TokenType::IDENTIFIER);
     
    }

    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    void number() {
        while (isDigit(peek()))
            advance();

        // Look for a fractional part.
        if (peek() == '.' && isDigit(peekNext())) {
            // Consume the "."
            advance();

            while (isDigit(peek()))
                advance();
        }
		std::string numberString = source.substr(start, current - start);
		double numberValue = std::stod(numberString);

        addToken(TokenType::NUMBER,
            numberValue);
    }

    char peekNext() {
        if (current + 1 >= source.length())
            return '\0';
        return source.at(current + 1);
    }

    void string() {
        while (peek() != '\"' && !isAtEnd()) {
            if (peek() == '\n')
                line++;
            advance();
        }

        if (isAtEnd()) {
            error(line, "Unterminated string.");
            return;
        }

        // The closing ".
        advance();

        // Trim the surrounding quotes.
        std::string value = source.substr(start + 1, (current - start) - 2);
        addToken(TokenType::STRING, value);
    }

    bool match(char expected) {
        if (isAtEnd())
            return false;
        if (source.at(current) != expected)
            return false;

        current++;
        return true;
    }

    char advance() {
        return source.at(current++);
    }

    char peek() {
        if (isAtEnd())
            return '\0';
        return source.at(current);
    }

    void addToken(TokenType type) {
        addToken(type, "");
    }

    void addToken(TokenType type, std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> literal) {
        std::string text = source.substr(start, current - start);
        tokens.push_back(Token(type, text, literal, line));
    }
};