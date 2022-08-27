#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cmath>

#include "Connectives.h"
#include "EvalType.h"
#include "TruthTable.h"

static int get_precedence(Connective con)
{
    return static_cast<int>(con);
}

static Connective get_iterative_connective_left(const std::string& str, int* pos)
{
    char c = str[*pos];
    switch(c)
    {
        case L'¬': return Connective::Negation;
        case L'∧':
        case '^': return Connective::And;
        case 'V':
        case 'v':
        case '|':
        case L'∨': return Connective::Or;
        case L'⊕':
        case 'X': return Connective::Exor;
        case L'→': return Connective::Implication;
        case L'↔': return Connective::Biconditional;

        case '-':
            if(str[*pos + 1] == '>')
            {
                (*pos)++;
                return Connective::Implication;
            }
            else return Connective::Negation;
        
        case '<':
            if(str[(*pos) + 1] == '-'
            && str[(*pos) + 2] == '>')
            {
                (*pos) += 2;
                return Connective::Biconditional;
            }
            else return Connective::NONE;
        default:
            return Connective::NONE;
    }
}

static Connective get_iterative_connective_right(const std::string& str, int* pos)
{
    char c = str[*pos];
    switch(c)
    {
        case '-':
        case L'¬': return Connective::Negation;
        case L'∧':
        case '^': return Connective::And;
        case 'V':
        case 'v':
        case '|':
        case L'∨': return Connective::Or;
        case L'⊕':
        case 'X': return Connective::Exor;
        case L'→': return Connective::Implication;
        case L'↔': return Connective::Biconditional;

        case '>':
            if(str[*pos - 1] == '-')
            {
                if(str[(*pos) - 2] == '<')
                {
                    (*pos) -= 2;
                    return Connective::Biconditional;
                }
                
                (*pos)--;
                return Connective::Implication;
            }

        default:
            return Connective::NONE;
    }
}

bool is_connective_unary(Connective con)
{
    return con == Connective::Negation;
}

char* substandard_connective_output(Connective c)
{
    switch(c)
    {
        case Connective::And: return "&";
        case Connective::Or: return "|";
        case Connective::Exor: return "";
        case Connective::Negation: return "-";
        case Connective::Implication: return "=>";
        case Connective::Biconditional: return "<=>";
        default: return "";
    }
}

wchar_t optimal_connective_character(Connective c)
{
    switch(c)
    {
        case Connective::And: return L'∧';
        case Connective::Or: return L'∨';
        case Connective::Exor: return L'⊕';
        case Connective::Negation: return L'¬';
        case Connective::Implication: return L'→';
        case Connective::Biconditional: return L'↔';
        default: return L' ';
    }
}

bool implication(bool p, bool q)
{
    if(p)
        return q;
    else
        return true;
}

bool biconditional(bool p, bool q)
{
    return implication(p, q) && implication(q, p);
}

static void recurse_pattern(const std::string& input, int left, int right, EvalType* current)
{

    int connective_position = -1;
    Connective con = Connective::VAR;
    for(int i = right - 1; i >= left; i--)
    {
        if(std::isspace(input[i]))
            continue;
        
        Connective _itercon = get_iterative_connective_right(input, &i);
        if(_itercon != Connective::NONE)
        {
            if(get_precedence(_itercon) > get_precedence(con))
            {
                con = _itercon;
                connective_position = i;
            }
        }
    }

    if(con == Connective::VAR)
    {
        // find connective variable and return
        // that sounds annoying I'll do that later
        for(int i = left; i < right; i++)
        {
            if(std::isalpha(input[i]))
            {
                connective_position = i;
                break;
            }
        }

        if(connective_position == -1)
        {
            std::cout << "Input is invalid" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        current->endpoint = input[connective_position];
        current->type = Connective::VAR;
        return;

    }

    current->type = con;

    current->right = new EvalType;
    get_iterative_connective_left(input, &connective_position);
    //std::cout << "Creating right node type " << input.substr(connective_position + 1, right - connective_position) << std::endl;
    recurse_pattern(input, connective_position + 1, right, current->right);

    
    if(is_connective_unary(con))
        return;

    current->left = new EvalType;
    get_iterative_connective_right(input, &connective_position);
    //std::cout << "Creating left node type " << input.substr(left, connective_position - left - 1) << std::endl;
    recurse_pattern(input, left, connective_position - 1, current->left);

}

TruthTable_t* parse_string(const std::string& input)
{
    std::vector<char> vars;
    
    EvalType* head = new EvalType;
    recurse_pattern(input, 0, input.length(), head);

    TruthTable_t* rv = new TruthTable_t(head);
    return rv;
}

void print_optimal_string(TruthTable_t* ttp)
{
    ttp->get_head()->PrintValue();
    //std::cout << std::endl << ttp->variable_count() << " variables.";
}

static void _cleanup_recursive(EvalType* et)
{
    if(et->right)
        _cleanup_recursive(et->right);
    if(et->left)
        _cleanup_recursive(et->left);
    
    delete et;
}

void print_atomic_table(TruthTable_t* ttp)
{
    ttp->print_atomic_table();
}

void cleanup_truthtable(TruthTable_t* ttp)
{
    _cleanup_recursive(ttp->get_head());
    delete ttp;
}

void print_truth_table(TruthTable_t* ttp)
{
    ttp->print_truth_table();
}