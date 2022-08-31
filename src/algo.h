#ifndef _ALGO_H_
#define _ALGO_H_

class TruthTable_t;
TruthTable_t* parse_string(const std::string& input);

void print_truth_table(TruthTable_t* ttp);
void print_truth_table_comparison(TruthTable_t* first, TruthTable_t* second);
void print_optimal_string(TruthTable_t* ttp);
void cleanup_truthtable(TruthTable_t* ttp);
void print_atomic_table(TruthTable_t* ttp);
bool validate_grouping_symbols(const std::string& input);

#endif