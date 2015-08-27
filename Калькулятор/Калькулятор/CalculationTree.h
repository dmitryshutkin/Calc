#pragma once
#include "Operation.h"

class CalculationTree
{
private:
	CalculationTree * a;
	Operation op;
	CalculationTree * b;
	CalculationTree(string);
public:
	int result();
};