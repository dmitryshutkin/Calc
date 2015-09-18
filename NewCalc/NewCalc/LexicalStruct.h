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
	std::vector<Token> tokens;                                             // Массив лексем
	std::vector<Token>::const_iterator current;                            // Текущая лексема
	LexicalStruct(const std::string &);                                    // Конструктор объекта по строке, содержащей выражение, проводит лексический анализ строки
	void next();                                                           // Берем следующую лексему
private:
	LexicalStruct() { };                                                   // Запрещаем конструктор по умолчанию
};



class Token
{
public:
	std::string value;                                                    // Значение лексемы
	enum TokenType { undefined, delimiter, number, function };
	TokenType type;                                                       // Тип
	Token(const std::string & v, TokenType tt) :value(v), type(tt) { };
private:
	Token() { };
};

#endif