#pragma once

#include <string>
#include <unordered_map>
#include "Value.h"
#include "Token.h"

class LogaClass;

class LogaInstance {
public:
	LogaInstance(LogaClass* klass) : klass(klass) {}
	std::string toString();
	Value get(Token name);
	void set(Token name, Value value);
private:
	LogaClass* klass;
	std::unordered_map<std::string, Value> fields;

};