#ifndef _ALGO_H_
#define _ALGO_H_

class TruthTable_t;
TruthTable_t* parse_string(const std::string& input);
void print_truth_table(TruthTable_t* ttp);
void print_optimal_string(TruthTable_t* ttp);
void cleanup_truthtable(TruthTable_t* ttp);
void print_atomic_table(TruthTable_t* ttp);

#endif