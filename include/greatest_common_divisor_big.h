#ifndef GCD
#define GCD


//Euclid's Algorithm, Greatest Common Divisor
big_2 euclid_gcd_big(const std::vector<big_2>& X,
                    const std::vector<big_2>& Y,
                    const std::vector<int64_t>& iterator,
                    const big_2 &p,
                    const big_2 &q,
                    const big_2 &N,
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
