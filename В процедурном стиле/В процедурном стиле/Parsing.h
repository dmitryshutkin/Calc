#ifndef PARSING
#define PARSING

#pragma once

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3


extern char *prog;   // содержит анализируемое выражение 

void parse(double *);

#endif