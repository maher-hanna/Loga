#include "VariableStatement.h"

void VariableStatement::accept(StatementVisitor& visitor)
{
	visitor.visitVariableStatement(*this);

}
