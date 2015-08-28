#include "CalculationTree.h"
#include "CalcOperation.h"

int CalculationTree::result()
{
	return calcOp(a, b);
}
