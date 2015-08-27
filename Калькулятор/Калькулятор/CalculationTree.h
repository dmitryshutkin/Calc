#ifndef CALCULATIONTREE
#define CALCULATIONTREE

#pragma once

#include "CalcOperation.h"
#include <string>


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