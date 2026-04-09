#pragma once

#include <map>
#include <string>
#include <variant>
#include "Token.h"
#include "RuntimeError.h"


class Environment
{
public:
	Environment(const Environment& other) : values(other.values), enclosing(other.enclosing) {	}
	Environment operator=(const Environment& other) {
		values = other.values;
		enclosing = other.enclosing;
		return *this;
	}
	Environment() :enclosing(nullptr) {}
	Environment(Environment* enclosing) : enclosing(enclosing) {}

	void define(std::string name, std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value) {
		values[name]= value;
	}

	void assign(Token name, std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value) {
		if (values.contains(name.lexeme)) {
			values[name.lexeme] = value;
			return;
		}
		if (enclosing != nullptr) {
			enclosing->assign(name, value);
			return;
		}
		std::string errorMessage = "Undefined variable '" + name.lexeme + "'.";

		throw RuntimeError(name,
			errorMessage.c_str());
	}

	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> get(Token name) {
		if (values.contains(name.lexeme)) {
			return values[name.lexeme];
		}
		if (enclosing != nullptr) return enclosing->get(name);

		std::string errorMessage = "Undefined variable \'" + name.lexeme + "\'.";

		throw RuntimeError(name,
			errorMessage.c_str());
	}

	std::map<std::string, std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> values;
	Environment* enclosing;

};

