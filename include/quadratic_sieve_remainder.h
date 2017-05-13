#ifndef QS
#define QS


extern long long  prime[];
extern const int prime_size;


int fill_matrix(bin_matrix_t &m1, std::vector<int> &smooth_num, std::vector< std::vector<uint64_t> > &v_exp);

int find_solution (bin_matrix_t m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N);

void make_smooth_numbers(std::vector<long> &p_smooth, double size_B, uint64_t N);

void construct_xy(std::vector<long> &X, std::vector<long> &Y, uint64_t sqrt_N, uint64_t N, uint32_t M);
int make_exp_array(bin_matrix_t m2, std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> V, std::vector<long> &p_smooth, double size_B, uint32_t M,  std::vector<long> &solution_candidates_number);


long prime_factorisation(long  Y, std::vector<long> p_smooth, std::vector<uint64_t> &v_exp);
int delete_counter_row(bin_matrix_t &m2 ,std::vector<uint64_t> &counter , int max_i);
int clean_matrix(bin_matrix_t &m_all, bin_matrix_t &m_all_copy, std::vector<int> &smooth_num, int max_i);
int zero_vector_mod2_check(std::vector<uint64_t> v_exp);
int add_counter_row(bin_matrix_t &m2 ,std::vector<uint64_t> &counter ,int exponent_num);
#endif