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
int make_exp_array(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> V, std::vector<long> &p_smooth, double size_B, uint32_t M,  std::vector<long> &solution_candidates_number);
#endif