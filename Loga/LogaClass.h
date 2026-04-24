#pragma once

#include <string>
#include <vector>
#include "LogaCallable.h"
#include "Interpreter.h"
#include "Value.h"
#include "LogaInstance.h"
#include "LogaFunction.h"

class LogaClass: public LogaCallable {
public:
	LogaClass(std::string name) : name(name) {	}
	LogaClass(std::string name,std::unordered_map<std::string, LogaFunction*> methods) : name(name), methods(methods) {	}

	Value call(Interpreter* interpreter,
		std::vector<Value> arguments) override {
		LogaInstance* instance = new LogaInstance(this);
		LogaFunction* initializer = findMethod("init");
		if (initializer != nullptr) {
			initializer->bind(instance)->call(interpreter, arguments);
		}
		return instance;
	}


	int getNumberOfArguments() override{ 
		LogaFunction* initializer = findMethod("init");
		if (initializer == nullptr) return 0;
		return initializer->getNumberOfArguments();
	}

	std::string toString() override {
		return "<class " + name + ">";
	}
	LogaFunction* findMethod(std::string name) {
		if (methods.contains(name)) {
			return methods[name];
		}

		return nullptr;
	}


	virtual ~LogaClass() {} // Provide a definition

private:
	std::string name;
	std::unordered_map<std::string, LogaFunction*> methods;


};