#include <iostream>
#include <string>
#include "CalcTree.h"


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
	CalcTree calcTree(str);  // ������������ ������ ����������

	// ����� ����������
	cout << "\n���������:" << calcTree.result() << endl;
	cout << "�������� ������ - ��� �������� -1" << endl;
	cin.get(); cin.get();
	
	// ������� ���������� ��
	return -1;
}