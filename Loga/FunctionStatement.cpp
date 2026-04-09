#include "FunctionStatement.h"

void FunctionStatement::accept(StatementVisitor& visitor)
{
	visitor.visitFunctionStatement(*this);

}
