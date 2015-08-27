#include <iostream>
#include <string>
#include "CalculationTree.h"


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
	CalculationTree calc(str);  // Конструируем дерево вычислений

	// Вывод результата
	cout << "\nРезультат:" << calc.result() << endl;

	// Возврат управления ОС
	cout << "Тестовая заглушка. Код возврата -1" << endl;
	cin.get(); cin.get();
	return -1;
}