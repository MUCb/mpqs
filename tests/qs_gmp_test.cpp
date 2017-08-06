#define BOOST_TEST_MODULE QS Test
#include <boost/test/included/unit_test.hpp> 


// #include "bin_matrix.h"
// #include "quadratic_sieve.h"
// #include "log.h"
// #include "greatest_common_divisor.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
// #include "primes.h"
// #include "primes_10_8.h"
#include <time.h>

int showDebugMsg = 0;

#include <math.h> 


//-----------------------------------------------------------
// base <- exp((1/2) sqrt(ln(n) ln(ln(n))))
//-----------------------------------------------------------
void get_smoothness_base(mpz_t base, mpz_t n) {
    mpfr_t fN, lnN, lnlnN;
    mpfr_init(fN), mpfr_init(lnN), mpfr_init(lnlnN);

    mpfr_set_z(fN, n, MPFR_RNDU);
        (lnN, fN, MPFR_RNDU);
    mpfr_log(lnlnN, lnN, MPFR_RNDU);

    mpfr_mul(fN, lnN, lnlnN, MPFR_RNDU);
    mpfr_sqrt(fN, fN, MPFR_RNDU);
    mpfr_div_ui(fN, fN, 2, MPFR_RNDU);
    mpfr_exp(fN, fN, MPFR_RNDU);

    mpfr_get_z(base, fN, MPFR_RNDU);

    mpfr_clears(fN, lnN, lnlnN, NULL);
}



BOOST_AUTO_TEST_CASE(test_0) 
{
    int first_flag = 1;
    double it1 = 1.1;
    {
    {
        time_t start;
        time_t finish;
        start = clock();

        mpz_t p;
        mpz_t q;
        mpz_t N;

        mpz_set_str (p, "1414319", 10);
        mpz_set_str (q, "1461287", 10);

        mpz_init(N);
        mpz_mul(N, p, q);


        mpz_t sqrt_N;
        mpz_t rem;
        mpz_init(sqrt_N);
        mpz_init(rem);
        mpz_sqrtrem(sqrt_N, rem, N);
        mpz_add_ui(sqrt_N, sqrt_N, 1);
        

        gmp_printf ("N=%Zd,\n",N);
        gmp_printf ("sqrt_N=%Zd, rem=%Zd,\n",sqrt_N, rem);

        // selecting the size of the factor base
        mpz_t B;
        mpz_init(B);

        
    //     size_B = exp (sqrt (log(N) * log(log(N))) );
    //     size_B = pow(size_B , sqrt(2)/4);
    //     DEBUG (2,"size of factor base size_B=%f\n", size_B);

    //     // selecting smooth primes 
    //     std::vector<long> p_smooth;
    //     DEBUG (2, "smooth numbers\n");

    //     make_smooth_numbers(p_smooth, size_B, N);

    //     if ((p_smooth.size() < size_B))
    //     {
    //         ERROR ("to small primes \n");
    //         DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
    //         finish = clock();
    //         DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    //         continue;
    //         // exit (0);
    //     }
    //     std::vector<long> p_smooth_copy = p_smooth;
    //     // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

    //     // selecting the sieving interval
    //     uint32_t M;
    //     M = exp (sqrt (log(N) * log(log(N))) );
    //     M = pow(M , 3*sqrt(2)/4);
    //     DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

    //     // *** construct our sieve *** //
    //     std::vector<long> X;
    //     std::vector<long> Y;
    //     construct_xy(X, Y, sqrt_N, N, M);


    //     // simple sieve 
    //     // std::vector<long> V;
    //     // V = Y;
    //     // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
    //     std::vector<long> solution_candidates_number;
    //     std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
    //     // std::vector<uint64_t> v_extra_exp(Y.size()) ;
    //     std::vector<uint64_t> v_extra_exp(Y.size()) ;
    //     std::vector<int> smooth_num;

    //     int array_res = make_exp_array_condBsmooth_1(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number, v_extra_exp);

    //     uint64_t found = 0;
    //         if (solution_candidates_number.size() > 0)
    //         {
    //             // to check functionality use  ./qs_3.out 27 10
    //             DEBUG (3,"%s:%d\n", __func__, __LINE__);
    //             for (int i = 0; i <  solution_candidates_number.size(); ++i)
    //             {
    //                 DEBUG (3,"check %ld\n", Y[solution_candidates_number[i]]);

    //                 if ( Y[solution_candidates_number[i]] > 0 ){

    //                     std::vector<int64_t> tmp;
    //                     tmp.push_back(solution_candidates_number[i]);
    //                     found = euclid_gcd_m_big( X, Y, tmp, p, q, N, v_exp, p_smooth, v_extra_exp);
    //                     if (found)
    //                         break;
    //                 }
    //             }
    //         }
    //         solution_candidates_number.clear();
    //         if (found)
    //         {
    //             DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
    //             finish = clock();
    //             DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    //             continue;
    //         }

    //     if (array_res == 0)
    //     {
    //         // ERROR( "exit make_exp_array_extra");
    //         DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
    //         finish = clock();
    //         DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    //         continue;
    //         // exit (0); 
    //     }

    //     std::vector<int> smooth_num_back = smooth_num;
    //     bin_matrix_t m1(p_smooth.size() + 1);

    //     // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
    //     int find_res = find_solution_condBsmooth(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N, v_extra_exp);
    //     // int find_res = find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
    //     BOOST_TEST( find_res  >= 0);
    //     if(find_res >= 0)
    //     {
    //         DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t %d\t", iter, iter_1, p, q,find_res);
    //     } else {
    //         DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
    //     }
    //         finish = clock();
    //         DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    //     // break;
        
    //         // iter *= 1.1;
            
    // }
    // // break;
    // }
}

