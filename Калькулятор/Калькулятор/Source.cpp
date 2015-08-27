#include <iostream>
#include <string>
#include "CalculationTree.h"


using namespace std;

int main(void)
{
	// ������� ���������
	setlocale(LC_CTYPE, "");

	// �������� ������ ��� ��������
	string str = "";
	cout << "������� ������: ";
	cin >> str;
	cout << "�� ����� ������: " << str << endl;

	// ������� � ����������
	CalculationTree calc(str);  // ������������ ������ ����������

	// ����� ����������
	cout << "\n���������:" << calc.result() << endl;

	// ������� ���������� ��
	cout << "�������� ��������. ��� �������� -1" << endl;
	cin.get(); cin.get();
	return -1;
}