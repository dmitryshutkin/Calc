﻿#include "MainDefinitions.h"
#include "CalcTree.h"
#include <iostream>
#include <string>
#include <locale>

using namespace std;



int main(void)
{
	// Русская кодировка
	setlocale(LC_CTYPE, "");

	// Получить сторку для парсинга
	string str = "15*2 + 2 - 5 + 8*(3 - 1)";
	cout << "Калькулятор" << endl << ">> ";
	// getline(cin,str);

	cout << "Строка: \"" << str << "\"" << endl;
	
	// Парсинг и вычисление
	CalcTree calcTree(str);  // Конструируем дерево вычислений

	// Вывод результата
	cout << endl << "Результат: " << calcTree.result() << endl;
	
	// Отладочная информация
	cout << "Тестовая версия - код возврата -1" << endl;

	// Пауза
	cin.get(); 
	
	// Возврат управления ОС
	return -1;  // Тестовая версия - код возврата -1
}