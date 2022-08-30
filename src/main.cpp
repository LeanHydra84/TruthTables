#include <iostream>
#include <string>

#include "algo.h"

#define BREAK_ON_GROUPING_ERROR 1

int main()
{
    while(true)
    {
        std::string str;
        std::getline(std::cin, str);

        if(str == "")
            return 0;

        if(!validate_grouping_symbols(str))
        {
            std::cout << "Invalid grouping symbols";
#if BREAK_ON_GROUPING_ERROR
            exit(EXIT_FAILURE);
#else
            continue;
#endif
        }

        TruthTable_t* output = parse_string(str);
        print_truth_table(output);

        cleanup_truthtable(output);
    }
}