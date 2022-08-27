#ifndef _EVALTYPE_H_
#define _EVALTYPE_H_

#include "Connectives.h"

struct EvalType
{
    char endpoint;
    Connective type;
    
    EvalType* left;
    EvalType* right;

    EvalType();

    bool Value(std::unordered_map<char, bool>& atomic_values);
    void PrintValue();
    bool isEndpoint();
};

#endif