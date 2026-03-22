#pragma once
#include <string>
#include "ExpressionNode.h"
#include "Token.h"
#include "ExpressionVisitor.h"


class BinaryNode : public ExpressionNode
{
public:
	BinaryNode() :left(nullptr), binaryOperator(), right(nullptr) {}
	BinaryNode(ExpressionNode* left, Token binaryOperator, ExpressionNode* right) :left(left), binaryOperator(binaryOperator), right(right) {};
	ExpressionNode* left;
	Token binaryOperator;
	ExpressionNode* right;
	std::variant<double, int, std::string, std::nullptr_t, bool> accept(ExpressionVisitor& visitor) override;

};

