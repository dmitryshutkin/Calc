#ifndef CALCTREE
#define CALCTREE
#pragma once

#include "MainDefinitions.h"
#include "SyntaxCalcTree.h"
#include <string>
#include <vector>

using std::string;



class CalcTree
{
	SyntaxCalcTree * syntaxCalcTree;  // синтаксический анализ дерева вычислений
public:
	CalcTree(const string &);
	~CalcTree();
	int result();
};

#endif