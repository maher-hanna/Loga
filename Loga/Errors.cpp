#include "Errors.h"
#include <iostream>

bool hadError;
bool hadRuntimeError;

void report(int line, std::string where, std::string message) {
	std::cerr << "[line " << line << "] Error" << where << ": " << message;
	hadError = true;
}
void report(RuntimeError error) {
	std::cerr << error.what() << "\n";
}

void error(int line, std::string message) {
	report(line, "", message);
}

void error(Token token, std::string message) {
	if (token.type == TokenType::END_OF_FILE) {
		report(token.line, " at end", message);
	}
	else {
		report(token.line, " at '" + token.lexeme + "'", message);
	}
}

void error(RuntimeError &error)
{
	report(error);

	
	hadRuntimeError = true;

}
