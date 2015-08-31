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
	SyntaxCalcTree * syntaxCalcTree;	// �������������� ������ ������ ����������
	CalcTree();							// ��������� ����������� �� ���������
public:
	CalcTree(const string &);
	~CalcTree();
	int result();
};

#endif