#include <iostream>
#include <string>
#include <locale>

#include "Parsing.h"

using namespace std;

// #define BELL ""
#define BELL '\a'


int main(void)
{
	setlocale(LC_ALL, "Russian");
	string str;

	cout << BELL;
	while ((cout << " >>  ") && getline(cin, str))
	{
		if (str.empty())
			break;
		else if (str == "?")
		{
			cout << BELL << " =>     Команды интерпретатора:\n =>       \"cls\" - очистка консоли\n =>       Enter - завершение работы" << '\n' << endl;
			continue;
		}
		else if (str == "cls")
		{
			if (system("cls"))
				system("clear");
			cout << BELL;
			continue;
		}
		cout << BELL << " =>  " << parse(str) << '\n' << endl;
	}
	cout << BELL;
	return 0;
}