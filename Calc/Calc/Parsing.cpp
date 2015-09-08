#include <iostream>
#include <map>

#include "Parsing.h"
#include "CalcMath.h"


using namespace std;



// Класс лексем
class Token
{
public:
	char value[255];
	enum { undefined, delimiter, number, function } type;
};



// Контейнер указателей на математические функции 
map <string, double(*)(double)> mFunctions =
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



// Общедоступные данные
Token token;                    // Лексема, определяется побочным действием функциии get_token()
const char * rest_expr;         // Указатель на строку выражения, определяется побочным действием функциии parse(), обрезается после каждого вызова get_token()



								// Функции рекурсивной обработки выражения
								// Цепочка вызовов:
								// Сумма -> произведение -> степень -> унарный оператор -> функция -> выражение в скобках -> число

void expr_sum_mult_pow_sign_func_brackets_atom(double *);   // Сумма + произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_mult_pow_sign_func_brackets_atom(double *);       // Произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_pow_sign_func_brackets_atom(double *);            // Степень + унарный оператор + функция + выражение в скобках + число
void expr_sign_func_brackets_atom(double *);                // Унарный оператор + функция + выражение в скобках + число
void expr_func_brackets_atom(double *);                     // Функция + выражение в скобках + число
void expr_brackets_atom(double *);                          // Выражение в скобках + число
void expr_atom(double *);                                   // Число --- выход из рекурсивного спуска по цепочке вызовов

															// Определяем следующую лексему в выражении
void get_token(void);

// Возвращаем значение 1, если аргумент является разделителем
int isdelim(char);

// Возвращаем значения 1, если аргумент является функцией
int isfunc(const char *);

// Отображаем сообщения об ошибке
void serror(int);




// Точка входа анализатора


double parse(const string & str)
{
	return parse(str.c_str());
}


double parse(const char * const expr)
{
	rest_expr = expr;

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
				serror(3); // деление на ноль
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
		string tempFunctionName(token.value);

		get_token();

		expr_brackets_atom(answer);


		*answer = mFunctions[tempFunctionName](*answer);    // вызываем функцию по указателю из ассоциативного контейнера mFunctions по ключу tempFunctionName. Viva La STL!!!
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
		expr_sum_mult_pow_sign_func_brackets_atom(answer);  // вычисление подвыражения в выражении в скобках, в результате побочного действия должен остаться token == ')'
		if (*token.value != ')')                            // Отсутствует закрывающая скобка
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
	serror(0);                                  // иначе синтаксическая ошибка в выражении
	*answer = nanf("");                         // нечисло
}



// Определяем следующую лексему в выражении
void get_token(void)
{
	register char * temp;

	token.type = Token::undefined;              // обнуляем тип лексемы
	temp = token.value;
	*temp = '\0';                               // обнуляем значение лексемы через указатель

	if (!*rest_expr)                            // конец выражения 
		return;

	while (isspace((unsigned char)*rest_expr))  // пропустить пробелы, символы табуляции 
		++rest_expr;

	if (strchr("+-*/%^=()", *rest_expr))
	{
		token.type = Token::delimiter;          // устанавливаем тип лексемы
		*temp++ = *rest_expr++;                 // заполняем лексему символами из *rest_expr (один символ), смещаем указатели
	}
	else if (isfunc(rest_expr))
	{
		token.type = Token::function;
		while ((*rest_expr != '(') && !isdigit((unsigned char)*rest_expr))
			*temp++ = *rest_expr++;             // заполняем лексему символами из *rest_expr, смещаем указатели
	}
	else if (isdigit((unsigned char)*rest_expr))
	{
		token.type = Token::number;             // устанавливаем тип лексемы
		while (!isdelim(*rest_expr))
			*temp++ = *rest_expr++;             // заполняем лексему символами из *rest_expr, смещаем указатели на шаге
	}

	*temp = '\0';                               // закрываем строку
}



// Возвращаем значение 1, если аргумент является разделителем
int isdelim(char c)
{

	if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}



// Возвращаем значения 1, если аргумент является функцией
int isfunc(const char * expr_rest)
{
	int result = 0;
	for (const auto & elem : mFunctions)	  // Viva La STL!!!
		if (expr_rest == strstr(expr_rest, elem.first.c_str()))
		{
			result = 1;
			break;
		}
	return result;
}



// Отображаем сообщения об ошибке
void serror(int error)
{
	static char * e[] = {
		" =>  Синтаксическая ошибка",
		" =>  Несбалансированные скобки",
		" =>  Неизвестный оператор",
		" =>  Деление на ноль"
	};
	cout << e[error] << endl;
}
