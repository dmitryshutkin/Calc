#include <iostream>
#include <string>
#include "CalcTree.h"


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

	// Парсинг и вычисление
	CalcTree calcTree(str);  // Конструируем дерево вычислений

	// Вывод результата
	cout << "\nРезультат:" << calcTree.result() << endl;
	cout << "Тестовая версия - код возврата -1" << endl;
	cin.get(); cin.get();
	
	// Возврат управления ОС
	return -1;
}