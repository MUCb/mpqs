#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>


#include <unistd.h>

int showDebugMsg = 3;

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
    DEBUG (2,"size of factor base size_B=%f\n", size_B);

    // selecting smooth primes 
    std::vector<long> p_smooth;
    DEBUG (2,"smooth numbers\n");

    make_smooth_numbers(p_smooth, size_B, N);

    if ((p_smooth.size() < size_B))
    {
        ERROR ("to small primes \n");
        return 0;
    }

    // selecting the sieving interval
    uint32_t M;
    M = exp (sqrt (log(N) * log(log(N))) );
    M = pow(M , 3*sqrt(2)/4);
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

    int ret = make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number); 

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
                found = euclid_gcd( X, Y, tmp, p, q, N);
                if (found)
                    break;
            }
        }
    }
    solution_candidates_number.clear();
    if (found)
    {
        return 0;
    }

    if (ret == 0)
    {
        ERROR( "exit make_exp_array");
        exit; 
    }


    std::vector<int> smooth_num_back = smooth_num;
    bin_matrix_t m1(p_smooth.size() + 1);

    if (find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N) >= 0)
    {
        printf("Success\n");
        return 1;
    }
    else
    {
        printf("ERROR \n");
        return 0;
    }
}