#define BOOST_TEST_MODULE QS remainder Test
#include <boost/test/included/unit_test.hpp> 


#include "dynamic_bin_matrix.h"
// #include "primes.h"
#include "quadratic_sieve_remainder.h"
#include "log.h"

#include "greatest_common_divisor.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

int showDebugMsg = 3;

// BOOST_AUTO_TEST_CASE(test_1) 
// {
//     for (int iter = 15; iter < 16 ; iter++) {
//         uint64_t p = prime[iter];
//         uint64_t q = prime[31];

//         uint64_t N = p * q;
//         uint64_t sqrt_N = 0;
//         uint64_t sqrt_Nk = 0;
//         uint64_t k = 1;
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

//         for (int i = 2; p_smooth.size() < 10; ++i) // 2 log n
//         {
//             p_smooth.push_back(prime[i]);
//         }
//         DEBUG(2, "p_smooth size %d\n", p_smooth.size());

//         // make_smooth_numbers(p_smooth, size_B, N);

//         if ((p_smooth.size() < size_B))
//         {
//             ERROR ("to small primes \n");
//             exit;
//         }

//         // selecting the sieving interval
//         uint32_t M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         M = pow(M , 3*sqrt(2)/4);

//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
        
//         // *** construct our sieve *** //
        
//         std::vector<long> X;
//         std::vector<long> Y;
//         for (k = 1; k < 3; ++k)
//         {
//             std::vector<long> X1;
//             std::vector<long> Y1;
//             sqrt_Nk = trunc(sqrt(N * k)) + 1;
//             construct_xy(X1, Y1, sqrt_Nk, N, M);
//             X.insert(X.end(), X1.begin(), X1.end());
//             Y.insert(Y.end(), Y1.begin(), Y1.end());
            
//         }

//         for (uint64_t i = 0; i < X.size(); ++i)
//         {
//             DEBUG (2, "X = %llu\t",X[i]);
//             DEBUG (2, "Y = %li\t",Y[i]);
//             DEBUG (2, "\n");
//         }
        
//         DEBUG (2, "X size  = %d\n",X.size());
//         // simple sieve 
//         std::vector<long> solution_candidates_number;
//         std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<int> smooth_num;
//         DEBUG (2, "v_exp size  = %d\n",v_exp.size());

//         if (make_exp_array(v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
//         {
//             ERROR( "exit make_exp_array");
//             exit; 
//         }

//         std::vector<int> smooth_num_back = smooth_num;
//         bin_matrix_t m1(p_smooth.size() + 1);

//         BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
//     }
// }



BOOST_AUTO_TEST_CASE(test_2) 
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

        for (int i = 2; p_smooth.size() < 10; ++i) // 2 log n
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

        bin_matrix_t m1(p_smooth.size() + 1);
        // DEBUG(1, "smooth %d\n", p_smooth.size());
        // DEBUG(1, "size ========= %d\n", m1.collumn_size);
        // break;




        std::vector<long> V;
        V = Y;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        #define FIRST_VALUE    1
        // v_exp[i].size()-1
        for (int y_number = 0; y_number < V.size(); ++y_number)
        {
            if(V[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                        smooth_iter < p_smooth.size(); 
                        smooth_iter++, exponent_num++)
            {
                // if(V[y_num] == -1 || V[y_num] == 1)
                //     continue;

                long int tmp;
                do{
                    tmp = V[y_number] % p_smooth[smooth_iter];
                    DEBUG (4, "v = %10li\t",V[y_number]);
                    DEBUG (4, "p_smooth = %li\t",p_smooth[smooth_iter]);
                    DEBUG (4, "tmp = %li\n",tmp);
                    if(tmp == 0){
                        V[y_number] = V[y_number] / p_smooth[smooth_iter];
                        v_exp[y_number][exponent_num] += 1; 
                    }
                } while (tmp == 0);

                if(V[y_number] == -1 || V[y_number] == 1){

                    // for (int i = 0; i < v_exp[y_number].size(); ++i)
                    // {
                    //     DEBUG (3, "%li\t",v_exp[y_number][i]);
                        
                    // }
                    DEBUG (3, "Y = %li\n",Y[y_number]);
                    int null_flag = 1;
                    for (   int exponent_num = 0;
                                exponent_num < v_exp[y_number].size(); 
                                exponent_num++ )
                    {
                        DEBUG (3, "%ld\t", v_exp[y_number][exponent_num]);
                        if ((v_exp[y_number][exponent_num] % 2 )!= 0)
                            null_flag = 0;
                    }
                    DEBUG (3, "%ld\n", Y[y_number]);
                    // skip negative value !!!!
                    if (null_flag && V[y_number] > 0) {
                        solution_candidates_number.push_back(y_number);
                        uint64_t found = 0;
                        std::vector<int64_t> tmp;
                        tmp.push_back(y_number);
                        found = euclid_gcd( X, Y, tmp, p, q, N);
                        if (found)
                            break;

                        
                    } else {
                        smooth_num.push_back(y_number);


                        ERROR("filled1 %d\n", m1.filled);
                        if (m1.add_row(v_exp[y_number]) == 1){
                            ERROR("%s %d\n", __func__, __LINE__);
                            m1.show();
                            ERROR("%s %d\n", __func__, __LINE__);
                            // m2.make_upper_triangular();
                            int null_line = m1.make_upper_triangular();
                            if (null_line != -1){
                                exit(0);
                            }
                        }
                    }

                    
                    break;
                }
            }
        }
        m1.show();
        exit(0); ///DEBUG  ////////////////////////////////////////////////////////////////////

















        // if (make_exp_array(m1, v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        // {
        //     ERROR( "exit make_exp_array");
        //     break; 
        // }

        // std::vector<int> smooth_num_back = smooth_num;

        // BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}
