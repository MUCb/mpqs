//#define BOOST_TEST_MODULE QS Test
//#include <boost/test/included/unit_test.hpp> 

#include <iostream> 
#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "greatest_common_divisor.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
// #include "primes.h"
#include "primes.h"
using namespace std;
int showDebugMsg = 0;

int main (void )
//BOOST_AUTO_TEST_CASE(test_5) 
{

    int first_flag = 1;
    double it1 = 1.1;
    // for (int iter_1 = 10; iter_1 < 11 ; iter_1++) 
    // for (int iter_1 = 1000; iter_1 < 1200 ; iter_1++) 
    // for (int iter_1 = 5760000; iter_1 < 5760030 ; iter_1++) 
    // for (int iter_1 = 3; iter_1 < 1000 ; iter_1++) 
    // for (int iter_1 = 3; iter_1 < 4 ; iter_1++) 
    // int iter_1 = 52000;
    int iter_1 = 4999;
//    int iter_1 = 199;
    //while (iter_1 < 6000 ) 
    // while (iter_1 < 78400 ) 
    {
        iter_1 += 1;
        // iter_1 += 10;
        // iter_1 = ceil(it1* (double)iter_1);
        
   // int iter = iter_1 + 597;
    int iter = 6997;
    //while (iter < 8000 )

    // for (int iter = 3; iter < 1000 ; iter++) 
    // for (int iter = 3; iter < 4 ; iter++) 
    // for (int iter = 10000; iter < 10200 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 10200 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 5760030 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 1000 ; iter++) 
    // for (int iter = 10; iter < 11 ; iter++) 
    {
        iter += 3;
        // iter += 10;
        // iter = ceil(it1* (double)iter);
        // if(first_flag)
        // {
        //     first_flag = 0;
        //     iter = 9486;
        //     iter_1 = 4532;
        // }

        time_t start;
        time_t finish;
        start = clock();


        // Special test case size_B wa changed
        // uint64_t p = prime[100];
        // iter = 40;
        // iter_1 = 14;
        
        // iter = 3243;
        // iter_1 = 2332;
        uint64_t p = prime[iter_1];  // 10^8
        uint64_t q = prime[iter];
        // uint64_t q = prime[147];

        uint64_t N = p * q; //  10^19
        uint64_t sqrt_N = 0;
        DEBUG (1, "i=%d\tj=%d\n", iter, iter_1);
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (log(N) * log(log(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        // size_B *= 2;
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            //ERROR ("to small primes \n");
            ERROR ("Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
                    finish = clock();
        //DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
      // exit(0);
            //continue ;
             exit (0);
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
            /*if (found)
            {
                //DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
                DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
                        finish = clock();
        DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
                continue;
            }*/

            //ERROR( "exit make_exp_array");
           // DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
            //        finish = clock();
        //DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
            // exit (0); 
         //   continue;
        }




        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        int find_res = find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
        //BOOST_CHECK(find_res   >= 0);
        if(find_res >= 0)
        {
            //DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
             DEBUG (0,  "found %lu\t%lu\t%d\n", p, q, m1.filled);
        finish = clock();
        DEBUG (1, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        } else {
            ERROR ( "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
                    finish = clock();
        //DEBUG (1, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        }
        // exit(0);

    }
    }
}
