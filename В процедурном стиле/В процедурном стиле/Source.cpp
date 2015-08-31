/* Демонстрационная программа для анализатора. */
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
		printf("Ошибка при выделении памяти.\n");
		exit(1);
	}

	/* Обработка выражений до ввода пустой строки. */
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