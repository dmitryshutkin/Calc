/* ���������������� ��������� ��� �����������. */
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <locale>
#include "Parsing.h"

using namespace std;

char *prog;
// void parse(double *answer);

int main(void)
{
	setlocale(LC_CTYPE, "");
	double answer;
	char *p;

	p = (char *)malloc(100);
	if (!p)
	{
		printf("������ ��� ��������� ������.\n");
		exit(1);
	}

	/* ��������� ��������� �� ����� ������ ������. */
	do
	{
		prog = p;
		printf(">> ");
		gets_s(prog, 100);
		if (!*prog) break;
		parse(&answer);
		printf(">> %.2f\n", answer);
	} while (*p);

	return 0;
}