#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	// Русская кодировка
	setlocale(LC_CTYPE, "");
	// Получить сторку для парсинга
	string str = "";
	cout << "Введите строку: ";
	cin >> str;
	cout << "Вы ввели строку: " << str << endl;
	// Парсинг

	// Возврат управления ОС
	cout << "Тестовая заглушка. Код возврата -1" << endl;
	cin.get(); cin.get();
	return -1;
}