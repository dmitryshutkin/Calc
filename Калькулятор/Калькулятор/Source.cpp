#include <iostream>
#include <string>

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
	// �������

	// ������� ���������� ��
	cout << "�������� ��������. ��� �������� -1" << endl;
	cin.get(); cin.get();
	return -1;
}