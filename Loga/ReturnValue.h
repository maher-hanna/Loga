#pragma once
#include <exception>
#include <string>
#include <variant>
#include "LogaCallable.h"

class ReturnValue : public std::exception
{
public:
	ReturnValue() :value(nullptr), message("") {}
	ReturnValue(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value) :value(value), message("") {}
	ReturnValue(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value,
		const char* message) :value(value), message(message) {
	}
	ReturnValue(std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value,
		std::string message) :value(value), message(message) {
	}
	virtual const char* what() const throw()
	{
		return "Return value exception";
	}

	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> value;

private:
	std::string message;
};