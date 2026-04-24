#include "LogaFunction.h"
#include "Environment.h"
#include "Interpreter.h"
#include "ReturnValue.h"
#include "Value.h"

Value LogaFunction::call(Interpreter* interpreter, std::vector<Value> arguments)
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
		if (isInitializer) return closure->getAt(0, "this");

		return returnValue.value;
	}
	if (isInitializer) return closure->getAt(0, "this");

	return nullptr;
}

LogaFunction* LogaFunction::bind(LogaInstance* instance)
{
	Environment* environment = new Environment(closure);
	environment->define("this", instance);
	return new LogaFunction(declaration, environment,isInitializer);
}
