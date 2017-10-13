#define BOOST_TEST_MODULE QS unit maytrix Test
#include <boost/test/included/unit_test.hpp> 


#include "dynamic_bin_matrix.h"
// #include "primes.h"
#include "quadratic_sieve.h"
#include "log.h"

#include "greatest_common_divisor.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

 #include <math.h>
#include <time.h>

int showDebugMsg = 3;

BOOST_AUTO_TEST_CASE(test_2) 
{
    int iter = 0;
    int iter_1 = 0;
// for (int iter1 = 5; iter1 < 70 ; iter1++) {
    // for (int iter = iter1 + 1; iter < 70 ; iter++) 
    {

        time_t start;
        time_t finish;
        start = clock();
        
        uint64_t p = prime[900]; // k = 3 p = 10
        uint64_t q = prime[500];

        // uint64_t p = prime[1200]; // k = 3 p = 10
        // uint64_t q = prime[1450];


        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        uint64_t sqrt_Nk = 0;
        uint64_t k = 1;
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
            DEBUG (0, "Fail solution i=%d\tj=%d p=%lu\tq=%lu\t", iter, iter_1, p, q);
            finish = clock();
            DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
            // continue;
            exit (0);
        }
        std::vector<long> p_smooth_copy = p_smooth;


        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);

        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
        
        // *** construct our sieve *** //
        std::vector<long> X;
        std::vector<long> Y;
        construct_xy(X, Y, sqrt_N, N, M);


        DEBUG (2, "X size  = %lu\n",X.size());
        

        // simple sieve 
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        // std::vector< std::vector<uint64_t> > v_exp_copy(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        // std::vector<uint64_t> v_extra_exp(Y.size()) ;
        std::vector<int> smooth_num;
        DEBUG (2, "v_exp size  = %lu\n",v_exp.size());

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            // check the solution candidate 
            // we skip this for now
        }



        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        int find_res = find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
        BOOST_CHECK(find_res   >= 0);
        if(find_res >= 0)
        {
            DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
        finish = clock();
        DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        } else {
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
                    finish = clock();
        DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        }
        
    }
}