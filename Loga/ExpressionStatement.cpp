#include "ExpressionStatement.h"

void ExpressionStatement::accept(StatementVisitor& visitor)
{
	visitor.visitExpressionStatement(*this);

}
