/* Демонстрационная программа для анализатора. */
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <locale>
#include "Parsing.h"

using namespace std;



char *str;
// void parse(double *answer);



int main(void)
{
	setlocale(LC_CTYPE, "");
	double answer;
	char *p;

	p = (char *)malloc(1000);
	if (!p)
	{
		printf("Ошибка при выделении памяти.\n");
		exit(1);
	}

	/* Обработка выражений до ввода пустой строки. */
	do
	{
		str = p;
		printf(">> ");
		gets_s(str, 1000);
		if (!*str) break;
		answer = parse(str);
		printf(">> %.2f\n", answer);
	} while (*p);

	return 0;
}