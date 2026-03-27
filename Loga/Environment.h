#pragma once

#include <map>
#include <string>
#include <variant>
#include "Token.h"
#include "RuntimeError.h"


class Environment
{
public:
	Environment() :values() {}

	void define(std::string name, std::variant<double, int, std::string, std::nullptr_t, bool> value) {
		values[name]= value;
	}
	std::variant<double, int, std::string, std::nullptr_t, bool> get(Token name) {
		if (values.contains(name.lexeme)) {
			return values[name.lexeme];
		}
		std::string errorMessage = "Undefined variable \'" + name.lexeme + "\'.";

		throw RuntimeError(name,
			errorMessage.c_str());
	}
	std::map<std::string, std::variant<double, int, std::string, std::nullptr_t, bool>> values;

};

