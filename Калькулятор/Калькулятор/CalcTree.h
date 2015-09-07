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
public:
	CalcTree(const string &);
	~CalcTree();
	int result();
private:
	SyntaxCalcTree * syntaxCalcTree;	// синтаксический анализ дерева вычислений
	CalcTree();							// запрещаем конструктор по умолчанию
};

#endif