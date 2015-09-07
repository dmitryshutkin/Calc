#ifndef SYNTAXCALCTREE
#define SYNTAXCALCTREE
#pragma once

#include "MainDefinitions.h"
#include "SyntaxCalcOperation.h"
#include <string>
#include <vector>

using std::string;
using std::vector;



class SyntaxCalcTree
{
private:
	SyntaxCalcTree	* a, * b;
	SyntaxCalcOperation op;
public:
	int result();
	SyntaxCalcTree(const vector<string> &);
};

#endif