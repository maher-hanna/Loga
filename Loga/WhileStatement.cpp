#include "WhileStatement.h"

void WhileStatement::accept(StatementVisitor& visitor)
{
	visitor.visitWhileStatement(*this);

}
