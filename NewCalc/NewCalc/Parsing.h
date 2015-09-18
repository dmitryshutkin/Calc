#ifndef PARSING
#define PARSING

#include "Main.h"
#include "LexicalStruct.h"

#pragma once
#include <string>





class Parsing
{

public:

	double operator() (const std::string &);

	double operator() (const char * const);


private:

	// ������� ����������� ��������� ���������
	// ������� �������:
	// ����� -> ������������ -> ������� -> ������� �������� -> ������� -> ��������� � ������� -> �����

	double expr_sum_mult_pow_sign_func_brackets_atom(LexicalStruct &);   // ����� + ������������ + ������� + ������� �������� + ������� + ��������� � ������� + �����
	double expr_mult_pow_sign_func_brackets_atom(LexicalStruct &);       // ������������ + ������� + ������� �������� + ������� + ��������� � ������� + �����
	double expr_pow_sign_func_brackets_atom(LexicalStruct &);            // ������� + ������� �������� + ������� + ��������� � ������� + �����
	double expr_sign_func_brackets_atom(LexicalStruct &);                // ������� �������� + ������� + ��������� � ������� + �����
	double expr_func_brackets_atom(LexicalStruct &);                     // ������� + ��������� � ������� + �����
	double expr_brackets_atom(LexicalStruct &);                          // ��������� � ������� + �����
	double expr_atom(LexicalStruct &);                                   // ����� --- ����� �� ������������ ������ �� ������� �������


};

extern Parsing parse;

#endif