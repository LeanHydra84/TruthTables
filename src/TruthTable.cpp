#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#include "Connectives.h"
#include "TruthTable.h"

#include "algo_pvt.h"

void TruthTable_t::read_variables_recurse(EvalType* cur)
{
    if(cur == nullptr) return;
    if(cur->isEndpoint()
    && std::find(variables.begin(), variables.end(), cur->endpoint) == variables.end())
    {
        if(!is_constant_variable(cur->endpoint)) non_const_variables++;
        variables.push_back(cur->endpoint);
        return;
    }
    read_variables_recurse(cur->left);
    read_variables_recurse(cur->right);
}

int TruthTable_t::xytoi(int r, int c)
{
    return (c + r * variable_count());
}

void TruthTable_t::assemble_atomic_table(bool* table, int r1, int r2, int c)
{
    int half = (r1 + r2) / 2;
    for(int i = r1; i < r2; i++)
    {
        int index = xytoi(i, c);
        if(variables[c] == 'T') table[index] = true;
        else if(variables[c] == 'F') table[index] = false;
        else table[index] = i < half;
    }
    
    if(c + 1 < variable_count())
    {
        if(is_constant_variable(variables[c]))
        {
            assemble_atomic_table(table, r1, r2, c + 1);
        }
        else
        {
            assemble_atomic_table(table, r1, half, c + 1);
            assemble_atomic_table(table, half, r2, c + 1);
        }
    }
}

TruthTable_t::TruthTable_t(EvalType* head) : variables(), head(head), non_const_variables(0)
{
    read_variables_recurse(head);
}

EvalType* TruthTable_t::get_head() { return head; }
int TruthTable_t::variable_count() { return variables.size(); }
int TruthTable_t::row_count() { return std::pow(2, non_const_variables); }

void TruthTable_t::print_truth_table()
{
    std::unordered_map<char, bool> map;
    bool* atomic_table = new bool[row_count() * variable_count()];
    assemble_atomic_table(atomic_table, 0, row_count(), 0);

    for(char c : variables)
        std::cout << " | " << c;
    std::cout << " | ";
    print_optimal_string(this);
    std::cout << std::endl;

    for(int i = 0; i < row_count(); i++)
    {
        for(int c = 0; c < variable_count(); c++)
        {
            map[variables[c]] = atomic_table[xytoi(i, c)];
            std::cout << " | " << (atomic_table[xytoi(i, c)] ? 'T' : 'F' );
        }

        bool value = head->Value(map);
        std::cout << " | " << (value ? 'T' : 'F') << std::endl;

    }

    delete[] atomic_table;
}

void TruthTable_t::print_atomic_table()
{
    bool* atomic_table = new bool[row_count() * variable_count()];
    assemble_atomic_table(atomic_table, 0, row_count(), 0);

    std::cout << std::endl;
    for(int r = 0; r < row_count(); r++)
    {
        for(int c = 0; c < variable_count(); c++)
        {
            std::cout << " | " << (atomic_table[xytoi(r, c)] ? 'T' : 'F');
        }
        std::cout << std::endl;
    }

    delete[] atomic_table;
}