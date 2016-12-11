#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>

#include "bin_matrix.h"

#include <unistd.h>

// const int showDebugMsg = 3;

#define PRIME_SIZE 75
 uint64_t prime[PRIME_SIZE] = { 0,  1,    2,            
        3,         5,         7,        11,        13,        17,        19,        23, 
       29,        31,        37,        41,        43,        47,        53,        59, 
       61,        67,        71,        73,        79,        83,        89,        97, 
      101,       103,       107,       109,       113,       127,       131,       137, 
      139,       149,       151,       157,       163,       167,       173,       179, 
      181,       191,       193,       197,       199,       211,       223,       227, 
      229,       233,       239,       241,       251,       257,       263,       269, 
      271,       277,       281,       283,       293,       307,       311,       313,    
      317,       331,       337,       347,       349,       353,       359,       367 };  




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
    DEBUG (1,"p=%"PRIu64"\tq=%"PRIu64"\tp*q=N=%"PRIu64"\n", p, q, N);
    
    // take square root of N 
    {
        double tmp = sqrt(N);
        if(tmp == trunc(tmp)) 
        {
            printf("<<<[FACTOR]>>> %"PRIu64"\n", N);
            exit(0);
        }
        else
        {
            sqrt_N = trunc(tmp) + 1;
        }
        DEBUG (2,"sqrt of N = %"PRIu64"\n",sqrt_N );
    }

    // selecting the size of the factor base
    double size_B;
    size_B = exp (sqrt (log(N) * log(log(N))) );
    size_B = pow(size_B , sqrt(2)/4);
    DEBUG (2,"size of factor base size_B=%f\n", size_B);
    // case for test 2 
    //*********  test1  **************
    //********************************
    //*********  test2  **************
    // size_B = size_B + 2;
    // size_B = size_B +1;
    //********************************

    // selecting smooth primes 
    std::vector<long> p_smooth;
    DEBUG (2,"smooth numbers\n");

    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);
    DEBUG (2,"%"PRIu64"\n", prime[2]);

    for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < PRIME_SIZE); ++i)
    {
        uint64_t tmp = N;
        for (int j = 1; j < (prime[i]-1)/2; ++j)
        {
            tmp = (tmp * N) % prime[i];
        }
        tmp %= prime[i];
        // printf("tmp %"PRIu64"\n", tmp);

        if( tmp == 1)
        {
            p_smooth.push_back(prime[i]);
            DEBUG (2,"%"PRIu64"\n", prime[i]);
        }
        // break;
    }

    if ((p_smooth.size() < size_B))
    {
        ERROR ("to small primes \n");
        return 0;
    }

    // selecting the sieving interval
    uint32_t M;
    M = exp (sqrt (log(N) * log(log(N))) );
    M = pow(M , 3*sqrt(2)/4);
    // M *= 2;
    // M += 20;
    DEBUG (1,"The sieving interval M=%"PRIu32"\n", M);


    // *** construct our sieve *** //
    std::vector<long> X;

    for (uint64_t i = M/2; i > 0; i = i - 1)
    {
        // if ((sqrt_N+i) == 180)
            // continue;
        X.push_back(sqrt_N - i);
        DEBUG (3,"X%"PRIu64" =%"PRIu64"\n",i, sqrt_N - i );
        // sleep(1000);
    }

    /* fill in  sqrt(N) + 1 sqrt(N) + 2  sqrt(N) + 3 .....*/
    for (uint64_t i = 0; i <= M/2; ++i)
    {
        // if ((sqrt_N+i) == 180)
            // continue;
        X.push_back(sqrt_N + i);
        DEBUG (3,"X%"PRIu64" =%"PRIu64"\n",i, sqrt_N + i );
    }



    DEBUG (2,"\n");
    std::vector<long> Y;
    // fill in  (Xi)^2 - N 
    for (uint64_t i = 0; i < X.size(); ++i)
    {
        DEBUG (2,"X = %"PRIu64"\t",X[i]);
        Y.push_back(X[i]*X[i] - N);
        DEBUG (2,"Y = %li\t",Y[i]);
        DEBUG (2,"\n");
    }
    // simple sieve 
    std::vector<long> V;
    V = Y;
    std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;

    // add sign to exponent matrix
    #define NEGATIVE_SIGN    0 
    #define FIRST_VALUE    1
    // v_exp[i].size()-1
    for (int y_number = 0; y_number < v_exp.size(); ++y_number)
    {
        if(Y[y_number] < 0 )
            v_exp[y_number][NEGATIVE_SIGN] = 1;
    }

    for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                smooth_iter < p_smooth.size(); 
                smooth_iter++, exponent_num++)
    {
        for (int y_num = 0; y_num < M; ++y_num)
        {
            if(V[y_num] == -1 || V[y_num] == 1)
                continue;

            long int tmp;
            do{
                tmp = V[y_num] % p_smooth[smooth_iter];
                DEBUG (3,"v = %10li\t",V[y_num]);
                DEBUG (3,"p_smooth = %li\t",p_smooth[smooth_iter]);
                DEBUG (3,"tmp = %li\n",tmp);
                if(tmp == 0){
                    V[y_num] = V[y_num] / p_smooth[smooth_iter];
                    v_exp[y_num][exponent_num] += 1; 
                }
            } while (tmp == 0);
        }
        // break;
    }
    std::vector<int> smooth_num;
    std::vector<long> solution_candidates_number;
    // std::vector<uint64_t> P11;
    for (int y_num = 0; y_num < V.size(); ++y_num)
    {
        int null_flag = 1;
        // printf("V = %"PRIu64"\t",V[i]);
        if(V[y_num] == 1 || V[y_num] == -1)
        {
            for (   int exponent_num = FIRST_VALUE;
                        exponent_num < v_exp[y_num].size(); 
                        exponent_num++ )
            {
                DEBUG (3,"%ld\t", v_exp[y_num][exponent_num]);
                if ((v_exp[y_num][exponent_num] % 2 )!= 0)
                    null_flag = 0;
            }
            DEBUG (3,"%ld\n", Y[y_num]);
            // skip negative value !!!!
            if (null_flag && V[y_num] > 0) {
                solution_candidates_number.push_back(y_num);
            } else {
                smooth_num.push_back(y_num);
            }
        }
    }
    DEBUG (3,"\n");

    uint64_t found = 0;
    
    if (solution_candidates_number.size() > 0)
    {
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

    return 0;
    


    if (smooth_num.size()  < size_B + 1)
    {
        ERROR( "to small number of smooth numbbers\n");
        return 0; 
    }

    // just print exponent array
    // for (int i = 0; i < V.size(); ++i)
    // {
    //  for (int j = 0; j < p_smooth.size(); ++j)
    //  {
    //      printf("%"PRIu64"\t", v_exp[i][j]);
    //  }
    //  printf("\n");
    // }

    std::vector<int> smooth_num_back = smooth_num;
    bin_matrix_t m1(p_smooth.size() + 1);
    // m1.show();
    // for (int i = 0; i < m1.m_size() + 1; ++i)
    // {
    //     // unit_num[i] = 0;
    //     m1.filled++;
    //     for (int j = 0; j < m1.m_size(); ++j)
    //     {
    //         if(i == j)
    //             m1.matrix[i][j] = 1;
    //         else
    //             m1.matrix[i][j] = 0;

    //         // DEBUG (3,"%"PRIu64"\t", unit_matrix[i][j]);
    //     }
    //     // DEBUG (3,"\n");
    // }
    // m1.filled++;
    // m1.matrix[6][1] = 1;
    // m1.matrix[6][4] = 1;
    // m1.show();
    // int null_line = m1.resolve_matrix();
    // m1.show();
    // printf("null_line %d\n",null_line );
    // m1.show();

    // find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);

    printf("\n");
    printf("exit\n");
    exit (0);

    return 0;
}