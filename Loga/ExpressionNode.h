#pragma once 
#include <string>
#include "ExpressionVisitor.h"

class ExpressionNode {
public:
	ExpressionNode() {}
	virtual std::string accept(ExpressionVisitor& visitor) = 0;
	virtual ~ExpressionNode() {}

};