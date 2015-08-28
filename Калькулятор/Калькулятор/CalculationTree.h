#ifndef CALCULATIONTREE
#define CALCULATIONTREE
#pragma once
#include <string>

class CalculationTree;

class CalcOperation
{
public:
	int result(CalculationTree *, CalculationTree *);
	int operator() (CalculationTree *, CalculationTree *);
};

class CalculationTree
{
private:
	CalculationTree	*a, *b;
	CalcOperation calcOp;
public:
	int result();
	CalculationTree(std::string str) : a(nullptr), b(nullptr) { };
};

#endif