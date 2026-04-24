#pragma once 
#include "ExpressionVisitor.h"
#include "Value.h"

class Expression {
public:
	Expression() {}
	virtual Value accept(ExpressionVisitor& visitor) = 0;
	virtual ~Expression() {}

};