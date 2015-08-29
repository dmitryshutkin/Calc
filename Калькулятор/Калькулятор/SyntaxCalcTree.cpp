#include "SyntaxCalcTree.h"
#include <iostream>

using namespace std;



int SyntaxCalcTree::result()
{
	return op(a, b);
} // ! SyntaxCalcTree::result()



SyntaxCalcTree::SyntaxCalcTree(const vector<string> & tokens)
{
	// Синтаксический анализ. Создание дерева вычислений из массива лексем

	// Разбиваем список лексем на пары, начиная с первого оператора, предполагаем корректный ввод
	
	a = b = nullptr;  // Заглушка

} // ! SyntaxCalcTree::SyntaxCalcTree(const vector<string> & )


