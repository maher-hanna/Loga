#pragma once

#include "LogaCallable.h"
#include "FunctionStatement.h"

class LogaFunction : public LogaCallable {
public:
	LogaFunction(FunctionStatement& declaration, Environment* closure) : declaration(declaration), closure(closure) {
		this->numberOfArguments = (int)declaration.params.size();
	}

	virtual std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> call(Interpreter* interpreter,
		std::vector<std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> arguments) override;

	int getNumberOfArguments() override{
		return (int)declaration.params.size();
	}

	std::string toString(){
		return "<fn " + declaration.name.lexeme + ">";
	}
private:
	FunctionStatement declaration;
	Environment* closure;


};