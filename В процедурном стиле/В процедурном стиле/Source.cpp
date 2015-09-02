#include <iostream>
#include <string>
#include <locale>

#include "Parsing.h"

using namespace std;

const char bell = '\a';



int main(void)
{
	// setlocale(LC_CTYPE, "");
	setlocale(LC_ALL, "Russian");
	string str;

	cout << bell;
	while((cout << " >>  ") && getline(cin, str))
	{	
		if (str.empty())
			break;
		else if (str == "?")
		{
			cout << bell << " =>     Команды интерпретатора:\n =>       \"cls\" - очистка консоли\n =>       Enter - завершение работы" << endl << endl;
			continue;
		}
		else if (str == "cls")
		{
			if (system("cls"))
				system("clear");
			cout << bell;
			continue;
		}
		cout << bell << " =>  " << parse(str.c_str()) << endl << endl;		
	} 
	cout << bell;
	return 0;
}