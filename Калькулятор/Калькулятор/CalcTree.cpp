#include "CalcTree.h"
#include <iostream>

using namespace std;



CalcTree::CalcTree(string str)
{
	// ����������� ������. �������� ������ �� ������ ������
	vector<string> tokens;
	string token("");
	int i = 0;
	while (i < str.size())
	{
		while ((i < str.size()) && (isdigit((unsigned char)str[i])))  // ��������� ��������� ����������, ����� �������� ����� i �� ������� ���������� ��������!
			token += str[i++];
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
	
	// ���������� ����������
	cout << "������ ������:" << endl;
	for (int i = 0; i < tokens.size(); ++i)
		cout << tokens[i] << endl;

	// ������� ������ ���������� �� ������� ����������� ������
	syntaxCalcTree = new SyntaxCalcTree(tokens);

} // ! CalcTree::CalcTree(string)



CalcTree::~CalcTree()
{
	delete syntaxCalcTree;
} // ! CalcTree::~CalcTree()



int CalcTree::result()
{
	return syntaxCalcTree->result();
} // ! CalcTree::result()
