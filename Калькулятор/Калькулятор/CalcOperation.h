#ifndef CALCOPERATION
#define CALCOPERATION

#pragma once


extern class CalculationTree;

class CalcOperation
{
private:
	int origin;
public:
	CalcOperation() : origin(0) { };
	int operator() (CalculationTree, CalculationTree);
	
};

#endif