#include <iostream>

using namespace std;

int main()
{
	char * expr_rest = new char[255];
	strcpy_s(expr_rest, 255, "test");
	cout << expr_rest << endl;
	cin.get();

	delete[] expr_rest;
	return 0;

}