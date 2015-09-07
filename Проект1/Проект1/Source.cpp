#include <iostream>

using namespace std;


void f1(char * v)
{
	//strcpy_s(v, 10, "new");
	while (isdigit((unsigned char)(*v)))
		v++;		
	cout << v << endl;
}

void f1(int * v)
{
	*v = 5;
}

void main()
{
	char *myString = new char[100];
	strcpy_s(myString, 100, "1554 String");
	int *myInt = new int[3];
	f1(myString);
	f1(myInt);
	cout << myString << endl;
	cout << *myInt << endl;
	cin.get();
}