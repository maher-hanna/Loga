#include "BlockStatement.h"

void BlockStatement::accept(StatementVisitor& visitor)
{
	visitor.visitBlockStatement(*this);

}
