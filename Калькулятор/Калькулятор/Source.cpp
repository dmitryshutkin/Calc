/* Это модуль содержит простой синтаксический анализатор,
который не распознает переменные.
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3

extern char *prog;   /* содержит анализируемое выражение */
char token[80];
char tok_type;

void eval_exp(double *answer), eval_exp2(double *answer);
void eval_exp3(double *answer), eval_exp4(double *answer);
void eval_exp5(double *answer), eval_exp6(double *answer);
void atom(double *answer);
void get_token(void), putback(void);
void serror(int error);
int isdelim(char c);

/* Точка входа анализатора. */
void eval_exp(double *answer)
{
	get_token();
	if (!*token)
	{
		serror(2);
		return;
	}
	eval_exp2(answer);

	if (*token) serror(0); /* последней лексемой должен быть нуль */
}

/* Сложение или вычитание двух слагаемых. */
void eval_exp2(double *answer)
{
	register char  op;
	double temp;

	eval_exp3(answer);
	while ((op = *token) == '+' || op == '-')
	{
		get_token();
		eval_exp3(&temp);
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

/* Умножение или деление двух множителей. */
void eval_exp3(double *answer)
{
	register char op;
	double temp;

	eval_exp4(answer);
	while ((op = *token) == '*' || op == '/' || op == '%')
	{
		get_token();
		eval_exp4(&temp);
		switch (op)
		{
			case '*':
			*answer = *answer * temp;
			break;
			case '/':
			if (temp == 0.0)
			{
				serror(3); /* деление на нуль */
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

/* Возведение в степень */
void eval_exp4(double *answer)
{
	double temp, ex;
	register int t;

	eval_exp5(answer);

	if (*token == '^')
	{
		get_token();
		eval_exp4(&temp);
		ex = *answer;
		if (temp == 0.0)
		{
			*answer = 1.0;
			return;
		}
		for (t = temp - 1; t>0; --t) *answer = (*answer) * (double)ex;
	}
}

/* Умножение унарных операторов + и -. */
void eval_exp5(double *answer)
{
	register char  op;

	op = 0;
	if ((tok_type == DELIMITER) && *token == '+' || *token == '-')
	{
		op = *token;
		get_token();
	}
	eval_exp6(answer);
	if (op == '-') *answer = -(*answer);
}

/* Вычисление выражения в скобках. */
void eval_exp6(double *answer)
{
	if ((*token == '('))
	{
		get_token();
		eval_exp2(answer);
		if (*token != ')')
			serror(1);
		get_token();
	}
	else
		atom(answer);
}

/* Получение значения в скобках. */
void atom(double *answer)
{
	if (tok_type == NUMBER)
	{
		*answer = atof(token);
		get_token();
		return;
	}
	serror(0);  /* иначе синтаксическая ошибка в выражении */
}

/* Выражение лексемы во входной поток. */
void putback(void)
{
	char *t;

	t = token;
	for (; *t; t++) prog--;
}

/* Отображение сообщения об ошибке. */
void serror(int error)
{
	static char *e[] = {
		"Синтаксическая ошибка",
		"Несбалансированные скобки",
		"Нет выражения",
		"Деление на нуль"
	};
	printf("%s\n", e[error]);
}

/* Возврат очередной лексемы. */
void get_token(void)
{
	register char *temp;

	tok_type = 0;
	temp = token;
	*temp = '\0';

	if (!*prog) return; /* конец выражения */
	while (isspace(*prog)) ++prog; /* пропустить пробелы,
								   символы табуляции и пустой строки */

	if (strchr("+-*/%^=()", *prog))
	{
		tok_type = DELIMITER;
		/* перейтик следующему символу */
		*temp++ = *prog++;
	}
	else if (isalpha(*prog))
	{
		while (!isdelim(*prog)) *temp++ = *prog++;
		tok_type = VARIABLE;
	}
	else if (isdigit(*prog))
	{
		while (!isdelim(*prog)) *temp++ = *prog++;
		tok_type = NUMBER;
	}

	*temp = '\0';
}

/* Возвращение значения ИСТИНА, если с является разделителем. */
int isdelim(char c)
{

	if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}