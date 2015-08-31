#include "MainDefinitions.h"
#include "CalcTree.h"
#include <iostream>
#include <string>
#include <locale>

using namespace std;



int main(void)
{
	// ������� ���������
	setlocale(LC_CTYPE, "");

	// �������� ������ ��� ��������
	string str = "";
	cout << "�����������" << endl << ">> ";
	getline(cin,str);
	
	// ������� � ����������
	CalcTree calcTree(str);  // ������������ ������ ����������

	// ����� ����������
	cout << endl << "���������: " << calcTree.result() << endl;
	
	// ���������� ����������
	cout << "�������� ������ - ��� �������� -1" << endl;

	// �����
	cin.get(); 
	
	// ������� ���������� ��
	return -1;  // �������� ������ - ��� �������� -1
}