#ifndef CALCOPERATION
#define CALCOPERATION

#pragma once


class CalcTree;

class CalcOperation
{
public:
	int operator() (CalcTree *, CalcTree *);
};

#endif