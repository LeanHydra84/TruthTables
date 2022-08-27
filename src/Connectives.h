#ifndef _CONNECTIVES_H_
#define _CONNECTIVES_H_

#define NOT_AN_ENDPOINT -1

enum class Connective
{
    NONE,
    VAR,
    Negation,
    And,
    Or,
    Exor,
    Implication,
    Biconditional,
};

#endif