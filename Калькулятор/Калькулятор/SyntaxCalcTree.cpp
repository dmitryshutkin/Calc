#include "SyntaxCalcTree.h"
#include <iostream>

using namespace std;



int SyntaxCalcTree::result()
{
	return op(a, b);
} // ! SyntaxCalcTree::result()



SyntaxCalcTree::SyntaxCalcTree(const vector<string> & tokens)
{
	// �������������� ������. �������� ������ ���������� �� ������� ������

	// ��������� ������ ������ �� ����, ������� � ������� ���������, ������������ ���������� ����
	
	a = b = nullptr;  // ��������

} // ! SyntaxCalcTree::SyntaxCalcTree(const vector<string> & )


