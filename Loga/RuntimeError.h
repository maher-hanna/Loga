#pragma once
#include <exception>
#include <string>
#include "Token.h"

class RuntimeError : public std::exception
{
public:
	RuntimeError() :opr(), message("") {}
	RuntimeError(Token opr,
		const char* message) :opr(opr), message(message) {
	}
	RuntimeError(Token opr,
		std::string message) :opr(opr), message(message) {
	}
	virtual const char* what() const throw()
	{
		return "Runtime error happened";
	}
	Token opr;

private:
	std::string message;
};