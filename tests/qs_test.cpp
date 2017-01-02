#define BOOST_TEST_MODULE QS Test
#include <boost/test/included/unit_test.hpp> 


#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

int showDebugMsg = 1;

BOOST_AUTO_TEST_CASE(test_1) 
{
    for (int iter = 15; iter < 30 ; iter++) {
        uint64_t p = prime[iter];
        uint64_t q = prime[31];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
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
        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}


BOOST_AUTO_TEST_CASE(test_2) 
{
    for (int iter = 15; iter < 26 ; iter++) {
        uint64_t p = prime[iter];
        uint64_t q = prime[33];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        // size_B = size_B +2;   not working !!!!!!!!!!!!!!!!!
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            ERROR ("to small primes \n");
            exit;
        }

        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);
        M = M * 4 / 3;
        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

        // *** construct our sieve *** //
        std::vector<long> X;
        std::vector<long> Y;

        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;
        
        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);
        printf("matrix size %d\n", p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}



BOOST_AUTO_TEST_CASE(test_3) 
{
// Special test case size_B wa changed
    // for (int iter = 15; iter < 32 ; iter++) {
        uint64_t p = prime[26];
        // uint64_t p = prime[iter];
        uint64_t q = prime[33];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        // size_B = size_B +2;   not working !!!!!!!!!!!!!!!!!
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            ERROR ("to small primes \n");
            exit;
        }

        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);
        M = M * 4 / 3;
        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

        // *** construct our sieve *** //
        std::vector<long> X;
        std::vector<long> Y;

        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;
        
        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);
        printf("matrix size %d\n", p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    // }
}



BOOST_AUTO_TEST_CASE(test_4) 
{
    for (int iter = 27; iter < 32 ; iter++) {
        uint64_t p = prime[iter];
        uint64_t q = prime[33];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        // size_B = size_B +2;   not working !!!!!!!!!!!!!!!!!
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            ERROR ("to small primes \n");
            exit;
        }

        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);
        M = M * 4 / 3;
        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

        // *** construct our sieve *** //
        std::vector<long> X;
        std::vector<long> Y;

        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;
        
        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);
        printf("matrix size %d\n", p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}


BOOST_AUTO_TEST_CASE(test_5) 
{
    // Special test case size_B wa changed
        uint64_t p = prime[10];
        uint64_t q = prime[60];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        size_B = size_B +1;
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

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

        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }
        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    // }
}


BOOST_AUTO_TEST_CASE(test_6) 
{
    // Special test case size_B wa changed
        uint64_t p = prime[10];
        uint64_t q = prime[74];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        size_B = size_B +1;
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

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

        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    // }
}


BOOST_AUTO_TEST_CASE(test_7) 
{
    // special test case 
    // Do we need to delete exponennt if they are all zero
        uint64_t p = prime[27];
        uint64_t q = prime[26];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        // size_B = size_B +1;
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

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

        construct_xy(X, Y, sqrt_N, N, M);


        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            ERROR( "exit make_exp_array");
            exit; 
        }


        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
}
