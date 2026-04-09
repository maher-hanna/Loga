#pragma once 
#include <string>
#include "ExpressionVisitor.h"

class Expression {
public:
	Expression() {}
	virtual std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> accept(ExpressionVisitor& visitor) = 0;
	virtual ~Expression() {}

};