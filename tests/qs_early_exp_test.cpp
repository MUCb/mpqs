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

 #include <math.h>

int showDebugMsg = 1;

// BOOST_AUTO_TEST_CASE(test_1) 
// {
//     // for (int iter = 15; iter < 30 ; iter++) 
//     {
//         uint64_t p = prime[20];
//         uint64_t q = prime[31];

//         // uint64_t p = prime[15];
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[16];
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[17]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[18]; // k = 3 p = 12
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[19]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[20]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[21]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[22]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[23]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[24]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[25]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[26]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[27]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[28]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[29]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[30]; // k = 3 p = 10
//         // uint64_t q = prime[31];

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

//         bin_matrix_t m_all(p_smooth.size() + 1);
//         bin_matrix_t m_counter(p_smooth.size() + 1);
//         std::vector<uint64_t> counter(p_smooth.size() + 1);
//         // DEBUG(1, "smooth %d\n", p_smooth.size());
//         // DEBUG(1, "size ========= %d\n", m_all.collumn_size);
//         // break;

//         std::vector<long> V;
//         V = Y;
//         // add sign to exponent matrix
//         #define NEGATIVE_SIGN    0 
        
//         // v_exp[i].size()-1
//         for (int y_number = 0; y_number < V.size(); ++y_number) {
//             if(V[y_number] < 0 )
//                 v_exp[y_number][NEGATIVE_SIGN] = 1;

//             prime_factorisation(V[y_number], p_smooth, v_exp[y_number]);
//             if(V[y_number] < 0 )
//                 V[y_number] *= -1;
//             if(V[y_number] != 1){
//                 double res = sqrt(V[y_number]);
//                 if(res == trunc(res)) {
//                     DEBUG (0, "Y = %li\tV = %li\n",Y[y_number], V[y_number]);
//                     DEBUG (0, "found  ========================================= %f\n",res);
//                     // DEBUG (0, "iter %d\n",iter);
//                 }
                
//             }
                

//         }
//     }

// }


// Y = 13454   V = 961
// found  ========================================= 31.000000
// iter 20
// Y = -6727   V = 961
// found  ========================================= 31.000000
// iter 21
// Y = 21218   V = 10609
// found  ========================================= 103.000000
// iter 21
// Y = -1849   V = 1849
// found  ========================================= 43.000000
// iter 22
// Y = -1849   V = 1849
// found  ========================================= 43.000000
// iter 22
// Y = 17672   V = 2209
// found  ========================================= 47.000000
// iter 22
// Y = -961    V = 961
// found  ========================================= 31.000000
// iter 26
// Y = -961    V = 961
// found  ========================================= 31.000000
// iter 26
// Y = 27848   V = 3481
// found  ========================================= 59.000000
// iter 26
// Y = -5329   V = 5329
// found  ========================================= 73.000000
// iter 27
// Y = -3844   V = 961
// found  ========================================= 31.000000
// iter 27
// Y = 20402   V = 10201
// found  ========================================= 101.000000
// iter 28








BOOST_AUTO_TEST_CASE(test_2) 
{
// for (int iter1 = 5; iter1 < 70 ; iter1++) {
    // for (int iter = iter1 + 1; iter < 70 ; iter++) 
    {
        // uint64_t p = prime[iter];
        // uint64_t q = prime[iter1];

        // uint64_t p = prime[5]; // k = 5 p = 10
        // uint64_t q = prime[42];

        // uint64_t p = prime[17]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[18]; // k = 3 p = 12
        // uint64_t q = prime[31];

        // uint64_t p = prime[19]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[20]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[21]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[22]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[23]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[24]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[25]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[26]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[27]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[28]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[29]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[30]; // k = 3 p = 10
        // uint64_t q = prime[31];

        uint64_t p = prime[300]; // k = 3 p = 10
        uint64_t q = prime[500];

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

        bin_matrix_t m_all(p_smooth.size() + 1);
        bin_matrix_t m_counter(p_smooth.size() + 1);
        std::vector<uint64_t> counter(p_smooth.size() + 1);
        // DEBUG(1, "smooth %d\n", p_smooth.size());
        // DEBUG(1, "size ========= %d\n", m_all.collumn_size);
        // break;

        std::vector<long> V;
        V = Y;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        
        // v_exp[i].size()-1
        for (int y_number = 0; y_number < V.size(); ++y_number) {

            if(V[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            prime_factorisation(V[y_number], p_smooth, v_exp[y_number]);
            

            int sign_flag = 0;
            if(V[y_number] < 0 ){
                sign_flag = 1;
                V[y_number] *= -1;
            }
            if(V[y_number] != 1){
                double res = sqrt(V[y_number]);
                if(res == trunc(res)) {
                    V[y_number] = 1;
                    DEBUG (0, "found  ========================================= %f\n",res);
                    DEBUG (0, "Y = %li\tV = %li\n",Y[y_number], V[y_number]);
                    // DEBUG (0, "iter %d\n",iter);
                }
                
            }
            if(sign_flag)
                V[y_number] *= -1;

            if(V[y_number] == -1 || V[y_number] == 1){
                
                DEBUG (3, "Y = %li\n",Y[y_number]);

                // modulo-2 division 
                int null_flag = 1;
                vec_mod2(v_exp[y_number], null_flag);
                
                DEBUG (3, "%ld\n", Y[y_number]);
                // check if we alredy have null vector
                // skip negative value !!!!
                if (null_flag && V[y_number] > 0) { // sign check is extra !!!!
                    // solution_candidates_number.push_back(y_number);

                    //    will be added later  ##########################
                    uint64_t found = 0;
                    std::vector<int64_t> tmp;
                    tmp.push_back(y_number);
                    found = euclid_gcd( X, Y, tmp, p, q, N);
                    if (found)
                        break;
                        // exit(0);
                    //##########################
                } else {
                    smooth_num.push_back(y_number);
                    // ERROR("filled1 %d\n", m_all.filled);
                    if (m_all.add_row(v_exp[y_number]) == 1){

                        int exponent_num = (v_exp[y_number].size() - 1);
                        // ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);

                        while (v_exp[y_number][exponent_num] == 0 && exponent_num >= 0){
                            exponent_num--;
                        }

                        if (exponent_num >= 0)
                        {
                            int count_flag = 0;
                            count_flag = add_counter_row(m_counter ,counter ,exponent_num);

                            if (count_flag)
                            {
                                bin_matrix_t m_selected(p_smooth.size() + 1);
                                bin_matrix_t m_selected_copy(p_smooth.size() + 1);
                                std::vector<int> smooth_num_selected;
                                std::vector<int> smooth_num_selected_iter;

                                ERROR("find limit %d", exponent_num);
                                m_counter.show();
                                m_all.show();
                                for (int i = 0; i < m_counter.matrix.size(); ++i)
                                {
                                    if (m_counter.matrix[i][exponent_num] == 1)
                                    {
                                        m_selected.add_row(m_all.matrix[i]);
                                        smooth_num_selected.push_back(smooth_num[i]);
                                        smooth_num_selected_iter.push_back(i);
                                    }
                                }
                                m_selected.show();
                                m_selected_copy= m_selected;
                                int null_line = m_selected.make_upper_triangular();
                                std::vector<int64_t> P11;

                                if (null_line > -1)
                                {
                                    // DEBUG(2, "collumn size %d\n", m_all.collumn_size);
                                    for (uint64_t col = 0; col <  m_selected.filled; ++col)
                                    {
                                        DEBUG (2,"matrix[%d][%d] = %ld\n",null_line,col, m_selected.unit_matrix[null_line][col]);
                                        if( m_selected.unit_matrix[null_line][col] > 0)
                                        {
                                            DEBUG (2,"num = %d\t", smooth_num_selected[col]);
                                            DEBUG (2,"Y  = %ld\n", Y[smooth_num_selected[col]]);
                                            P11.push_back(smooth_num_selected[col]);
                                        }
                                    }
                                    DEBUG (2,"\n");

                                    int found = 0;
                                    found = euclid_gcd( X, Y, P11, p, q, N);
                                    // printf("found %lu\n", found);
                                    m_selected.show();
                                    if (found) {
                                        break;
                                        // exit( null_line);
                                    } else {
                                        int max_i = 0;
                                        DEBUG (3," null_line %d\n",null_line );
                                        m_selected_copy.show();
                                        max_i = m_selected_copy.max_unit_num(m_selected.unit_matrix[null_line]);
                                        DEBUG (3," iter %d\n",max_i );

                                        DEBUG (3," line %d\n",smooth_num_selected_iter[max_i]);

                                        DEBUG (3," delete before \n");
                                        m_all.show();
                                        m_all.delete_row( smooth_num_selected_iter[max_i] );
                                        DEBUG (3," delete after \n");
                                        m_all.show();
                                        DEBUG (3," delete before \n");
                                        m_counter.show();
                                        m_counter.delete_row( smooth_num_selected_iter[max_i] );
                                        DEBUG (3," delete after \n");
                                        m_counter.show();

                                        for (int i = exponent_num; i < v_exp[y_number].size(); ++i) {
                                            counter[i]--;
                                        }

                                        smooth_num.erase(smooth_num.begin() + smooth_num_selected_iter[max_i]);
                                    }
                                }

                                // exit(0);
                            }
                        }
                        else{
                            ERROR( "empty string \n");
                            exit(0);
                        }

                        // ERROR("%s %d\n", __func__, __LINE__);
                        // m_all.show();
                        // ERROR("%s %d\n", __func__, __LINE__);

                        //  make_upper_triangular will be added later 
                        // int null_line = m_all.make_upper_triangular();
                        // if (null_line != -1){
                        //     exit(0);
                        // }
                    }
                    else
                    {
                        ERROR("cant add aaaaa\n");
                        exit(0);
                    }
                }
            }
        }
        // m_all.show();
        // m_counter.show();


        // exit(0); ///DEBUG  ////////////////////////////////////////////////////////////////////

        // if (make_exp_array(m_all, v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        // {
        //     ERROR( "exit make_exp_array");
        //     break; 
        // }

        // std::vector<int> smooth_num_back = smooth_num;

        // BOOST_TEST( find_solution(m_all, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    }
}



// }