#include "Parsing.h"
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>


using namespace std;

char * expr;				// ������ ���������, ������������ � ������� double parse(char *)

char token[1000];			// �������, ������������ �������� void get_token(void)
char tok_type;				// ��� �������, ������������ �������� void get_token(void)

// ������� ����������� ��������� ���������
void expr_sum_mult_pow_sign_brackets_atom(double *);	// ����� + ������������ + ������� + ������� �������� + ��������� � ������� + �����
void expr_mult_pow_sign_brackets_atom(double *);		// ������������ + ������� + ������� �������� + ��������� � ������� + �����
void expr_pow_sign_brackets_atom(double *);				// ������� + ������� �������� + ��������� � ������� + �����
void expr_sign_brackets_atom(double *);					// ������� �������� + ��������� � ������� + �����
void expr_brackets_atom(double *);						// ��������� � ������� + �����
void expr_atom(double *);								// ����� - ����� �� ������������ ������ �� ������� �������

// ����������� ��������� ������� � ���� �������
void get_token(void);									

// ����������� �������� 1, ���� �������� �������� ������������
int isdelim(char);			

// ����������� ��������� �� ������
void serror(int);										



// ����� ����� �����������
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

	if (*token)		// ��������� �������� ������ ���� ����
		serror(0); 

	return answer;

}



// ����� + ������������ + ������� + ������� �������� + ��������� � ������� + �����
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



// ������������ + ������� + ������� �������� + ��������� � ������� + �����
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
				serror(3); // ������� �� ����
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



// ������� + ������� �������� + ��������� � ������� + �����
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



// ������� �������� + ��������� � ������� + �����
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



// ��������� � ������� + �����
void expr_brackets_atom(double * answer)
{
	if ((*token == '('))
	{
		get_token();
		expr_sum_mult_pow_sign_brackets_atom(answer);	// ���������� ��������� � ������
		if (*token != ')')	// ����������� ����������� ������
			serror(1);
		get_token();
	}
	else
		expr_atom(answer);
}



// ����� - ����� �� ������������ ������ �� ������� �������
void expr_atom(double * answer)
{
	if (tok_type == NUMBER)
	{
		*answer = atof(token);
		get_token();
		return;
	}
	serror(0);  // ����� �������������� ������ � ���������
}



// ������� ��������� �������
void get_token(void)
{
	register char * temp;

	tok_type = 0;	// �����
	temp = token;
	*temp = '\0';	// �����, ������������� ��������� ���������� �������� ����� ������

	if (!*expr) return; // ����� ��������� 
	while (isspace(*expr)) 
		++expr; // ���������� �������, ������� ��������� � ������ ������, ���������� �� ������, ������ ���������

	if (strchr("+-*/%^=()", *expr))	// ����-�����������
	{
		tok_type = DELIMITER;	
		// �������� ���������� ������� 
		*temp++ = *expr++;
	}
	else if (isdigit(*expr))	// �����
	{
		while (!isdelim(*expr)) 
			*temp++ = *expr++;
		tok_type = NUMBER;
	}


	cout << "Token: " << token << endl;  // ���������� ����������
	cout << "Expr: " << expr << endl;    
	cout << endl;

	*temp = '\0';
}



// ����������� �������� 1, ���� �������� �������� ������������
int isdelim(char c)
{

	if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}



// ����������� ��������� �� ������
void serror(int error)
{
	static char * e[] = {
		"�������������� ������",
		"������������������ ������",
		"��� ���������",
		"������� �� ����"
	};
	printf("%s\n", e[error]);
}

