#include "Parsing.h"
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>


using namespace std;

char * expr;				// Строка выражения, определяется в функции double parse(char *)

char token[1000];			// Лексема, определяется функцией void get_token(void)
char tok_type;				// Вид лексемы, определяется функцией void get_token(void)

// Функции рекурсивной обработки выражения
void expr_sum_mult_pow_sign_brackets_atom(double *);	// Сумма + произведение + степень + унарный оператор + выражение в скобках + число
void expr_mult_pow_sign_brackets_atom(double *);		// Произведение + степень + унарный оператор + выражение в скобках + число
void expr_pow_sign_brackets_atom(double *);				// Степень + унарный оператор + выражение в скобках + число
void expr_sign_brackets_atom(double *);					// Унарный оператор + выражение в скобках + число
void expr_brackets_atom(double *);						// Выражение в скобках + число
void expr_atom(double *);								// Число - выход из рекурсивного спуска по цепочке вызовов

// Определение следующей лексемы и вида лексемы
void get_token(void);									

// Возвращение значения 1, если аргумент является разделителем
int isdelim(char);			

// Отображение сообщения об ошибке
void serror(int);										



// Точка входа анализатора
double parse(char * p)
{
	expr = p;
	double answer; 

	get_token();
	
	if (!*token)
	{
		serror(2);
		return 0;
	}

	expr_sum_mult_pow_sign_brackets_atom(&answer);

	if (*token)		// последней лексемой должен быть ноль
		serror(0); 

	return answer;

}



// Сумма + произведение + степень + унарный оператор + выражение в скобках + число
void expr_sum_mult_pow_sign_brackets_atom(double * answer)
{
	register char  op;
	double temp;

	expr_mult_pow_sign_brackets_atom(answer);

	while ((op = *token) == '+' || op == '-')
	{
		get_token();
		expr_mult_pow_sign_brackets_atom(&temp);
		switch (op)
		{
			case '-':
			*answer = *answer - temp;
			break;
			case '+':
			*answer = *answer + temp;
			break;
		}
	}
}



// Произведение + степень + унарный оператор + выражение в скобках + число
void expr_mult_pow_sign_brackets_atom(double * answer)
{
	register char op;
	double temp;

	expr_pow_sign_brackets_atom(answer);

	while ((op = *token) == '*' || op == '/' || op == '%')
	{
		get_token();
		expr_pow_sign_brackets_atom(&temp);
		switch (op)
		{
			case '*':
			*answer = *answer * temp;
			break;
			case '/':
			if (temp == 0.0)
			{
				serror(3); // деление на нуль
				*answer = 0.0;
			}
			else *answer = *answer / temp;
			break;
			case '%':
			*answer = (int)*answer % (int)temp;
			break;
		}
	}
}



// Степень + унарный оператор + выражение в скобках + число
void expr_pow_sign_brackets_atom(double * answer)
{
	double temp, ex;
	register int t;

	expr_sign_brackets_atom(answer);

	if (*token == '^')
	{
		get_token();
		expr_pow_sign_brackets_atom(&temp);
		ex = *answer;
		if (temp == 0.0)
		{
			*answer = 1.0;
			return;
		}
		for (t = temp - 1; t>0; --t) *answer = (*answer) * (double)ex;
	}
}



// Унарный оператор + выражение в скобках + число
void expr_sign_brackets_atom(double * answer)
{
	register char  op;

	op = 0;
	if ((tok_type == DELIMITER) && *token == '+' || *token == '-')
	{
		op = *token;
		get_token();
	}

	expr_atom(answer);

	if (op == '-') *answer = -(*answer);
}



// Выражение в скобках + число
void expr_brackets_atom(double * answer)
{
	if ((*token == '('))
	{
		get_token();
		expr_sum_mult_pow_sign_brackets_atom(answer);	// вычисление выражения в токене
		if (*token != ')')	// Отсутствует закрывающая скобка
			serror(1);
		get_token();
	}
	else
		expr_atom(answer);
}



// Число - выход из рекурсивного спуска по цепочке вызовов
void expr_atom(double * answer)
{
	if (tok_type == NUMBER)
	{
		*answer = atof(token);
		get_token();
		return;
	}
	serror(0);  // иначе синтаксическая ошибка в выражении
}



// Возврат очередной лексемы
void get_token(void)
{
	register char * temp;

	tok_type = 0;	// сброс
	temp = token;
	*temp = '\0';	// сброс, инициализация временной переменной символом конца строки

	if (!*expr) return; // конец выражения 
	while (isspace(*expr)) 
		++expr; // пропустить пробелы, символы табуляции и пустой строки, откусываем от строки, смещая указатель

	if (strchr("+-*/%^=()", *expr))	// знак-разделитель
	{
		tok_type = DELIMITER;	
		// перейтик следующему символу 
		*temp++ = *expr++;
	}
	else if (isdigit(*expr))	// число
	{
		while (!isdelim(*expr)) 
			*temp++ = *expr++;
		tok_type = NUMBER;
	}


	cout << "Token: " << token << endl;  // отладочная информация
	cout << "Expr: " << expr << endl;    
	cout << endl;

	*temp = '\0';
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
		"Синтаксическая ошибка",
		"Несбалансированные скобки",
		"Нет выражения",
		"Деление на ноль"
	};
	printf("%s\n", e[error]);
}

