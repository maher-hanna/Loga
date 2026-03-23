#include "PrintStatement.h"

void PrintStatement::accept(StatementVisitor& visitor)
{
	return visitor.visitPrintStatement(*this);

}
