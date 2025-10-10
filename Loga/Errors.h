#pragma once
#include <string>

extern bool hadError;

void report(int line, std::string where, std::string message);

void error(int line, std::string message);