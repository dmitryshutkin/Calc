#include "LexicalStruct.h"

#ifdef DEBUG
	#include <iostream>
	#include <iomanip>
#endif



using namespace std;

LexicalStruct::LexicalStruct(const string & expr)
{
	// Лексический анализ выражения
	string tmp;
	for (int i = 0; i < expr.size(); ++i)
	{
		// Пробелы
		if (isspace(expr[i]))
			continue;
		// Цифры
		if (isdigit(expr[i]))
		{
			tmp = expr[i];
			++i;
			while ((i < expr.size()) && ((isdigit(expr[i])) || expr[i] == ',' || expr[i] == '.'))
			{
				if (expr[i] == '.')
				{
					tmp += ',';
					++i;
					continue;
				}					
				tmp += expr[i++];
			}
			tokens.push_back(Token(tmp, Token::number));
			tmp.clear();
		}
		// Функции
		if (isalpha(expr[i]))
		{
			tmp = expr[i];
			++i;
			while ((i < expr.size()) && (isalpha(expr[i])))
				tmp += expr[i++];				
			tokens.push_back(Token(tmp, Token::function));
			tmp.clear();
		}
		// Знаки
		if ((i < expr.size()) && (strchr("+-*/^=()", expr[i])))
		{
			tmp = expr[i];
			tokens.push_back(Token(tmp, Token::delimiter));
			tmp.clear();
		}
	}
	// Установка указателя текущей лексемы на начало
	current = tokens.cbegin();
	#ifdef DEBUG
		cout << "Лексический анализ:" << endl;
		for (auto i = current; i < tokens.cend(); i++)
			cout << setw(7) << left << i->value << setw(5) << i->type << endl;
	#endif
}

void LexicalStruct::next()
{
	++current;
}
