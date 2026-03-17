#pragma once
#include <string>
#include "Token.h"

extern bool hadError;

void report(int line, std::string where, std::string message);

void error(int line, std::string message);
void error(Token token, std::string message);