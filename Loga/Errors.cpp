#include "Errors.h"
#include <iostream>

bool hadError;

void report(int line, std::string where, std::string message) {
	std::cerr << "[line " << line << "] Error" << where << ": " << message;
	hadError = true;
}

void error(int line, std::string message) {
	report(line, "", message);
}