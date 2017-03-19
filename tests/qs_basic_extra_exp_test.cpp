#define BOOST_TEST_MODULE QS Test
#include <boost/test/included/unit_test.hpp> 


#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "log.h"
#include "greatest_common_divisor.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

int showDebugMsg = 0;


//   5k - 6k
// Fail 35056
// Found 464444

// found   492363
// Found   499500


// 4k - 5k
// Fail 36918
// Found 462582

// found 491887
// Found  499500  -- 98%


// 1 - 2k
// Fail 207525
// Found 1785481

// Fail  58416  --- 3.019%
// found 1868348
// Found 1934590


// 1 - 5k
// Fail 1228642
// Found 11253864

// Fail  403271 ----- 3.33%
// found 12008247 ---- 99.4%
// Found 12079235


// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Fail.*j=4[0-9][0-9][0-9]" | wc -l
// 36918
// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Fail.*j=3[0-9][0-9][0-9]" | wc -l
// 68589
// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Fail.*j=2[0-9][0-9][0-9]" | wc -l
// 238567
// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Fail.*j=1[0-9][0-9][0-9]" | wc -l
// 463851



// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Found.*j=4[0-9][0-9][0-9]" | wc -l
// 499500
// 13.52
// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Found.*j=3[0-9][0-9][0-9]" | wc -l
// 2230409
// 32.51
// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Found.*j=2[0-9][0-9][0-9]" | wc -l
// 4760433
// 19.95
// vmisko@kv-1223:~/shared$ cat ./res_qs_basic_extra__ | grep -rin "Found.*j=1[0-9][0-9][0-9]" | wc -l
// 6535149
// 14.08




BOOST_AUTO_TEST_CASE(test_0) 
{
    int first_flag = 1;
    // for (int iter_1 = 10; iter_1 < 11; iter_1++) 
    for (int iter_1 = 3; iter_1 < 5000 ; iter_1++) 
    {

    for (int iter = iter_1+1; iter < 5000 ; iter++) 
    // for (int iter = 13; iter < 14 ; iter++) 
    {
        // uint64_t p = prime[461];
        // uint64_t q = prime[15];
        // uint64_t p = prime[147];
        // iter = 40;
        // iter_1 = 14;

        // if(first_flag)
        // {
        //     first_flag = 0;
        //     iter = 6569;
        //     iter_1 = 3905;
        // }

            // iter = 5100;
            // iter_1 = 5000;
        uint64_t p = prime[iter_1];
        uint64_t q = prime[iter];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "i=%d\tj=%d\n", 147, iter_1 );
        // DEBUG (1, "i=%d\tj=%d\n", iter, iter);
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            ERROR ("to small primes \n");
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
            continue;
            // exit (0);
        }
        std::vector<long> p_smooth_copy = p_smooth;
        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);
        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

        // *** construct our sieve *** //
        std::vector<long> X;
        std::vector<long> Y;
        construct_xy(X, Y, sqrt_N, N, M);


        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        // std::vector<uint64_t> v_extra_exp(Y.size()) ;
        std::vector<uint64_t> v_extra_exp(Y.size()) ;
        std::vector<int> smooth_num;

        int array_res = make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number, v_extra_exp);

        uint64_t found = 0;
            if (solution_candidates_number.size() > 0)
            {
                // to check functionality use  ./qs_3.out 27 10
                DEBUG (3,"%s:%d\n", __func__, __LINE__);
                for (int i = 0; i <  solution_candidates_number.size(); ++i)
                {
                    DEBUG (3,"check %ld\n", Y[solution_candidates_number[i]]);

                    if ( Y[solution_candidates_number[i]] > 0 ){

                        std::vector<int64_t> tmp;
                        tmp.push_back(solution_candidates_number[i]);
                        found = euclid_gcd_m( X, Y, tmp, p, q, N, v_exp, p_smooth, v_extra_exp);
                        if (found)
                            break;
                    }
                }
            }
            solution_candidates_number.clear();
            if (found)
            {
                DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", iter, iter_1, p, q);
                continue;
            }

        if (array_res == 0)
        {
            ERROR( "exit make_exp_array_extra");
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
            continue;
            // exit (0); 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        int find_res = find_solution_extra(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N, v_extra_exp);
        // int find_res = find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
        BOOST_TEST( find_res  >= 0);
        if(find_res >= 0)
        {
            DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t %d\n", iter, iter_1, p, q,find_res);
        } else {
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
        }
        // break;
    }
    // break;
    }
}

