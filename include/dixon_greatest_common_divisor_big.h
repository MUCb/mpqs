#ifndef GCD
#define GCD


//Euclid's Algorithm, Greatest Common Divisor
big_2 dixon_euclid_gcd_big(const std::vector<big_2>& X,
                    const std::vector<big_2>& Y,
                    const std::vector<int64_t>& iterator,
                    const big_2 &p,
                    const big_2 &q,
                    const big_2 &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long long> p_smooth,
					double size_B
                );
#endif
