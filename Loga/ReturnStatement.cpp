#include "ReturnStatement.h"

void ReturnStatement::accept(StatementVisitor& visitor)
{
	return visitor.visitReturnStatement(*this);

}
