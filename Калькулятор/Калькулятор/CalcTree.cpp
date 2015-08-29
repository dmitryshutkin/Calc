#include "CalcTree.h"
#include <iostream>

using namespace std;



CalcTree::CalcTree(string str)
{
	// Лексический анализ. Разбивка строки на список лексем
	vector<string> tokens;
	string token("");
	int i = 0;
	while (i < str.size())
	{
		while ((i < str.size()) && (isdigit((unsigned char)str[i])))  // Проверить ленивость вычислений, чтобы избежать выход i за пределы допустимых значений!
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
	
	// Отладочная информация
	cout << "Список лексем:" << endl;
	for (int i = 0; i < tokens.size(); ++i)
		cout << tokens[i] << endl;

	// Создаем дерево вычислений из массива лексических единиц
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
