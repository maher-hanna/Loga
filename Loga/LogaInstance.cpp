#include "LogaInstance.h"
#include "LogaClass.h"
#include "LogaFunction.h"

std::string LogaInstance::toString() {
	return "<instance of " + klass->toString() + ">";
}

Value LogaInstance::get(Token name)
{
    if (fields.contains(name.lexeme)) {
        return fields[name.lexeme];
    }
    LogaFunction* method = klass->findMethod(name.lexeme);
    if (method != nullptr) return method->bind(this);

    throw RuntimeError(name,
        "Undefined property '" + name.lexeme + "'.");
}

void LogaInstance::set(Token name, Value value)
{
    fields[name.lexeme] = value;
    return;
}
