#pragma once
#include <vector>
#include <variant>
#include <string>

class BinaryNode;
class GroupingNode;
class LiteralNode;
class UnaryNode;
class VariableNode;
class AssignNode;
class LogicalNode;
class CallNode;
class Interpreter;


class LogaCallable {
public:
	virtual std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> call(Interpreter* interpreter,
		std::vector<std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> arguments) = 0;


	virtual int getNumberOfArguments() { return numberOfArguments; }
	virtual ~LogaCallable() {} // Provide a definition
protected:
	int numberOfArguments = 0;


};


class EmptyFunctionCall : public LogaCallable {
public:
	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> call(Interpreter* interpreter,
		std::vector<std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> arguments) override {
		return nullptr;
	}


};