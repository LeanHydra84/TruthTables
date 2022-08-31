#ifndef _TRUTHTABLE_H_
#define _TRUTHTABLE_H_

#include <vector>
#include "EvalType.h"

class TruthTable_t
{
private:

    std::vector<char> variables;
    EvalType* head;
    int non_const_variables;

private:
    void read_variables_recurse(EvalType* cur);
    int xytoi(int r, int c);
    void assemble_atomic_table(bool* table, int r1, int r2, int c);

public:
    TruthTable_t(EvalType* head);

    EvalType* get_head();
    int variable_count();
    int row_count();

    void print_truth_table();
    void print_atomic_table();
    bool print_comparison(TruthTable_t* other);

};

#endif