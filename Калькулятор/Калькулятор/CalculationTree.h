#ifndef CALCULATIONTREE
#define CALCULATIONTREE
#pragma once
#include <string>

class CalculationTree;

class CalcOperation
{
private:
	int origin;
public:
	CalcOperation() : origin(0) { };
	int operator() (CalculationTree, CalculationTree);
};

class CalculationTree
{
private:
	CalculationTree	* a, * b;
	CalcOperation calcOp;
public:
	int result();
	CalculationTree(std::string str) : a(nullptr), b(nullptr) { };
};

#endif