#include "LexicalStruct.h"

#ifdef DEBUG
	#include <iostream>
	#include <iomanip>
#endif



using namespace std;

LexicalStruct::LexicalStruct(const string & expr)
{
	// ����������� ������ ���������
	string tmp;
	for (int i = 0; i < expr.size(); ++i)
	{
		// �������
		if (isspace(expr[i]))
			continue;
		// �����
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
		// �������
		if (isalpha(expr[i]))
		{
			tmp = expr[i];
			++i;
			while ((i < expr.size()) && (isalpha(expr[i])))
				tmp += expr[i++];				
			tokens.push_back(Token(tmp, Token::function));
			tmp.clear();
		}
		// �����
		if ((i < expr.size()) && (strchr("+-*/^=()", expr[i])))
		{
			tmp = expr[i];
			tokens.push_back(Token(tmp, Token::delimiter));
			tmp.clear();
		}
	}
	// ��������� ��������� ������� ������� �� ������
	current = tokens.cbegin();
	#ifdef DEBUG
		cout << "����������� ������:" << endl;
		for (auto i = current; i < tokens.cend(); i++)
			cout << setw(7) << left << i->value << setw(5) << i->type << endl;
	#endif
}

void LexicalStruct::next()
{
	++current;
}
