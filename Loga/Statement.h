#pragma once
#include "StatementVisitor.h"

class Statement 
{
public:
	virtual void accept(StatementVisitor& visitor) = 0;

private:

};

