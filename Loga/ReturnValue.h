#pragma once
#include <exception>
#include <string>
#include "Value.h"

class ReturnValue : public std::exception
{
public:
	ReturnValue() :value(nullptr), message("") {}
	ReturnValue(Value value) :value(value), message("") {}
	ReturnValue(Value value,
		const char* message) :value(value), message(message) {
	}
	ReturnValue(Value value,
		std::string message) :value(value), message(message) {
	}
	virtual const char* what() const throw()
	{
		return "Return value exception";
	}

	Value value;

private:
	std::string message;
};