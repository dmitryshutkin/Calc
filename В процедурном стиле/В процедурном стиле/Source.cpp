#include <iostream>
#include <string>
#include <locale>

#include "Parsing.h"

using namespace std;



int main(void)
{
	// setlocale(LC_CTYPE, "");
	setlocale(LC_ALL, "Russian");
	string str;

	cout << "\a";
	while((cout << " >>  ") && getline(cin, str))
	{	
		if (str.empty())
			break;
		else if (str == "?")
		{
			cout << "\a" << " =>     ������� ��������������:\n =>       \"cls\" - ������� �������\n =>       Enter - ���������� ������" << endl << endl;
			continue;
		}
		else if (str == "cls")
		{
			if (system("cls"))
				system("clear");
			cout << "\a";
			continue;
		}
		cout << "\a" << " =>  " << parse(str.c_str()) << endl << endl;		
	} 
	cout << "\a";
	return 0;
}