#include <iostream> 
#include "bin_matrix.h"
#include "quadratic_sieve_big.h"
#include "greatest_common_divisor_big.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include "big_2.h"
// #include "primes.h"
#include "primes.h"
using namespace std;
int showDebugMsg = 1;

int main (void )
{

    int first_flag = 1;
    //double it1 = 1.1;
    //int iter_1 = 4999;
    int iter_1 = 5000;
    //int iter_1 = 53;
    while (iter_1 < 5300 ) 
    {
        iter_1 += 5;
        
    //int iter = 6997;
    int iter = iter_1 + 597;
    //int iter = 75;

    while (iter < 6000 )
    {
        iter += 9;

        time_t start;
        time_t finish;
        start = clock();

        big_2 p(prime[iter_1]);
        big_2 q(prime[iter]);

        big_2 one = 1;
        big_2 N = p * q; //  10^19
        big_2 sqrt_N = 0;
        big_2 null = 0;
        
        LOG(1) std::cout << "iter = " << iter 
                        << "\titer_1 " << iter_1 
                        << "\tp=" << p 
                        << "\tq=" << q 
                        << "\tN=" << N 
                        << "\n";

        sqrt_N = squareRoot(N);
        sqrt_N = sqrt_N + one;
        LOG(2) std::cout << "n=" << N << "\tsqrt=" << sqrt_N <<  "\n";


        // selecting the size of the factor base
        double size_B;
        size_B = exp (sqrt (ln(N) * log(ln(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        // size_B *= 2;
        DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        make_smooth_numbers(p_smooth, size_B, N);
        if ((p_smooth.size() < size_B))
        {
            //ERROR ("to small primes \n");
            //ERROR ("Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
            LOG(0) std::cout << "Fail solution i=" << iter << "\tj=" << iter_1 << " p=" << p << "\tq=" << q << "\n";
                    finish = clock();
        //DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
            //continue ;
             exit (0);
        }
        std::vector<long long> p_smooth_copy = p_smooth;
        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

        // selecting the sieving interval
        long long  M;
        M = exp (sqrt (ln(N) * log(ln(N))) );
        M = pow(M , 3*sqrt(2)/4);

        DEBUG (2, "The sieving interval M=%li\n", M);

        // *** construct our sieve *** //
        std::vector<big_2> X;
        std::vector<big_2> Y;
        std::vector<big_2> V;

        construct_xy(X, Y, sqrt_N, N, M);

        // simple sieve 
        // std::vector<long> V;
        // V = Y;
        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        std::vector<long long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;

        if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        {
            big_2 found = 0;
            if (solution_candidates_number.size() > 0)
            {
                // to check functionality use  ./qs_3.out 27 10
                DEBUG (3,"%s:%d\n", __func__, __LINE__);
                for (int i = 0; i <  solution_candidates_number.size(); ++i)
                {
                    LOG(3) std::cout <<"check " << Y[solution_candidates_number[i]] << "\n";

                    if ( Y[solution_candidates_number[i]] > null ){

                        std::vector<int64_t> tmp;
                        tmp.push_back(solution_candidates_number[i]);
                        found = euclid_gcd_big( X, Y, tmp, p, q, N ,v_exp, p_smooth);
                        if (! (found == 0))
                            return 0;
                    }
                }
            }
            solution_candidates_number.clear();
            //if (found)
           // {
           //     //DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
           //     DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
           //             finish = clock();
       // DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        //        continue;
         //   }

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
        int find_res = find_solution_big(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
        //BOOST_CHECK(find_res   >= 0);
        if(find_res >= 0)
        {
            //DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
             LOG(0) std::cout << "Found solution i=" << iter << "\tj=" << iter_1 << " p=" << p << " q=" << q << "\n";
        finish = clock();
        //DEBUG (1, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        } else {
            LOG(0) std::cout << "Fail solution i=" << iter << "\tj=" << iter_1 << " p=" << p << "\tq=" << q << "\n";
                    finish = clock();
        //DEBUG (1, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        }
        // exit(0);
    }
    }
}
