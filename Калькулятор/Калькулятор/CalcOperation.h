#ifndef CALCOPERATION
#define CALCOPERATION

#pragma once


extern class CalculationTree;

class CalcOperation
{
public:
	int operator() (CalculationTree, CalculationTree);
};

#endif