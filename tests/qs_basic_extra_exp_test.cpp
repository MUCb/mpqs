#define BOOST_TEST_MODULE QS Test
#include <boost/test/included/unit_test.hpp> 


#include "bin_matrix.h"
#include "quadratic_sieve.h"
#include "log.h"
#include "greatest_common_divisor.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

int showDebugMsg = 0;

BOOST_AUTO_TEST_CASE(test_0) 
{
    int first_flag = 1;
    // for (int iter_1 = 10; iter_1 < 11; iter_1++) 
    for (int iter_1 = 3; iter_1 < 500 ; iter_1++) 
    {

    for (int iter = iter_1+1; iter < 500 ; iter++) 
    // for (int iter = 13; iter < 14 ; iter++) 
    {
        // uint64_t p = prime[461];
        // uint64_t q = prime[15];
        // uint64_t p = prime[147];
        // iter = 40;
        // iter_1 = 14;

        // if(first_flag)
        // {
        //     first_flag = 0;
        //     iter = 6569;
        //     iter_1 = 3905;
        // }

            // iter = 311;
            // iter_1 = 4;
        uint64_t p = prime[iter_1];
        uint64_t q = prime[iter];

        uint64_t N = p * q;
        uint64_t sqrt_N = 0;
        DEBUG (1, "i=%d\tj=%d\n", 147, iter_1 );
        // DEBUG (1, "i=%d\tj=%d\n", iter, iter);
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
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
            continue;
            // exit (0);
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
        // std::vector<uint64_t> v_extra_exp(Y.size()) ;
        std::vector<uint64_t> v_extra_exp(Y.size()) ;
        std::vector<int> smooth_num;

        if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number, v_extra_exp) == 0)
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
                        found = euclid_gcd_m( X, Y, tmp, p, q, N, v_exp, p_smooth, v_extra_exp);
                        if (found)
                            break;
                    }
                }
            }
            solution_candidates_number.clear();
            if (found)
            {
                DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", iter, iter_1, p, q);
                continue;
            }

            ERROR( "exit make_exp_array_extra");
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
            continue;
            // exit (0); 
        }

        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        int find_res = find_solution_extra(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N, v_extra_exp);
        // int find_res = find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
        BOOST_TEST( find_res  >= 0);
        if(find_res >= 0)
        {
            DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t %d\n", iter, iter_1, p, q,find_res);
        } else {
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
        }
        // break;
    }
    // break;
    }
}


// BOOST_AUTO_TEST_CASE(test_1) 
// {
//     for (int iter = 15; iter < 18 ; iter++) 
//     {
//         // uint64_t p = prime[19];
//         uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }

// BOOST_AUTO_TEST_CASE(test_2) 
// {
//     // for (int iter = 15; iter < 18 ; iter++) 
//     {
//         uint64_t p = prime[19];
//         // uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         size_B += 2;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }


// BOOST_AUTO_TEST_CASE(test_3) 
// {
//     for (int iter = 20; iter < 22 ; iter++) 
//     {
//         // uint64_t p = prime[22];
//         uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         // size_B += 1;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }



// BOOST_AUTO_TEST_CASE(test_4) 
// {
//     // for (int iter = 20; iter < 30 ; iter++) 
//     {
//         uint64_t p = prime[22];
//         // uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         size_B += 1;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }



// BOOST_AUTO_TEST_CASE(test_5) 
// {
//     // for (int iter = 23; iter < 30 ; iter++) 
//     {
//         uint64_t p = prime[26];
//         // uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         size_B += 2;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         M *= 2;
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }



// BOOST_AUTO_TEST_CASE(test_6) 
// {
//     for (int iter = 27; iter < 30 ; iter++) 
//     {
//         // uint64_t p = prime[30];
//         uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         // size_B += 2;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         // M *= 2;
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }



//**************************************
// BOOST_AUTO_TEST_CASE(test_7) 
// {
//     // for (int iter = 27; iter < 40 ; iter++) 
//     {
//         uint64_t p = prime[30];
//         // uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         size_B += 2;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         // M *= 2;
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number, v_extra_exp) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution_extra(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N, v_extra_exp)  >= 0);
//     }
// }



// BOOST_AUTO_TEST_CASE(test_8) 
// {
//     for (int iter = 31; iter < 45 ; iter++) 
//     {
//         // uint64_t p = prime[30];
//         uint64_t p = prime[iter];
//         uint64_t q = prime[70];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         double size_B;
//         size_B = exp (sqrt (log(N) * log(log(N))) );
//         size_B = pow(size_B , sqrt(2)/4);
//         // size_B += 2;
//         DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit (0);
//         }
//         std::vector<long> p_smooth_copy = p_smooth;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);
//         // M *= 2;
//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);

//         // *** construct our sieve *** //
//         std::vector<long> X;
//         std::vector<long> Y;
//         construct_xy(X, Y, sqrt_N, N, M);


//         // simple sieve 
//         // std::vector<long> V;
//         // V = Y;
//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<uint64_t> v_extra_exp(Y.size()) ;
//         std::vector<int> smooth_num;

//         if (make_exp_array_extra(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array_extra");
//             exit (0); 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N)  >= 0);
//     }
// }