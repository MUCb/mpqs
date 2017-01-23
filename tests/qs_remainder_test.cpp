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
    // for (int iter = 15; iter < 16 ; iter++) {
        // uint64_t p = prime[15];
        // uint64_t q = prime[31];

        // uint64_t p = prime[16];
        // uint64_t q = prime[31];

        // uint64_t p = prime[17]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // uint64_t p = prime[18]; // k = 10 p = 12
        // uint64_t q = prime[31];


        uint64_t p = prime[19]; // k = 10 p = 15
        uint64_t q = prime[31];

        // uint64_t p = prime[20]; // k = 10 p = 12
        // uint64_t q = prime[31];

        // uint64_t p = prime[21]; // k = 10 p = 12
        // uint64_t q = prime[31];

        // uint64_t p = prime[22]; // k = 10 p = 12
        // uint64_t q = prime[31];



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

        for (int i = 2; p_smooth.size() < 12; ++i) // 2 log n
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
        for (k = 1; k < 10; ++k)
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
        bin_matrix_t m2(p_smooth.size() + 1);
        std::vector<uint64_t> counter(p_smooth.size() + 1);
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

                if(V[y_number] == -1 || V[y_number] == 1)
                    break;
            }

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
                        v_exp[y_number][exponent_num] %= 2;
                        if (v_exp[y_number][exponent_num] != 0)
                            null_flag = 0;
                    }
                    DEBUG (3, "%ld\n", Y[y_number]);
                    // skip negative value !!!!
                    if (null_flag && V[y_number] > 0) {
                        // solution_candidates_number.push_back(y_number);

                        //    will be added later  ##########################
                        // uint64_t found = 0;
                        // std::vector<int64_t> tmp;
                        // tmp.push_back(y_number);
                        // found = euclid_gcd( X, Y, tmp, p, q, N);
                        // if (found)
                        //     exit(0);
                        //##########################

                        
                    } else {

                        // // we can find the same Y in different k
                        // int duplication_flag = 0;
                        // for (int i = 0; i < smooth_num.size(); ++i)
                        // {
                        //     if(Y[smooth_num[i]] == Y[y_number] ){
                        //         duplication_flag = 1;
                        //         DEBUG(3, "duplication flag was set %d %d |%d %d \n",Y[smooth_num[i]], Y[y_number] , smooth_num[i], y_number);
                        //         break;
                        //     }
                        // }

                        // if (duplication_flag)
                        //     continue;


                        smooth_num.push_back(y_number);


                        ERROR("filled1 %d\n", m1.filled);
                        if (m1.add_row(v_exp[y_number]) == 1){

                            int exponent_num = (v_exp[y_number].size() - 1);
                            // ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);
                            while (v_exp[y_number][exponent_num] == 0 && exponent_num >= 0){
                                exponent_num--;
                            }

                            if (exponent_num >= 0)
                            {
                                std::vector<uint64_t> tmp(v_exp[y_number].size());
                                for (int i = exponent_num; i < v_exp[y_number].size(); ++i)
                                {
                                    tmp[i] = 1;
                                    counter[i]++;
                                }
                                m2.add_row(tmp);
                                // ERROR("added num %d\n", exponent_num);

                                int count_flag = 0;
                                for (exponent_num = 1; exponent_num < counter.size(); ++exponent_num)
                                {
                                    if (counter[exponent_num] == exponent_num + 2)
                                    {
                                        count_flag = 1;
                                        break;
                                    }
                                }

                                if (count_flag)
                                {
                                    bin_matrix_t m3(p_smooth.size() + 1);
                                    bin_matrix_t m4(p_smooth.size() + 1);
                                    std::vector<int> smooth_num3;
                                    std::vector<int> smooth_num3_1;

                                    ERROR("find limit %d", exponent_num);
                                    m2.show();
                                    m1.show();
                                    for (int i = 0; i < m2.matrix.size(); ++i)
                                    {
                                        if (m2.matrix[i][exponent_num] == 1)
                                        {
                                            m3.add_row(m1.matrix[i]);
                                            smooth_num3.push_back(smooth_num[i]);
                                            smooth_num3_1.push_back(i);
                                        }
                                    }
                                    m3.show();
                                    m4 = m3;
                                    int null_line = m3.make_upper_triangular();
                                    std::vector<int64_t> P11;

                                    if (null_line > -1)
                                    {
                                        // DEBUG(2, "collumn size %d\n", m1.collumn_size);
                                        for (uint64_t col = 0; col <  m3.filled; ++col)
                                        {
                                            DEBUG (2,"matrix[%d][%d] = %ld\n",null_line,col, m3.unit_matrix[null_line][col]);
                                            if( m3.unit_matrix[null_line][col] > 0)
                                            {
                                                DEBUG (2,"num = %d\t", smooth_num3[col]);
                                                DEBUG (2,"Y  = %ld\n", Y[smooth_num3[col]]);
                                                P11.push_back(smooth_num3[col]);
                                            }
                                        }
                                        DEBUG (2,"\n");

                                        int found = 0;
                                        found = euclid_gcd( X, Y, P11, p, q, N);
                                        // printf("found %lu\n", found);
                                        m3.show();
                                        if (found) {
                                            exit( null_line);
                                        } else {
                                            int max_i = 0;
                                            DEBUG (3," null_line %d\n",null_line );
                                            m4.show();
                                            max_i = m4.max_unit_num(m3.unit_matrix[null_line]);
                                            DEBUG (3," iter %d\n",max_i );

                                            DEBUG (3," line %d\n",smooth_num3_1[max_i]);

                                            DEBUG (3," delete before \n");
                                            m1.show();
                                            m1.delete_row( smooth_num3_1[max_i] );
                                            DEBUG (3," delete after \n");
                                            m1.show();
                                            DEBUG (3," delete before \n");
                                            m2.show();
                                            m2.delete_row( smooth_num3_1[max_i] );
                                            DEBUG (3," delete after \n");
                                            m2.show();

                                            for (int i = exponent_num; i < v_exp[y_number].size(); ++i) {
                                                counter[i]--;
                                            }

                                            smooth_num.erase(smooth_num.begin() + smooth_num3_1[max_i]);



                                            // m4.delete_row(max_i);
                                            // DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
                                            // smooth_num_back.erase(smooth_num_back.begin() + max_i);
                                            // smooth_num3.erase(smooth_num3.begin() + max_i);
                                            // m2.show();
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
                            // m1.show();
                            // ERROR("%s %d\n", __func__, __LINE__);

                            //  make_upper_triangular will be added later 
                            // int null_line = m1.make_upper_triangular();
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
        m1.show();
        m2.show();
        exit(0); ///DEBUG  ////////////////////////////////////////////////////////////////////

















        // if (make_exp_array(m1, v_exp, smooth_num, Y, p_smooth, size_B, M, solution_candidates_number) == 0)
        // {
        //     ERROR( "exit make_exp_array");
        //     break; 
        // }

        // std::vector<int> smooth_num_back = smooth_num;

        // BOOST_TEST( find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N)  >= 0);
    // }
}



