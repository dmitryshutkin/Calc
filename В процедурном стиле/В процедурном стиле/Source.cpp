/* ���������������� ��������� ��� �����������. */
#include <cstdlib>
#include <cctype>
//#include <cstdio>
#include <iostream>
#include <cstring>
#include <locale>
#include "Parsing.h"

using namespace std;



char * str;


int main(void)
{
	setlocale(LC_CTYPE, "");
	
	//double answer;
	//char * p;

	//p = (char *)malloc(1000);
	//if (!p)
	//{
	//	printf("������ ��� ��������� ������.\n");
	//	exit(1);
	//}

	//// ��������� ��������� �� ����� ������ ������
	//do
	//{
	//	str = p;
	//	printf(">> ");
	//	gets_s(str, 1000);
	//	if (!*str) 
	//		break;
	//	answer = parse(str);
	//	printf(">> %.2f\n", answer);
	//} while (*p);

	char * str = new char[1000];

	for (;;) {		// "forever"
		cout << ">> ";
		cin.getline(str, 1000);
		if (!*str)
			break;
		cout << ">>" << parse(str) << endl;
	} // for

	delete[] str;
	// �����
	return 0;
}