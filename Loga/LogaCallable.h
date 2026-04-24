#pragma once
#include <vector>
#include "Value.h"

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
	virtual Value call(Interpreter* interpreter,
		std::vector<Value> arguments) = 0;


	virtual int getNumberOfArguments() { return numberOfArguments; }
	virtual std::string toString() {
		return "<callable>";
	}
	virtual ~LogaCallable() {} // Provide a definition

protected:
	int numberOfArguments = 0;


};


class EmptyFunctionCall : public LogaCallable {
public:
	Value call(Interpreter* interpreter,
		std::vector<Value> arguments) override {
		return nullptr;
	}


};