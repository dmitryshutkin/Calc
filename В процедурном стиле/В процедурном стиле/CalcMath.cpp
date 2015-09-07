#define _USE_MATH_DEFINES 
#include <cmath>

#include "CalcMath.h"


double ctg(double x)
{
	return 1 / tan(x);	// заглушка
}



double arccos(double x)
{
	return M_PI / 2 - asin(x);	// заглушка
}



double arcctg(double x)
{
	return M_PI / 2 - atan(x);	// заглушка
}