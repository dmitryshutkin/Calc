#ifndef PARSING
#define PARSING

#include "Main.h"
#include "LexicalStruct.h"

#pragma once
#include <string>





class Parsing
{

public:

	double operator() (const std::string &);

	double operator() (const char * const);


private:

	// Функции рекурсивной обработки выражения
	// Цепочка вызовов:
	// Сумма -> произведение -> степень -> унарный оператор -> функция -> выражение в скобках -> число

	double expr_sum_mult_pow_sign_func_brackets_atom(LexicalStruct &);   // Сумма + произведение + степень + унарный оператор + функция + выражение в скобках + число
	double expr_mult_pow_sign_func_brackets_atom(LexicalStruct &);       // Произведение + степень + унарный оператор + функция + выражение в скобках + число
	double expr_pow_sign_func_brackets_atom(LexicalStruct &);            // Степень + унарный оператор + функция + выражение в скобках + число
	double expr_sign_func_brackets_atom(LexicalStruct &);                // Унарный оператор + функция + выражение в скобках + число
	double expr_func_brackets_atom(LexicalStruct &);                     // Функция + выражение в скобках + число
	double expr_brackets_atom(LexicalStruct &);                          // Выражение в скобках + число
	double expr_atom(LexicalStruct &);                                   // Число --- выход из рекурсивного спуска по цепочке вызовов


};

extern Parsing parse;

#endif