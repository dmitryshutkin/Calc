#include <iostream>
#include <map>

#include "Parsing.h"
#include "CalcMath.h"


using namespace std;



// ����� ������
class Token
{
public:
	char value[255];
	enum { undefined, delimiter, number, function } type;
};



// ��������� ���������� �� �������������� ������� 
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



// ������������� ������
Token token;                    // �������, ������������ �������� ��������� �������� get_token()
const char * rest_expr;         // ��������� �� ������ ���������, ������������ �������� ��������� �������� parse(), ���������� ����� ������� ������ get_token()



								// ������� ����������� ��������� ���������
								// ������� �������:
								// ����� -> ������������ -> ������� -> ������� �������� -> ������� -> ��������� � ������� -> �����

void expr_sum_mult_pow_sign_func_brackets_atom(double *);   // ����� + ������������ + ������� + ������� �������� + ������� + ��������� � ������� + �����
void expr_mult_pow_sign_func_brackets_atom(double *);       // ������������ + ������� + ������� �������� + ������� + ��������� � ������� + �����
void expr_pow_sign_func_brackets_atom(double *);            // ������� + ������� �������� + ������� + ��������� � ������� + �����
void expr_sign_func_brackets_atom(double *);                // ������� �������� + ������� + ��������� � ������� + �����
void expr_func_brackets_atom(double *);                     // ������� + ��������� � ������� + �����
void expr_brackets_atom(double *);                          // ��������� � ������� + �����
void expr_atom(double *);                                   // ����� --- ����� �� ������������ ������ �� ������� �������

															// ���������� ��������� ������� � ���������
void get_token(void);

// ���������� �������� 1, ���� �������� �������� ������������
int isdelim(char);

// ���������� �������� 1, ���� �������� �������� ��������
int isfunc(const char *);

// ���������� ��������� �� ������
void serror(int);




// ����� ����� �����������


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

	if (*token.value)		// ��������� �������� ������ ���� ����
	{
		serror(0);
		answer = nanf("");
	}

	return answer;

}



// ����� + ������������ + ������� + ������� �������� + ������� + ��������� � ������� + �����
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



// ������������ + ������� + ������� �������� + ������� + ��������� � ������� + �����
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
				serror(3); // ������� �� ����
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



// ������� + ������� �������� + ������� + ��������� � ������� + �����
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



// ������� �������� + ������� + ��������� � ������� + �����
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



// ������� + ��������� � ������� + �����
void expr_func_brackets_atom(double * answer)
{
	if (token.type == Token::function)
	{
		string tempFunctionName(token.value);

		get_token();

		expr_brackets_atom(answer);


		*answer = mFunctions[tempFunctionName](*answer);    // �������� ������� �� ��������� �� �������������� ���������� mFunctions �� ����� tempFunctionName. Viva La STL!!!
	}
	else
		expr_brackets_atom(answer);
}



// ��������� � ������� + �����
void expr_brackets_atom(double * answer)
{
	if ((*token.value == '('))
	{
		get_token();
		expr_sum_mult_pow_sign_func_brackets_atom(answer);  // ���������� ������������ � ��������� � �������, � ���������� ��������� �������� ������ �������� token == ')'
		if (*token.value != ')')                            // ����������� ����������� ������
		{
			serror(1);
			*answer = nanf("");
		}
		get_token();
	}
	else
		expr_atom(answer);
}



// ����� --- ����� �� ������������ ������
void expr_atom(double * answer)
{
	if (token.type == Token::number)
	{
		*answer = atof(token.value);
		get_token();

		return;
	}
	serror(0);                                  // ����� �������������� ������ � ���������
	*answer = nanf("");                         // �������
}



// ���������� ��������� ������� � ���������
void get_token(void)
{
	register char * temp;

	token.type = Token::undefined;              // �������� ��� �������
	temp = token.value;
	*temp = '\0';                               // �������� �������� ������� ����� ���������

	if (!*rest_expr)                            // ����� ��������� 
		return;

	while (isspace((unsigned char)*rest_expr))  // ���������� �������, ������� ��������� 
		++rest_expr;

	if (strchr("+-*/%^=()", *rest_expr))
	{
		token.type = Token::delimiter;          // ������������� ��� �������
		*temp++ = *rest_expr++;                 // ��������� ������� ��������� �� *rest_expr (���� ������), ������� ���������
	}
	else if (isfunc(rest_expr))
	{
		token.type = Token::function;
		while ((*rest_expr != '(') && !isdigit((unsigned char)*rest_expr))
			*temp++ = *rest_expr++;             // ��������� ������� ��������� �� *rest_expr, ������� ���������
	}
	else if (isdigit((unsigned char)*rest_expr))
	{
		token.type = Token::number;             // ������������� ��� �������
		while (!isdelim(*rest_expr))
			*temp++ = *rest_expr++;             // ��������� ������� ��������� �� *rest_expr, ������� ��������� �� ����
	}

	*temp = '\0';                               // ��������� ������
}



// ���������� �������� 1, ���� �������� �������� ������������
int isdelim(char c)
{

	if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}



// ���������� �������� 1, ���� �������� �������� ��������
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



// ���������� ��������� �� ������
void serror(int error)
{
	static char * e[] = {
		" =>  �������������� ������",
		" =>  ������������������ ������",
		" =>  ����������� ��������",
		" =>  ������� �� ����"
	};
	cout << e[error] << endl;
}
