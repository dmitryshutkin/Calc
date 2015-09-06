﻿#include <iostream>

#include "Parsing.h"


using namespace std;

class Token					// Класс лексем
{
public:
	enum Type
	{
		undefined,
		delimiter,
		number,
		function
	};
	char value[255];
	Type type;				// Вид лексемы, определяется функцией get_token()
};


Token token;				// Лексема, определяется побочным действием функциии get_token.value()
const char * expr;			// Указатель на строку выражения, определяется побочным действием функциии parse(), обрезается после get_token.value()





// Функции рекурсивной обработки выражения
// Цепочка вызовов:
// Сумма -> произведение -> степень -> унарный оператор -> функция -> выражение в скобках -> число

void expr_sum_mult_pow_sign_func_brackets_atom(double *);   // Сумма + произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_mult_pow_sign_func_brackets_atom(double *);       // Произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_pow_sign_func_brackets_atom(double *);            // Степень + унарный оператор + функция + выражение в скобках + число
void expr_sign_func_brackets_atom(double *);                // Унарный оператор + функция + выражение в скобках + число
void expr_func_brackets_atom(double *);                     // Функция + выражение в скобках + число
void expr_brackets_atom(double *);                          // Выражение в скобках + число
void expr_atom(double *);                                   // Число --- выход из рекурсивного спуска

// Определение следующей лексемы в выражении и вида лексемы
void get_token(void);									

// Возвращение значения 1, если аргумент является разделителем
int isdelim(char);			

// Отображение сообщения об ошибке
void serror(int);										




// Точка входа анализатора
double parse(const char * const p)
{
	expr = p;

	double answer; 

	get_token();
	
	if (!*token.value)
	{
		serror(2);  
		return nanf("");
	}

	expr_sum_mult_pow_sign_func_brackets_atom(&answer);

	if (*token.value)		// последней лексемой должен быть ноль
	{
		serror(0);
		answer = nanf("");
	}

	return answer;

}



// Сумма + произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_sum_mult_pow_sign_func_brackets_atom(double * answer)
{
	register char  op;
	double temp;

	expr_mult_pow_sign_func_brackets_atom(answer);

	while ((op = *token.value) == '+' || op == '-')
	{
		get_token();
		expr_mult_pow_sign_func_brackets_atom(&temp);
		
		switch (op)
		{
		case '-':
			*answer -= temp;
			break;
		case '+':
			*answer += temp;
			break;
		}
	}
}



// Произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_mult_pow_sign_func_brackets_atom(double * answer)
{
	register char op;
	double temp;

	expr_pow_sign_func_brackets_atom(answer);

	while ((op = *token.value) == '*' || op == '/' || op == '%')
	{
		get_token();
		expr_pow_sign_func_brackets_atom(&temp);

		switch (op)
		{
		case '*':
			*answer *= temp;
			break;
		case '/':
			if (temp == 0.0)
			{
				serror(3); // деление на нуль
				*answer = nanf("");
			}
			else 
				*answer /= temp;
			break;
		case '%':
			*answer = (int)*answer % (int)temp;
			break;
		}
	}
}



// Степень + унарный оператор + функция + выражение в скобках + число
void expr_pow_sign_func_brackets_atom(double * answer)
{	
	expr_sign_func_brackets_atom(answer);

	if (*token.value == '^')
	{
		double temp;
		get_token();
		expr_pow_sign_func_brackets_atom(&temp);
		*answer = pow(*answer, temp);
	}
}



// Унарный оператор + функция + выражение в скобках + число
void expr_sign_func_brackets_atom(double * answer)
{
	register char  op;

	op = 0;
	if ((token.type == Token::delimiter) && *token.value == '+' || *token.value == '-')
	{
		op = *token.value;
		get_token();
	}

	expr_func_brackets_atom(answer);

	if (op == '-') 
		*answer = -(*answer);
}



// Функция + выражение в скобках + число
void expr_func_brackets_atom(double * answer)
{
	if (token.type == Token::function)
	{
		get_token();

		expr_brackets_atom(answer);

		*answer = sin(*answer);   // заглушка - sin
	}
	else
		expr_brackets_atom(answer);
}


// Выражение в скобках + число
void expr_brackets_atom(double * answer)
{
	if ((*token.value == '('))
	{
		get_token();
		expr_sum_mult_pow_sign_func_brackets_atom(answer);	// вычисление подвыражения в выражении в скобках, в результате побочного действия должен остаться token == ')'
		if (*token.value != ')')	// Отсутствует закрывающая скобка
		{
			serror(1);
			*answer = nanf("");
		}
		get_token();
	}
	else
		expr_atom(answer);
}



// Число --- выход из рекурсивного спуска
void expr_atom(double * answer)
{
	if (token.type == Token::number)
	{
		*answer = atof(token.value);
		get_token();
		
		return;
	}
	serror(0);  // иначе синтаксическая ошибка в выражении
	*answer = nanf("");  // нечисло
}



// Возврат очередной лексемы
void get_token(void)
{
	register char * temp;

	token.type = Token::undefined;		// обнуляем тип лексемы
	temp = token.value;
	*temp = '\0';				// обнуляем значение лексемы через указатель

	if (!*expr)					// конец выражения 
		return;	

	while (isspace((unsigned char)*expr))		// пропустить пробелы, символы табуляции 
		++expr;		

	if (strchr("+-*/%^=()", *expr))
	{
		token.type = Token::delimiter;	// устанавливаем тип лексемы
		*temp++ = *expr++;		// заполняем лексему символами из *expr (один символ), смещаем указатели
	}
	else if (expr  == strstr(expr, "sin"))
	{
		token.type = Token::function;
		while ((*expr != '(') && !isdigit((unsigned char)*expr))	//
			*temp++ = *expr++;	// заполняем лексему символами из *expr, смещаем указатели
	}
	else if (isdigit((unsigned char)*expr))
	{
		token.type = Token::number;		// устанавливаем тип лексемы
		while (!isdelim(*expr))	
			*temp++ = *expr++;	// заполняем лексему символами из *expr, смещаем указатели
	}

	*temp = '\0';				// закрываем строку
}



// Возвращение значения 1, если аргумент является разделителем
int isdelim(char c)
{

	if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}



// Отображение сообщения об ошибке
void serror(int error)
{
	static char * e[] = {
		" =>  Синтаксическая ошибка",
		" =>  Несбалансированные скобки",
		" =>  Нет выражения",
		" =>  Деление на ноль"
	};
	cout << e[error] << endl;
}
