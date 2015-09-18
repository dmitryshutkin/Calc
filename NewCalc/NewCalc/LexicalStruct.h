#ifndef LEXICALSTRUCT
#define LEXICALSTRUCT

#include "Main.h"

#pragma once

#include <string>
#include <vector>




class Token;



class LexicalStruct
{
public:
	std::vector<Token> tokens;                                             // ������ ������
	std::vector<Token>::const_iterator current;                            // ������� �������
	LexicalStruct(const std::string &);                                    // ����������� ������� �� ������, ���������� ���������, �������� ����������� ������ ������
	void next();                                                           // ����� ��������� �������
private:
	LexicalStruct() { };                                                   // ��������� ����������� �� ���������
};



class Token
{
public:
	std::string value;                                                    // �������� �������
	enum TokenType { undefined, delimiter, number, function };
	TokenType type;                                                       // ���
	Token(const std::string & v, TokenType tt) :value(v), type(tt) { };
private:
	Token() { };
};

#endif