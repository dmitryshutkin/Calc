#include <iostream>

#include "Parsing.h"



using namespace std;



// Класс лексем
class Token
{
public:
	char value[255];
	enum { undefined, delimiter, number, function } type;	// Вид лексемы
};





// Функции рекурсивной обработки выражения
// Цепочка вызовов:
// Сумма -> произведение -> степень -> унарный оператор -> функция -> выражение в скобках -> число

void expr_sum_mult_pow_sign_func_brackets_atom(double *, char * &, Token &);   // Сумма + произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_mult_pow_sign_func_brackets_atom(double *, char * &, Token &);       // Произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_pow_sign_func_brackets_atom(double *, char * &, Token &);            // Степень + унарный оператор + функция + выражение в скобках + число
void expr_sign_func_brackets_atom(double *, char * &, Token &);                // Унарный оператор + функция + выражение в скобках + число
void expr_func_brackets_atom(double *, char * &, Token &);                     // Функция + выражение в скобках + число
void expr_brackets_atom(double *, char * &, Token &);                          // Выражение в скобках + число
void expr_atom(double *, char * &, Token &);                                   // Число --- выход из рекурсивного спуска

// Определение следующей лексемы в выражении и вида лексемы
void get_token(char * &, Token &);

// Возвращение значения 1, если аргумент является разделителем
int isdelim(char);			

// Отображение сообщения об ошибке
void serror(int);										




// Точка входа анализатора
double parse(const char * const expr)
{
	double answer;
	char expr_rest[255];			// Указатель на строку выражения, определяется побочным действием функциии parse(), обрезается после get_token()
	char * expr_rest_ptr = expr_rest;

	Token token;					// Лексема, определяется побочным действием функциии get_token()
	


	strcpy_s(expr_rest, 255, expr);
	//*expr_rest = *expr;

	get_token(expr_rest_ptr, token);

	if (!*token.value)				// нулевая строка
	{
		serror(2);  
		return nanf("");
	}

	expr_sum_mult_pow_sign_func_brackets_atom(&answer, expr_rest_ptr, token);

	if (*token.value)				// последней лексемой должен быть ноль
	{
		serror(0);
		answer = nanf("");
	}

	
	return answer;
}



// Сумма + произведение + степень + унарный оператор + функция + выражение в скобках + число
void expr_sum_mult_pow_sign_func_brackets_atom(double * answer, char * & expr_rest, Token & token)
{
	register char  op;
	double temp;

	expr_mult_pow_sign_func_brackets_atom(answer, expr_rest, token);

	while ((op = *token.value) == '+' || op == '-')
	{
		get_token(expr_rest, token);
		expr_mult_pow_sign_func_brackets_atom(&temp, expr_rest, token);
		
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
void expr_mult_pow_sign_func_brackets_atom(double * answer, char * & expr_rest, Token & token)
{
	register char op;
	double temp;

	expr_pow_sign_func_brackets_atom(answer, expr_rest, token);

	while ((op = *token.value) == '*' || op == '/' || op == '%')
	{
		get_token(expr_rest, token);
		expr_pow_sign_func_brackets_atom(&temp, expr_rest, token);

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
void expr_pow_sign_func_brackets_atom(double * answer, char * & expr_rest, Token & token)
{	
	expr_sign_func_brackets_atom(answer, expr_rest, token);

	if (*token.value == '^')
	{
		double temp;
		get_token(expr_rest, token);
		expr_pow_sign_func_brackets_atom(&temp, expr_rest, token);
		*answer = pow(*answer, temp);
	}
}



// Унарный оператор + функция + выражение в скобках + число
void expr_sign_func_brackets_atom(double * answer, char * & expr_rest, Token & token)
{
	register char  op;

	op = 0;
	if ((token.type == Token::delimiter) && *token.value == '+' || *token.value == '-')
	{
		op = *token.value;
		get_token(expr_rest, token);
	}

	expr_func_brackets_atom(answer, expr_rest, token);

	if (op == '-') 
		*answer = -(*answer);
}



// Функция + выражение в скобках + число
void expr_func_brackets_atom(double * answer, char * & expr_rest, Token & token)
{
	if (token.type == Token::function)
	{
		get_token(expr_rest, token);

		expr_brackets_atom(answer, expr_rest, token);

		*answer = sin(*answer);   // заглушка - sin
	}
	else
		expr_brackets_atom(answer, expr_rest, token);
}


// Выражение в скобках + число
void expr_brackets_atom(double * answer, char * & expr_rest, Token & token)
{
	if ((*token.value == '('))
	{
		get_token(expr_rest, token);
		expr_sum_mult_pow_sign_func_brackets_atom(answer, expr_rest, token);	// вычисление подвыражения в выражении в скобках, в результате побочного действия должен остаться token == ')'
		if (*token.value != ')')	// Отсутствует закрывающая скобка
		{
			serror(1);
			*answer = nanf("");
		}
		get_token(expr_rest, token);
	}
	else
		expr_atom(answer, expr_rest, token);
}



// Число --- выход из рекурсивного спуска
void expr_atom(double * answer, char * & expr_rest, Token & token)
{
	if (token.type == Token::number)
	{
		*answer = atof(token.value);
		get_token(expr_rest, token);
		
		return;
	}
	serror(0);  // иначе синтаксическая ошибка в выражении
	*answer = nanf("");  // нечисло
}



// Возврат очередной лексемы
void get_token(char * & expr_rest, Token & token)
{
	register char * temp;
	token.type = Token::undefined;						// обнуляем тип лексемы
	temp = token.value;
	*temp = '\0';										// обнуляем значение лексемы через указатель

	if (!*expr_rest)									// конец выражения 
		return;	

	while (isspace((unsigned char)*expr_rest))			// пропустить пробелы, символы табуляции 
		++expr_rest;		

	if (strchr("+-*/%^=()", *expr_rest))
	{
		token.type = Token::delimiter;					// устанавливаем тип лексемы
		*temp++ = *expr_rest++;							// заполняем лексему символами из *expr_rest (один символ), смещаем указатели
	}
	else if (expr_rest  == strstr(expr_rest, "sin"))
	{
		token.type = Token::function;
		while ((*expr_rest != '(') && !isdigit((unsigned char)*expr_rest))	//
			*temp++ = *expr_rest++;						// заполняем лексему символами из *expr_rest, смещаем указатели
	}
	else if (isdigit((unsigned char)*expr_rest))
	{
		token.type = Token::number;						// устанавливаем тип лексемы
		while (!isdelim(*expr_rest))	
			*temp++ = *expr_rest++;						// заполняем лексему символами из *expr_rest, смещаем указатели
	}

	*temp = '\0';										// закрываем строку

	// Отладочная информация
	cout << "Token: " << token.value << "  token type: " << token.type << "  expressinon rest: " << expr_rest << endl;
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
