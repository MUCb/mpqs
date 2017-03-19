#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>


#include <unistd.h>

int showDebugMsg = 3;

// #define PRIME_SIZE 75
//  uint64_t prime[PRIME_SIZE] = { 0,  1,    2,            
//         3,         5,         7,        11,        13,        17,        19,        23, 
//        29,        31,        37,        41,        43,        47,        53,        59, 
//        61,        67,        71,        73,        79,        83,        89,        97, 
//       101,       103,       107,       109,       113,       127,       131,       137, 
//       139,       149,       151,       157,       163,       167,       173,       179, 
//       181,       191,       193,       197,       199,       211,       223,       227, 
//       229,       233,       239,       241,       251,       257,       263,       269, 
//       271,       277,       281,       283,       293,       307,       311,       313,    
//       317,       331,       337,       347,       349,       353,       359,       367 };  

#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "log.h"
#include "greatest_common_divisor.h"
#include "primes.h"

int main (int argc, char *argv[])
{

    uint64_t p;
    uint64_t q;

    int p_idx;
    int q_idx;
    if (argc == 3)
    {

        p_idx = atol(argv[1]);
        q_idx = atol(argv[2]);
        DEBUG (2,"p_idx=%d\t", p_idx);
        DEBUG (2,"q_idx=%d\n", q_idx);
    }
    else {
        printf("USAGE: %s p q\n", argv[0]);
    }
    // return 0;
//*********  test1  **************
    // p = prime[28];
    // q = prime[36];// found 1 element in matrix
//********************************

//*********  test2  **************
    // p = prime[35];
    // q = prime[52];
//********************************

// *********  test3  **************
    // p = prime[35];
    // q = prime[53];
//********************************
    p = prime[p_idx];
    q = prime[q_idx];

    uint64_t N = p * q; //15347;
    uint64_t sqrt_N = 0;
    DEBUG (1,"p=%llu\tq=%llu\tp*q=N=%llu\n", p, q, N);
    
    // take square root of N 
    {
        double tmp = sqrt(N);
        if(tmp == trunc(tmp)) 
        {
            printf("<<<[FACTOR]>>> %llu\n", N);
            exit(0);
        }
        else
        {
            sqrt_N = trunc(tmp) + 1;
        }
        DEBUG (2,"sqrt of N = %llu\n",sqrt_N );
    }

    // selecting the size of the factor base
    double size_B;
    size_B = exp (sqrt (log(N) * log(log(N))) );
    size_B = pow(size_B , sqrt(2)/4);
    // size_B += 10;
    DEBUG (2,"size of factor base size_B=%f\n", size_B);

    // selecting smooth primes 
    std::vector<long> p_smooth;
    DEBUG (2,"smooth numbers\n");

    make_smooth_numbers(p_smooth, size_B, N);

    if ((p_smooth.size() < size_B))
    {
        ERROR ("to small primes \n");
        DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", p_idx, q_idx, p, q);
        return 0;
    }

    std::vector<long> p_smooth_copy = p_smooth;
    

    // selecting the sieving interval
    uint32_t M;
    M = exp (sqrt (log(N) * log(log(N))) );
    M = pow(M , 3*sqrt(2)/4);
    // M *= 5;
    DEBUG (1,"The sieving interval M=%llu\n", M);


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
                    found = euclid_gcd( X, Y, tmp, p, q, N, v_exp, p_smooth);
                    if (found)
                        break;
                }
            }
        }
        solution_candidates_number.clear();
        if (found)
        {
            DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", p_idx, q_idx, p, q);
            return 0;
        }

        ERROR( "exit make_exp_array");
        DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", p_idx, q_idx, p, q);
        // exit (0); 
        return 0;
    }



    std::vector<int> smooth_num_back = smooth_num;
    bin_matrix_t m1(p_smooth.size() + 1);

    if (find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy ,X, Y, p, q, N) >= 0)
    {
        printf("Success\n");
        DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", p_idx, q_idx, p, q);
        return 1;
    }
    else
    {
        printf("ERROR \n");
        DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", p_idx, q_idx, p, q);
        return 0;
    }


}