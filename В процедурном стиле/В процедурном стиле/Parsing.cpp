#include "Parsing.h"
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>


using namespace std;

char token[80];
char tok_type;

void eval_exp2(double *);	// �������� ��� ��������� ���� ���������
void eval_exp3(double *);	// ��������� ��� ������� ���� ����������
void eval_exp4(double *);	// ���������� � �������
void eval_exp5(double *);	// ��������� ������� ���������� + � -
void eval_exp6(double *);	// ���������� ��������� � �������
void atom(double *);		// ��������� �������� � �������
void get_token(void);		// ��������� ������� �� ������� �����
void serror(int);			// ����������� ��������� �� ������
int isdelim(char);			// ����������� �������� 1, ���� �������� �������� ������������



// ����� ����� �����������
void parse(double * answer)
{
	get_token();
	if (!*token)
	{
		serror(2);
		return;
	}
	eval_exp2(answer);

	if (*token) serror(0); // ��������� �������� ������ ���� ����
}



// �������� ��� ��������� ���� ���������
void eval_exp2(double * answer)
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



// ��������� ��� ������� ���� ����������
void eval_exp3(double * answer)
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



// ���������� � �������
void eval_exp4(double * answer)
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



// ��������� ������� ���������� + � -
void eval_exp5(double * answer)
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



// ���������� ��������� � �������
void eval_exp6(double * answer)
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



// ��������� �������� � �������
void atom(double * answer)
{
	if (tok_type == NUMBER)
	{
		*answer = atof(token);
		get_token();
		return;
	}
	serror(0);  // ����� �������������� ������ � ���������
}



// ����������� ��������� �� ������
void serror(int error)
{
	static char *e[] = {
		"�������������� ������",
		"������������������ ������",
		"��� ���������",
		"������� �� ����"
	};
	printf("%s\n", e[error]);
}



// ������� ��������� �������
void get_token(void)
{
	register char *temp;

	tok_type = 0;
	temp = token;
	*temp = '\0';

	if (!*prog) return; // ����� ��������� 
	while (isspace(*prog)) ++prog; // ���������� �������, ������� ��������� � ������ ������ 

	if (strchr("+-*/%^=()", *prog))
	{
		tok_type = DELIMITER;
		// �������� ���������� ������� 
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



// ����������� �������� 1, ���� �������� �������� ������������
int isdelim(char c)
{

	if (strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}