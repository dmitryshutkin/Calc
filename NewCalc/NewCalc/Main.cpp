#include "Main.h"
#include "Parsing.h"

#include <iostream>
#include <string>


using namespace std;

int main(int argc, char * argv[])
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
			cout << BELL << " =>     Команды интерпретатора:\n"
				            " =>       cls - очистка консоли\n"
				            " =>       [Enter] - завершение работы\n" << endl;
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