#include <iostream>
#include <string>

#include "algo.h"

int main()
{
    while(true)
    {
        std::string str;
        std::getline(std::cin, str);

        if(str == "")
            return 0;

        TruthTable_t* output = parse_string(str);
        print_truth_table(output);

        cleanup_truthtable(output);
    }
}