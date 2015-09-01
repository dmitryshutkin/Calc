#include <iostream>
#include <string>
#include <locale>

#include "Parsing.h"

using namespace std;



int main(void)
{
	setlocale(LC_CTYPE, "");
	
	string str;

	while((cout << " >>  ") && getline(cin, str))
	{	
		if (str.empty())
			break;
		cout << " =>  " << parse(str.c_str()) << endl << endl;
	} 

	return 0;
}