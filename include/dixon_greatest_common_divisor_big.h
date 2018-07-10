#ifndef GCD
#define GCD


//Euclid's Algorithm, Greatest Common Divisor
big dixon_euclid_gcd_big(const std::vector<big>& X,
                    const std::vector<big>& Y,
                    const std::vector<int64_t>& iterator,
                    const big &p,
                    const big &q,
                    const big &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long long> p_smooth,
					double size_B
                );
#endif
