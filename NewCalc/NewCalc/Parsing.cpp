#include <string>
#include <map>
#include <vector>

#include "Parsing.h"
#include "C:\Users\Dmitry\Source\Repos\Calc\Calc\Calc\CalcMath.h"


Parsing parse;

using namespace std;

// Контейнер указателей на математические функции 
static map <string, double(*)(double)> mFunctions =
{
	{ "sin", sin },
	{ "cos", cos },
	{ "tg", tan },
	{ "ctg", ctg },
	{ "arcsin", asin },
	{ "arccos", arccos },
	{ "arctg", atan },
	{ "arcctg", arcctg },
	{ "sqrt", sqrt },
	{ "exp", exp },
	{ "ln", log },
	{ "lg", log10 },
	{ "abs", abs }
};



double Parsing::operator()(const char * const expr)
{	
	return operator()(string(expr));
}



double Parsing::operator()(const string & expr)
{
	#ifdef DEBUG
		// Проверка на наличие строки
		if (expr.empty())
			return nanf("");
		// Лексический анализ
		LexicalStruct lexicalStruct(expr);
		// Синтаксический анализ методом рекурсивного спуска
		double result = expr_sum_mult_pow_sign_func_brackets_atom(lexicalStruct);
		// Проверка полноты обработки
		if (lexicalStruct.current != lexicalStruct.tokens.cend())
			return nanf("");
		// Возврат
		return result;
	#endif
	#ifndef DEBUG
		// Лексический и синтаксический анализ
		return expr_sum_mult_pow_sign_func_brackets_atom(LexicalStruct(expr));
	#endif	
}



double Parsing::expr_sum_mult_pow_sign_func_brackets_atom(LexicalStruct & lexicalStruct)
{
	double result, temp;
	result = expr_mult_pow_sign_func_brackets_atom(lexicalStruct);
	string op;
	while (
			(lexicalStruct.current < lexicalStruct.tokens.cend()) && 
			(((op = lexicalStruct.current->value) == "+") || (op == "-"))
		  )
	{
		lexicalStruct.next();
		temp = expr_mult_pow_sign_func_brackets_atom(lexicalStruct);
		if (op == "+")
			result += temp;
		else
			result -= temp;
	}
	return result;
}



double Parsing::expr_mult_pow_sign_func_brackets_atom(LexicalStruct & lexicalStruct)
{
	double result, temp;
	result = expr_pow_sign_func_brackets_atom(lexicalStruct);
	string op;
	while (
			(lexicalStruct.current < lexicalStruct.tokens.cend()) && 
			(((op = lexicalStruct.current->value) == "*") || (op == "/"))
		  )
	{
		lexicalStruct.next();
		temp = expr_pow_sign_func_brackets_atom(lexicalStruct);
		if (op == "*")
			result *= temp;
		else
			if (temp != 0.0)
				result /= temp;
			else
				result = nanf("");
	}
	return result;
}



double Parsing::expr_pow_sign_func_brackets_atom(LexicalStruct & lexicalStruct)
{
	double result, temp;
	result = expr_sign_func_brackets_atom(lexicalStruct);
	while ((lexicalStruct.current < lexicalStruct.tokens.cend()) && (lexicalStruct.current->value == "^"))
	{
		lexicalStruct.next();
		temp = expr_sign_func_brackets_atom(lexicalStruct);
		result = pow(result, temp);
	}
	return result;
}



double Parsing::expr_sign_func_brackets_atom(LexicalStruct & lexicalStruct)
{
	if ((lexicalStruct.current < lexicalStruct.tokens.cend()) && (lexicalStruct.current->value == "-"))
	{
		lexicalStruct.next();
		return -expr_func_brackets_atom(lexicalStruct);
	}
	else
		return expr_func_brackets_atom(lexicalStruct);
}



double Parsing::expr_func_brackets_atom(LexicalStruct & lexicalStruct)
{
	if ((lexicalStruct.current < lexicalStruct.tokens.cend()) && (lexicalStruct.current->type == Token::function))
	{
		if (!mFunctions.count(lexicalStruct.current->value))
			return nanf("");
		string tempFunctionName(lexicalStruct.current->value);
		lexicalStruct.next();
		return mFunctions[tempFunctionName](expr_brackets_atom(lexicalStruct));    // вызываем функцию по указателю из ассоциативного контейнера mFunctions по ключу tempFunctionName. Viva La STL!!!
	}
	else
		return expr_brackets_atom(lexicalStruct);
}



double Parsing::expr_brackets_atom(LexicalStruct & lexicalStruct)
{
	if ((lexicalStruct.current < lexicalStruct.tokens.cend()) && (lexicalStruct.current->value == "("))
	{
		lexicalStruct.next();
		double temp = expr_sum_mult_pow_sign_func_brackets_atom(lexicalStruct);
		if ((lexicalStruct.current < lexicalStruct.tokens.cend()) && (lexicalStruct.current->value == ")"))
		{
			lexicalStruct.next();
			return temp;
		}
		else
			return nanf("");
	}
	else
		return expr_atom(lexicalStruct);
}



double Parsing::expr_atom(LexicalStruct & lexicalStruct)
{
	if ((lexicalStruct.current < lexicalStruct.tokens.cend()) && (lexicalStruct.current->type == Token::number))
	{
		double temp = stod(lexicalStruct.current->value);
		lexicalStruct.next();
		return temp;
	}
	else
		return nanf("");
}