#include "ClassStatement.h"

void ClassStatement::accept(StatementVisitor& visitor)
{
	visitor.visitClassStatement(*this);
}
