#include "CalculationTree.h"
#include "CalcOperation.h"

int CalculationTree::result()
{
	return calcOp.operator()(0,0);
}
