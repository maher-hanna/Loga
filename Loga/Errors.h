#pragma once
#include <string>
#include "RuntimeError.h"
#include "Token.h"

extern bool hadError;
extern bool hadRuntimeError;


void report(int line, std::string where, std::string message);
void report(RuntimeError error);


void error(int line, std::string message);
void error(Token token, std::string message);
void error(RuntimeError &error);