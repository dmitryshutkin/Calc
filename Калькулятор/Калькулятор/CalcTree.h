#ifndef CALCTREE
#define CALCTREE

#pragma once

#include "CalcOperation.h"
#include <string>


class CalcTree
{
private:
	CalcTree	* a, * b;
	CalcOperation op;
public:
	int result();
	CalcTree(std::string str);
};

#endif