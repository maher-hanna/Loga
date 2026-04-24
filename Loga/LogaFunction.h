#pragma once

#include "LogaCallable.h"
#include "FunctionStatement.h"
#include "Value.h"

class LogaFunction : public LogaCallable {
public:
	LogaFunction(FunctionStatement& declaration, Environment* closure, bool isInitializer = false) : declaration(declaration), closure(closure), isInitializer(isInitializer) {
		this->numberOfArguments = (int)declaration.params.size();
	}

	virtual Value call(Interpreter* interpreter,
		std::vector<Value> arguments) override;

	int getNumberOfArguments() override{
		return (int)declaration.params.size();
	}
	LogaFunction* bind(LogaInstance* instance);
	std::string toString() override {
		return "<fn " + declaration.name.lexeme + ">";
	}
private:
	FunctionStatement declaration;
	Environment* closure;
	bool isInitializer;


};