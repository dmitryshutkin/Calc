#ifndef CALCOPERATION
#define CALCOPERATION
#pragma once

#include "MainDefinitions.h"



class SyntaxCalcTree;

class SyntaxCalcOperation
{
public:
	int operator() (SyntaxCalcTree *, SyntaxCalcTree *);
};

#endif