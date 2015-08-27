#ifndef CALCOPERATION
#define CALCOPERATION
#pragma once
//#include "CalculationTree.h"

class CalcOperation
{
private:
	int origin;
public:
	CalcOperation() : origin(0) { };
	int operator() (int, int);
	
};

#endif