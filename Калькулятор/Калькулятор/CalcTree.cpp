#include "CalcTree.h"
#include "CalcOperation.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int CalcTree::result()
{
	return op(a, b);
}

CalcTree::CalcTree(string str)
{
	// ����������� ������. �������� ������ �� ������ ������
	vector<string> tokens;
	string token("");
	int i = 0;
	while ( i < str.size() )
	{
		while ( (i < str.size()) && (isdigit(str[i])) )  // ��������� ��������� ����������
		{
			token += str[i];
			++i;
		}
		if (token != "")
		{
			tokens.push_back(token);
			token = "";
		}
		if (str[i] == '+')
			tokens.push_back("+");
		if (str[i] == '-')
			tokens.push_back("-");
		if (str[i] == '*')
			tokens.push_back("*");
		if (str[i] == '/')
			tokens.push_back("/");
		if (str[i] == '(')
			tokens.push_back("(");
		if (str[i] == ')')
			tokens.push_back(")");
		++i;
	}

	// �������� ������
	cout << "������ ������:" << endl;
	for (int i = 0; i < tokens.size(); ++i)
		cout << tokens[i] << endl;

	// �������������� ������. �������� ������ � ������������ � ����������� ��������
	a = b = nullptr;  // ��������
}


