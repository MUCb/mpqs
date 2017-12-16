#ifndef QS
#define QS

#include "big_2.h"

extern long long  prime[];
extern const int prime_size;


int fill_matrix(bin_matrix_t & m1, std::vector<int> &smooth_num, std::vector< std::vector<uint64_t> > &v_exp);

int find_solution_big (bin_matrix_t & m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    std::vector<long long> p_smooth,
                    const std::vector<big_2>& X,
                    const std::vector<big_2>& Y,
                    const big_2 &p,
                    const big_2 &q,
                    const big_2 &N);
/*
int find_solution_condBsmooth (bin_matrix_t m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    std::vector<long> p_smooth,
                    const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N,
                    std::vector<uint64_t> &v_extra_exp);
*/
void make_smooth_numbers(std::vector<long long > &p_smooth, double size_B,const big_2 N);

void construct_xy(std::vector<big_2> &X, std::vector<big_2> &Y, big_2 sqrt_N, big_2 N, long long M);
int make_exp_array(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<big_2> V, std::vector<long long> &p_smooth, double size_B, long long  M,  std::vector<long long> &solution_candidates_number);
int make_exp_array_condBsmooth(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> Y, std::vector<long> &p_smooth, double size_B, uint32_t M,
    std::vector<long> &solution_candidates_number, std::vector<uint64_t> &v_extra_exp);
int make_exp_array_condBsmooth_1(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> Y, std::vector<long> &p_smooth, double size_B, uint32_t M,
    std::vector<long> &solution_candidates_number, std::vector<uint64_t> &v_extra_exp);

int zero_vector_mod2_check(std::vector<uint64_t> v_exp);
void add_counter_row(bin_matrix_t &m2 ,std::vector<uint64_t> &counter ,int exponent_num);
int is_counter_full(std::vector<uint64_t> &counter);
big_2 prime_factorisation(big_2  Y, std::vector<long long> p_smooth, std::vector<uint64_t> &v_exp);
#endif
