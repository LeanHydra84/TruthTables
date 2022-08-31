#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "algo.h"

#define BREAK_ON_ERROR 1

int main()
{
    while(true)
    {
        std::string str;
        std::getline(std::cin, str);

        std::cout << std::setfill('T');

        if(str == "")
            return 0;

        if(!validate_grouping_symbols(str))
        {
            std::cout << "Invalid grooming symbols" << std::endl;
#if BREAK_ON_ERROR
            exit(EXIT_FAILURE);
#else
            continue;
#endif
        }
    
        size_t pos = str.find('=');
        if(pos == std::string::npos)
        {
            TruthTable_t* output = parse_string(str);
            print_truth_table(output);

            cleanup_truthtable(output);
        }
        else
        {
            std::string firsthalf = str.substr(0, pos);
            std::string secondhalf = str.substr(pos + 1);

            if(firsthalf.length() == 0 || secondhalf.length() == 0)
            {
                std::cout << "Invalid equals sign." << std::endl;
#if BREAK_ON_ERROR
                exit(EXIT_FAILURE);
#else
                continue;
#endif
            }

            TruthTable_t* first = parse_string(firsthalf);
            TruthTable_t* second = parse_string(secondhalf);

            print_truth_table_comparison(first, second);

            cleanup_truthtable(first);
            cleanup_truthtable(second);

        }

    }
}