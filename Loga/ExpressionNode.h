#pragma once 
#include <string>
#include "ExpressionVisitor.h"

class ExpressionNode {
public:
	ExpressionNode() {}
	virtual std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor) = 0;
	virtual ~ExpressionNode() {}

};