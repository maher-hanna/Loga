#include "LogaFunction.h"
#include "Environment.h"
#include "Interpreter.h"
#include "ReturnValue.h"

std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> LogaFunction::call(Interpreter* interpreter, std::vector<std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> arguments)
{
	Environment* environment = new Environment(closure);
	for (int i = 0; i < declaration.params.size(); i++) {
		environment->define(declaration.params.at(i).lexeme,
			arguments.at(i));
	}

	try {
		interpreter->executeBlock(declaration.body, environment);
	}
	catch (ReturnValue& returnValue) {
		return returnValue.value;
	}
	return nullptr;
}
