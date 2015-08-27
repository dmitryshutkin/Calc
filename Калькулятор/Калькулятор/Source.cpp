#include <iostream>

using namespace std;

int main(void)
{
	setlocale(LC_CTYPE, "");
	cout << "Тестовая заглушка. Код возврата -1" << endl;
	cin.get();
	return -1;
}