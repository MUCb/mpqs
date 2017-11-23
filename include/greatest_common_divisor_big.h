#ifndef GCD
#define GCD


//Euclid's Algorithm, Greatest Common Divisor
big euclid_gcd_big(const std::vector<big>& X,
                    const std::vector<big>& Y,
                    const std::vector<int64_t>& iterator,
                    const big &p,
                    const big &q,
                    const big &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long long> p_smooth
                );

uint64_t euclid_gcd_m(const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const std::vector<int64_t>& iterator,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long> p_smooth,
                    std::vector<uint64_t> v_extra_exp
                );

#endif