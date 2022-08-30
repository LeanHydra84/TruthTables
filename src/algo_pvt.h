#ifndef _ALGO_PVT_H_
#define _ALGO_PVT_H_

#include "algo.h"
#include "Connectives.h"

bool implication(bool p, bool q);
bool biconditional(bool p, bool q);

const char* substandard_connective_output(Connective c);
wchar_t optimal_connective_character(Connective c);
bool is_connective_unary(Connective con);
bool is_constant_variable(char c);

#endif