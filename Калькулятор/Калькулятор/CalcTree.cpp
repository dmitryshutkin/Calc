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
	// Лексический анализ. Разбивка строки на список лексем
	vector<string> tokens;
	string token("");
	int i = 0;
	while ( i < str.size() )
	{
		while ( (i < str.size()) && (isdigit(str[i])) )  // Проверить ленивость вычислений
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

	// Тестовая печать
	cout << "Список лексем:" << endl;
	for (int i = 0; i < tokens.size(); ++i)
		cout << tokens[i] << endl;

	// Синтаксический анализ. Создание дерева в соответствии с приоритетом операций
	a = b = nullptr;  // Заглушка
}


