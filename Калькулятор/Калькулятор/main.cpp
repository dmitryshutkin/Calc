#include <iostream>
#include <string>
#include <locale>
#include "CalcTree.h"


using namespace std;

int main(void)
{
	// ������� ���������
	setlocale(LC_CTYPE, "");

	// �������� ������ ��� ��������
	string str = "";
	cout << "������� ������: ";
	getline(cin,str);
	cout << "�� ����� ������: " << str << endl;

	// ������� � ����������
	CalcTree calcTree(str);  // ������������ ������ ����������

	// ����� ����������
	cout << endl << "���������:" << calcTree.result() << endl;
	cout << "�������� ������ - ��� �������� -1" << endl;
	cin.get(); cin.get();
	
	// ������� ���������� ��
	return -1;  // �������� ������ - ��� �������� -1
}