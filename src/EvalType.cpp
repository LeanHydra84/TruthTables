#include <unordered_map>
#include <stdexcept>
#include <iostream>

#include "Connectives.h"
#include "EvalType.h"

#include "algo_pvt.h"

EvalType::EvalType() : endpoint(NOT_AN_ENDPOINT), type(Connective::NONE), left(nullptr), right(nullptr) { }

bool EvalType::Value(std::unordered_map<char, bool>& atomic_values)
{
    if(isEndpoint())
    {
        return atomic_values[endpoint];
    }

    
    bool l = false, r = false;
    if(left) l = left->Value(atomic_values);
    if(right) r = right->Value(atomic_values);
    switch(type)
    {
        case Connective::And: return l && r;
        case Connective::Or: return l || r;
        case Connective::Exor: return l != r;
        case Connective::Negation: return !r;
        case Connective::Implication: return implication(l, r);
        case Connective::Biconditional: return biconditional(l, r);
        default:
            std::cout << "Value called on unresolvable connective" << std::endl;
            exit(EXIT_FAILURE);
    }
}

void EvalType::PrintValue()
{
    if(isEndpoint())
    {
        std::cout << endpoint;
        return;
    }

    if(!is_connective_unary(type))
    {
        left->PrintValue();
        std::cout << " " << substandard_connective_output(type) << " ";
    }
    else
        std::cout << substandard_connective_output(type);

    right->PrintValue();
}

bool EvalType::isEndpoint() { return endpoint != NOT_AN_ENDPOINT; }