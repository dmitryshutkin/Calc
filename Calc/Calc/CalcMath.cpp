#define _USE_MATH_DEFINES 
#include <cmath>

#include "CalcMath.h"


double ctg(double x)
{
	return 1 / tan(x);
}



double arccos(double x)
{
	return M_PI_2 - asin(x);
}



double arcctg(double x)
{
	return M_PI_2 - atan(x);
}