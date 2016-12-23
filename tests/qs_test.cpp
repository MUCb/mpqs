#define BOOST_TEST_MODULE QS Test
#include <boost/test/included/unit_test.hpp> 


#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


int showDebugMsg = 4;

BOOST_AUTO_TEST_CASE(test_1) 
{
    for (int iter = 15; iter < 16 ; iter++) {
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

        //prime is 2 - special case 
        // Modulo 2, every integer is a quadratic residue.
        p_smooth.push_back(prime[2]);

        for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < PRIME_SIZE); ++i)
        {
            uint64_t tmp = N;
            for (int j = 1; j < (prime[i]-1)/2; ++j)
            {
                tmp = (tmp * N) % prime[i];
            }
            tmp %= prime[i];

            if( tmp == 1)
            {
                p_smooth.push_back(prime[i]);
                DEBUG (2, "%" PRIu64 "\n", prime[i]);
            }
        }

        if ((p_smooth.size() < size_B))
        {
            ERROR ("to small primes \n");
            exit;
        }

        // selecting the sieving interval
        uint32_t M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);
        DEBUG (1, "The sieving interval M=%" PRIu32 "\n", M);

        // *** construct our sieve *** //
        std::vector<long> X;

        for (uint64_t i = M/2; i > 0; i = i - 1)
        {
            X.push_back(sqrt_N - i);
            DEBUG (3, "X%" PRIu64 " =%" PRIu64 "\n",i, sqrt_N - i );
        }

        for (uint64_t i = 0; i <= M/2; ++i)
        {
            X.push_back(sqrt_N + i);
            DEBUG (3, "X%" PRIu64 " =%" PRIu64 "\n",i, sqrt_N + i );
        }
        

        DEBUG (2,"\n");
        std::vector<long> Y;
        // fill in  (Xi)^2 - N 
        for (uint64_t i = 0; i < X.size(); ++i)
        {
            DEBUG (2, "X = %" PRIu64 "\t",X[i]);
            Y.push_back(X[i]*X[i] - N);
            DEBUG (2, "Y = %li\t",Y[i]);
            DEBUG (2, "\n");
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

        // for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        // {
        //     DEBUG(1, "V=%10li\texp=%li\n", V[y_number], v_exp[y_number][NEGATIVE_SIGN]);
        // }

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
                    DEBUG (3, "v = %10li\t",V[y_num]);
                    DEBUG (3, "p_smooth = %li\t",p_smooth[smooth_iter]);
                    DEBUG (3, "tmp = %li\n",tmp);
                    if(tmp == 0){
                        V[y_num] = V[y_num] / p_smooth[smooth_iter];
                        v_exp[y_num][exponent_num] += 1; 
                    }
                } while (tmp == 0);
            }
            // break;
        }


        for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        {
            DEBUG(3, "V=%10li\tY=%10li\texp=%li\n", V[y_number], Y[y_number], v_exp[y_number][NEGATIVE_SIGN]);
        }

        std::vector<int> smooth_num;
        // std::vector<long> solution_candidates_number;
        // std::vector<uint64_t> P11;
        for (int y_num = 0; y_num < V.size(); ++y_num)
        {
            int null_flag = 1;
            // printf("V = %" PRIu64 "\t",V[i]);
            if(V[y_num] == 1 || V[y_num] == -1)
            {
                for (   int exponent_num = 0;
                            exponent_num < v_exp[y_num].size(); 
                            exponent_num++ )
                {
                    DEBUG (3, "%ld\t", v_exp[y_num][exponent_num]);
                    if ((v_exp[y_num][exponent_num] % 2 )!= 0)
                        null_flag = 0;
                }
                DEBUG (3, "%ld\n", Y[y_num]);
                // skip negative value !!!!
                if (null_flag && V[y_num] > 0) {
                    // solution_candidates_number.push_back(y_num);
                } else {
                    smooth_num.push_back(y_num);
                }
            }
        }
        DEBUG (3, "\n");
        // solution_candidates_number.clear();


        if (smooth_num.size()  < size_B + 1)
        {
            ERROR( "to small number of smooth numbbers\n");
            exit; 
        }
        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}