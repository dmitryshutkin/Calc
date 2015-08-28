#include "CalculationTree.h"


int CalculationTree::result()
{
	return calcOp.result(a, b);
}


int CalcOperation::result(CalculationTree * a, CalculationTree * b)
{
	return 0;
}

int CalcOperation::operator()(CalculationTree * a, CalculationTree * b)
{
	return 0;
}