#include "IfStatement.h"

void IfStatement::accept(StatementVisitor& visitor)
{
	visitor.visitIfStatement(*this);

}
