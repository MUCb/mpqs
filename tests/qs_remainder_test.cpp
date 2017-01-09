#define BOOST_TEST_MODULE QS remainder Test
#include <boost/test/included/unit_test.hpp> 


#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

int showDebugMsg = 3;

BOOST_AUTO_TEST_CASE(test_1) 
{
    for (int iter = 15; iter < 16 ; iter++) {
        uint64_t p = prime[iter];
        uint64_t q = prime[31];

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

        for (int i = 2; p_smooth.size() < 20; ++i)
        {
            p_smooth.push_back(prime[i]);
        }
        DEBUG(2, "p_smooth size %d\n", p_smooth.size());

        // make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            ERROR ("to small primes \n");
            exit;
        }

        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);

        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
        
        // *** construct our sieve *** //
        
        std::vector<long> X;
        std::vector<long> Y;
        for (k = 1; k < 3; ++k)
        {
            std::vector<long> X1;
            std::vector<long> Y1;
            sqrt_Nk = trunc(sqrt(N * k)) + 1;
            construct_xy(X1, Y1, sqrt_Nk, N, M);
            X.insert(X.end(), X1.begin(), X1.end());
            Y.insert(Y.end(), Y1.begin(), Y1.end());
            
        }

        for (uint64_t i = 0; i < X.size(); ++i)
        {
            DEBUG (2, "X = %llu\t",X[i]);
            DEBUG (2, "Y = %li\t",Y[i]);
            DEBUG (2, "\n");
        }
        
        DEBUG (2, "X size  = %d\n",X.size());
        // simple sieve 
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;
        DEBUG (2, "v_exp size  = %d\n",v_exp.size());

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }

        // std::vector<int> smooth_num_back = smooth_num;
        // bin_matrix_t m1(p_smooth.size() + 1);

        // BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}
