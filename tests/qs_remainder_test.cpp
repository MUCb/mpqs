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
#include <time.h>

#include "primes_10_8.h"

int showDebugMsg = 4;


BOOST_AUTO_TEST_CASE(test_1) 
{
    for (int iter_1 = 3; iter_1 < 4 ; iter_1++) 
//    for (int iter_1 = 1000; iter_1 < 1200 ; iter_1++) 
    // for (int iter_1 = 3; iter_1 < 1000 ; iter_1++) 
    // for (int iter_1 = 5760000; iter_1 < 5760030 ; iter_1++) 
    {

    // for (int iter = iter_1 + 1 - 5753000; iter < 7030 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 1000 ; iter++) 
 //   for (int iter = 10000; iter < 10200 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 10200 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 5760030 ; iter++) 
     for (int iter = 3; iter < 4 ; iter++) 
    {
        time_t start;
        time_t finish;
        start = clock();
    // for (int iter = 15; iter < 16 ; iter++) {
        // uint64_t p = prime[15];
        // uint64_t q = prime[31];

        // uint64_t p = prime[16];
        // uint64_t q = prime[31];

        // uint64_t p = prime[235]; // k = 3 p = 10
        // uint64_t q = prime[31];

        // 5761456
        // iter = 954;
        // iter_1 = 3;

        // iter = 100;
        // iter_1 = 50;
    FILE * pFile;
    char mystring [100];
    pFile = fopen ("prime_1","r");
    if (pFile == NULL) perror ("Error opening file");
    else {
        if ( fgets (mystring , 100 , pFile) != NULL ) {
            //puts (mystring);
        } else {
            std::cout << "error read prime numbers 1\n";
            exit(0);
            //return 1;
        }
        fclose (pFile);
    }

    // remove new line character
    char *pos;
    if ((pos=strchr(mystring, '\n')) != NULL)
            *pos = '\0';
    

        uint64_t p = stol(mystring); // k = 3 p = 10
    //std::cout << "p " << p << "\n";

    pFile = fopen ("prime_2","r");
    if (pFile == NULL) perror ("Error opening file");
    else {
        if ( fgets (mystring , 100 , pFile) != NULL ) {
            //puts (mystring);
        } else {
            std::cout << "error read prime numbers 2\n";
            exit(0);
            //return 1;
        }
        fclose (pFile);
    }
    
    // remove new line character
    if ((pos=strchr(mystring, '\n')) != NULL)
            *pos = '\0';

        uint64_t q = stol(mystring);
 
//        uint64_t p = prime[iter_1];  // 10^8
 //       uint64_t q = prime[iter];


        uint64_t N = p * q;
        // uint64_t sqrt_N = 0;
        uint64_t sqrt_Nk = 0;
        uint64_t k = 1;
        DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
        // sqrt_N = trunc(sqrt(N)) + 1;

        // selecting the size of the factor base
        // double size_B;
        // size_B = exp (sqrt (log(N) * log(log(N))) );
        // size_B = pow(size_B , sqrt(2)/4);
        // DEBUG (2,"size of factor base size_B=%f\n", size_B);

        // selecting smooth primes 
        std::vector<long> p_smooth;
        DEBUG (2, "smooth numbers\n");

        int p_size;
        // p_size = 2* log(N);
        p_size = exp (sqrt (log(N) * log(log(N))) );
        p_size = trunc(sqrt(p_size));
        // int p_size = 90;
        // p_size *= 2;

        for (int i = 2; p_smooth.size() < p_size; ++i) // 2 log n
        {
            p_smooth.push_back(prime[i]);
        }
        DEBUG(2, "p_smooth size %d\n", p_smooth.size());

        // make_smooth_numbers(p_smooth, size_B, N);

        // if ((p_smooth.size() < size_B))
        // {
        //     ERROR ("to small primes \n");
        //     DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
        //     continue;
        //     // exit(0);
        // }

        // selecting the sieving interval
        long M;
        M = exp (sqrt (log(N) * log(log(N))) );
        // M = pow(M , 3*sqrt(2)/4);
        // DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
        // M = trunc(sqrt(M));
        M = pow(M , 3/2);
         // M *= 2;
        // M = 20* log(N);

        DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
        // exit(0);
        
        // *** construct our sieve *** //
        
        std::vector<long> X;
        std::vector<long> Y;
        // for (k = 1; k < 6; ++k)
        // {
            // std::vector<long> X1;
            // std::vector<long> Y1;
            // sqrt_Nk = trunc(sqrt(N * k)) + 1;
            // construct_xy(X1, Y1, sqrt_Nk, N, M);
            // X.insert(X.end(), X1.begin(), X1.end());
            // Y.insert(Y.end(), Y1.begin(), Y1.end());
        // }

        // for (uint64_t i = 0; i < X.size(); ++i)
        // {
        //     DEBUG (2, "X = %llu\t",X[i]);
        //     DEBUG (2, "Y = %li\t",Y[i]);
        //     DEBUG (2, "\n");
        // }
        
        // DEBUG (2, "X size  = %d\n",X.size());
        // simple sieve 
        std::vector< std::vector<uint64_t> > v_exp(0, std::vector<uint64_t> (p_smooth.size() + 1)) ;
        std::vector<int> smooth_num;
        // std::vector<int> smooth_num_history;
        // DEBUG (2, "v_exp size  = %d\n",v_exp.size());

        bin_matrix_t m_all_unchanged(p_smooth.size() + 1);
        bin_matrix_t m_all(p_smooth.size() + 1);
        bin_matrix_t m_counter(p_smooth.size() + 1);
        std::vector<uint64_t> v_counter(p_smooth.size() + 1);
        // DEBUG(1, "smooth %d\n", p_smooth.size());
        // DEBUG(1, "size ========= %d\n", m_all_unchanged.collumn_size);
        // break;

        std::vector<long> Y_factored;
        // Y_factored = Y;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        // v_exp[i].size()-1
        uint64_t found = 0;
        // for (int y_number = 0; y_number < Y.size(); ++y_number) {

        // k = 1;
    int break_flag = 0;
    for (k = 1; k < 2; ++k)
    {
        DEBUG (3, "kkkkkkkkkkkkkkkkkkkk = %d\n",k);
        sqrt_Nk = trunc(sqrt(N * k)) + 1;
        int y_number = 0;
        for (long y_iter = 0; y_iter <= M; ++y_iter)
        // for (long y_iter = -M/2; y_iter <= M/2; ++y_iter)
        {
        // for (int w = 0; w < 2; ++w)
        {
            // if(w == 0)
            //     y_iter *= -1;
            // else
            //     y_iter *= -1;

            long long x_current = sqrt_Nk + y_iter;
            X.push_back(x_current);
            long long tmp = x_current*x_current;
            long Y_current;
            if(tmp < N){
                Y_current = tmp - N;
            }
            else{
                Y_current = tmp % N;
            }

            // We don't want use the same values for multiple times
            if ( std::find(Y.begin(), Y.end(), Y_current) != Y.end() ){
                continue;
            }

            Y.push_back(Y_current);
            y_number = Y.size() - 1;
            Y_factored.push_back(0);
            v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));

            // DEBUG (3, "X = %llu\t",x_current);
            // DEBUG (3, "Y = %li\n",Y[y_number]);
            // DEBUG (3, "y_number = %li\n",y_number);

            // #######################################################
                DEBUG (3, "X = %llu\t",x_current);
                DEBUG (3, "Y = %li\n",Y[y_number]);
                DEBUG (3, "y_number = %li\n",y_number);

            if(Y[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            Y_factored[y_number] = prime_factorisation(Y[y_number], p_smooth, v_exp[y_number]);
            
            if(Y_factored[y_number] == -1 || Y_factored[y_number] == 1){
                
                DEBUG (3, "Y = %li\n",Y[y_number]);
                
                // modulo-2 division 
                int null_flag = 1;
                null_flag = zero_vector_mod2_check(v_exp[y_number]);
                
                DEBUG (3, "%ld\n", Y[y_number]);

                // check if we alredy have null vector
                // skip negative value !!!!
                if (null_flag && Y_factored[y_number] > 0) {
                    std::vector<int64_t> tmp;
                    tmp.push_back(y_number);
                    found = euclid_gcd( X, Y, tmp, p, q, N, v_exp, p_smooth);
                    if (found)
                    {
                        DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
                        break_flag = 1;
                        break;
                        // exit(0);
                    }
                } else {

                    smooth_num.push_back(y_number);
                    // smooth_num_history.push_back(y_number);
                    // ERROR("filled1 %d\n", m_all_unchanged.filled);
                    if (m_all_unchanged.add_row(v_exp[y_number]) == 1){
                        m_all.add_row(v_exp[y_number]);

                        int max_exponent_num = (v_exp[y_number].size() - 1);
                        int count_limit = -2;
                        // ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);

                        while (v_exp[y_number][max_exponent_num] == 0 && max_exponent_num >= 0){
                            max_exponent_num--;
                        }
                        if (max_exponent_num >= 0)
                        {
                            // DEBUG (2,"%s %d max_exponent_num %d\n", __func__, __LINE__, max_exponent_num);
                            count_limit = add_counter_row(m_counter ,v_counter ,max_exponent_num);

                            DEBUG (2,"%s %d count_limit = %d\n", __func__, __LINE__, count_limit);
                            DEBUG (2,"counter== \n");
                            for (int i = 0; i < v_counter.size(); ++i) {
                                DEBUG (2,"%d\t", v_counter[i]);
                                
                            }
                            DEBUG (2,"\n");
                            DEBUG(2, "%s %d\n", __func__, __LINE__);
                            m_counter.show();
                            m_all_unchanged.show();
                            DEBUG(2, "%s %d\n", __func__, __LINE__);
                        }
                        else
                        {
                            ERROR("max_exponent_num error %s %d\n", __func__,__LINE__);
                            exit (0);
                        }
                        

                        if (max_exponent_num >= 0)
                        {
                            
                            if (count_limit > -1)
                            {
                                bin_matrix_t m_selected(p_smooth.size() + 1);
                                bin_matrix_t m_selected_unchanged(p_smooth.size() + 1);
                                std::vector<int> smooth_num_selected;
                                std::vector<int> smooth_num_selected_iter;

                                DEBUG(2, "find limit %d\n", count_limit);
                                m_counter.show();
                                m_all_unchanged.show();
                                for (int i = 0; i < m_counter.matrix.size(); ++i)
                                {
                                    if (m_counter.matrix[i][count_limit] == 1)
                                    {
                                        m_selected.add_row(m_all_unchanged.matrix[i]);
                                        smooth_num_selected.push_back(smooth_num[i]);
                                        smooth_num_selected_iter.push_back(i);
                                    }
                                }
                                m_selected.show();
                                m_selected_unchanged= m_selected;
                                int null_line = m_selected.resolve_matrix();
                                // exit (0);
                                // int null_line = m_selected.make_upper_triangular();
                                std::vector<int64_t> XYiters;

                                if (null_line > -1)
                                {
                                    // DEBUG(2, "collumn size %d\n", m_all_unchanged.collumn_size);
                                    for (uint64_t col = 0; col <  m_selected.filled; ++col)
                                    {
                                        DEBUG (2,"matrix[%d][%d] = %ld\n",null_line,col, m_selected.unit_matrix[null_line][col]);
                                        if( m_selected.unit_matrix[null_line][col] > 0)
                                        {
                                            DEBUG (2,"num = %d\t", smooth_num_selected[col]);
                                            DEBUG (2,"Y  = %ld\n", Y[smooth_num_selected[col]]);
                                            XYiters.push_back(smooth_num_selected[col]);
                                        }
                                    }
                                    DEBUG (2,"\n");

                                    // int found = 0;
                                    found = euclid_gcd( X, Y, XYiters, p, q, N, v_exp, p_smooth);
                                    // printf("found %lu\n", found);
                                    m_selected.show();
                                    if (found) {
                                        DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t", iter, iter_1, p, q);
                                        // exit( null_line);
                                        break_flag = 1;
                                        break;
                                    } else {
                                        int max_i = 0;
                                        int ret = 0;
                                        DEBUG (3," null_line %d\n",null_line );
                                        m_selected_unchanged.show();
                                        max_i = m_selected_unchanged.max_unit_num(m_selected.unit_matrix[null_line]);
                                        DEBUG (3," iter %d\n",max_i );
                                        // DEBUG (3," line %d\n",smooth_num_selected_iter[max_i]);

                                        ret = clean_matrix(m_all_unchanged, m_all,smooth_num, smooth_num_selected_iter[max_i]);
                                        if (!ret )
                                        {
                                            ERROR("clean_matrix");
                                            exit(0);
                                        }

                                        ret =  delete_counter_row(m_counter, v_counter, smooth_num_selected_iter[max_i]);
                                        if (!ret )
                                        {
                                            ERROR("delete_counter_row");
                                            exit(0);
                                        }

                                    }
                                } else {
                                    ERROR ("reslove matrix failed\n");
                                }
                            }
                        }
                        else{
                            ERROR( "empty string \n");
                            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
                            // exit(0);
                            break_flag = 1;
                            break;
                        }
                    }
                    else
                    {
                        ERROR("cant add aaaaa\n");
                        DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
                        break_flag = 1;
                        break;
                    }
                }
            }
        }}

        if(break_flag)
            break;
    }

        if (!found)
        {
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
            // continue;
        }

        finish = clock();
        DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);

    }
    }
}






// BOOST_AUTO_TEST_CASE(test_2) 
// {
//     // for (int iter_1 = 3; iter_1 < 4 ; iter_1++) 
//     // for (int iter_1 = 10000; iter_1 < 11000 ; iter_1++) 
//     // for (int iter_1 = 3; iter_1 < 1000 ; iter_1++) 
//     for (int iter_1 = 5760000; iter_1 < 5760030 ; iter_1++) 
//     {

//     for (int iter = iter_1 + 1 - 5753000; iter < 7030 ; iter++) 
//     // for (int iter = 3; iter < 1000 ; iter++) 
//     // for (int iter = iter_1 + 1; iter < 11000 ; iter++) 
//     // for (int iter = iter_1 + 1; iter < 5760030 ; iter++) 
//     // for (int iter = 3; iter < 4 ; iter++) 
//     {

//     // for (int iter = 15; iter < 16 ; iter++) {
//         // uint64_t p = prime[15];
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[16];
//         // uint64_t q = prime[31];

//         // uint64_t p = prime[235]; // k = 3 p = 10
//         // uint64_t q = prime[31];

//         // 5761456
//         // iter = 3243;
//         // iter_1 = 2332;

//         // iter = 100;
//         // iter_1 = 50;

//         uint64_t p = prime[iter_1];  // 10^8
//         uint64_t q = prime[iter];


//         uint64_t N = p * q;
//         // uint64_t sqrt_N = 0;
//         uint64_t sqrt_Nk = 0;
//         uint64_t k = 1;
//         DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        
//         // sqrt_N = trunc(sqrt(N)) + 1;

//         // selecting the size of the factor base
//         // double size_B;
//         // size_B = exp (sqrt (log(N) * log(log(N))) );
//         // size_B = pow(size_B , sqrt(2)/4);
//         // DEBUG (2,"size of factor base size_B=%f\n", size_B);

//         // selecting smooth primes 
//         std::vector<long> p_smooth;
//         DEBUG (2, "smooth numbers\n");

//         int p_size;
//         // int p_size = 2* log(N);
//         p_size = exp (sqrt (log(N) * log(log(N))) );
//         p_size = trunc(sqrt(p_size));
//         // int p_size = 90;
//         // p_size += 10;

//         for (int i = 2; p_smooth.size() < p_size; ++i) // 2 log n
//         {
//             p_smooth.push_back(prime[i]);
//         }
//         DEBUG(2, "p_smooth size %d\n", p_smooth.size());

//         // make_smooth_numbers(p_smooth, size_B, N);

//         // if ((p_smooth.size() < size_B))
//         // {
//         //     ERROR ("to small primes \n");
//         //     DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
//         //     continue;
//         //     // exit(0);
//         // }

//         // selecting the sieving interval
//         long M;
//         M = exp (sqrt (log(N) * log(log(N))) );
//         // DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
//         // M = trunc(sqrt(M));
//         M = pow(M , 3/2);
//          // M *= 2;
//         // M = 20* log(N);

//         DEBUG (2, "The sieving interval M=%" PRIu32 "\n", M);
//         // exit(0);
        
//         // *** construct our sieve *** //
        
//         std::vector<long> X;
//         std::vector<long> Y;
//         // for (k = 1; k < 6; ++k)
//         // {
//             // std::vector<long> X1;
//             // std::vector<long> Y1;
//             // sqrt_Nk = trunc(sqrt(N * k)) + 1;
//             // construct_xy(X1, Y1, sqrt_Nk, N, M);
//             // X.insert(X.end(), X1.begin(), X1.end());
//             // Y.insert(Y.end(), Y1.begin(), Y1.end());
//         // }

//         // for (uint64_t i = 0; i < X.size(); ++i)
//         // {
//         //     DEBUG (2, "X = %llu\t",X[i]);
//         //     DEBUG (2, "Y = %li\t",Y[i]);
//         //     DEBUG (2, "\n");
//         // }
        
//         // DEBUG (2, "X size  = %d\n",X.size());
//         // simple sieve 
//         std::vector< std::vector<uint64_t> > v_exp(0, std::vector<uint64_t> (p_smooth.size() + 1)) ;
//         std::vector<int> smooth_num;
//         // std::vector<int> smooth_num_history;
//         // DEBUG (2, "v_exp size  = %d\n",v_exp.size());

//         bin_matrix_t m_all_unchanged(p_smooth.size() + 1);
//         bin_matrix_t m_all(p_smooth.size() + 1);
//         bin_matrix_t m_counter(p_smooth.size() + 1);
//         std::vector<uint64_t> v_counter(p_smooth.size() + 1);
//         // DEBUG(1, "smooth %d\n", p_smooth.size());
//         // DEBUG(1, "size ========= %d\n", m_all_unchanged.collumn_size);
//         // break;

//         std::vector<long> Y_factored;
//         // Y_factored = Y;
//         // add sign to exponent matrix
//         #define NEGATIVE_SIGN    0 
//         // v_exp[i].size()-1
//         uint64_t found = 0;
//         // for (int y_number = 0; y_number < Y.size(); ++y_number) {

//         // k = 1;
//     int break_flag = 0;
//     for (k = 1; k < 3; ++k)
//     {
//         DEBUG (3, "kkkkkkkkkkkkkkkkkkkk = %d\n",k);
//         sqrt_Nk = trunc(sqrt(N * k)) + 1;
//         int y_number = 0;
//         for (long y_iter = 0; y_iter <= M; ++y_iter)
//         // for (long y_iter = -M/2; y_iter <= M/2; ++y_iter)
//         {
//         // for (int w = 0; w < 2; ++w)
//         {
//             // if(w == 0)
//             //     y_iter *= -1;
//             // else
//             //     y_iter *= -1;

//             long long x_current = sqrt_Nk + y_iter;
//             X.push_back(x_current);
//             long long tmp = x_current*x_current;
//             long Y_current;
//             if(tmp < N){
//                 Y_current = tmp - N;
//             }
//             else{
//                 Y_current = tmp % N;
//             }

//             // We don't want use the same values for multiple times
//             if ( std::find(Y.begin(), Y.end(), Y_current) != Y.end() ){
//                 continue;
//             }

//             Y.push_back(Y_current);
//             y_number = Y.size() - 1;
//             Y_factored.push_back(0);
//             v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));

//             // DEBUG (3, "X = %llu\t",x_current);
//             // DEBUG (3, "Y = %li\n",Y[y_number]);
//             // DEBUG (3, "y_number = %li\n",y_number);

//             // #######################################################
//                 DEBUG (3, "X = %llu\t",x_current);
//                 DEBUG (3, "Y = %li\n",Y[y_number]);
//                 DEBUG (3, "y_number = %li\n",y_number);

//             if(Y[y_number] < 0 )
//                 v_exp[y_number][NEGATIVE_SIGN] = 1;

//             Y_factored[y_number] = prime_factorisation(Y[y_number], p_smooth, v_exp[y_number]);
            
//             if(Y_factored[y_number] == -1 || Y_factored[y_number] == 1){
                
//                 DEBUG (3, "Y = %li\n",Y[y_number]);
                
//                 // modulo-2 division 
//                 int null_flag = 1;
//                 null_flag = zero_vector_mod2_check(v_exp[y_number]);
                
//                 DEBUG (3, "%ld\n", Y[y_number]);

//                 // check if we alredy have null vector
//                 // skip negative value !!!!
//                 if (null_flag && Y_factored[y_number] > 0) {
//                     std::vector<int64_t> tmp;
//                     tmp.push_back(y_number);
//                     found = euclid_gcd( X, Y, tmp, p, q, N, v_exp, p_smooth);
//                     if (found)
//                     {
//                         DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", iter, iter_1, p, q);
//                         break_flag = 1;
//                         break;
//                         // exit(0);
//                     }
//                 } else {

//                     smooth_num.push_back(y_number);
//                     // smooth_num_history.push_back(y_number);
//                     // ERROR("filled1 %d\n", m_all_unchanged.filled);
//                     if (m_all_unchanged.add_row(v_exp[y_number]) == 1){
//                         m_all.add_row(v_exp[y_number]);

//                         int max_exponent_num = (v_exp[y_number].size() - 1);
//                         int count_limit = -2;
//                         // ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);

//                         while (v_exp[y_number][max_exponent_num] == 0 && max_exponent_num >= 0){
//                             max_exponent_num--;
//                         }
//                         if (max_exponent_num >= 0)
//                         {
//                             // DEBUG (2,"%s %d max_exponent_num %d\n", __func__, __LINE__, max_exponent_num);
//                             count_limit = add_counter_row(m_counter ,v_counter ,max_exponent_num);

//                             // DEBUG (2,"%s %d count_limit = %d\n", __func__, __LINE__, count_limit);
//                             // DEBUG (2,"counter== \n");
//                             // for (int i = 0; i < v_counter.size(); ++i) {
//                             //     DEBUG (2,"%d\t", v_counter[i]);
                                
//                             // }
//                             // DEBUG (2,"\n");
//                             // DEBUG(2, "%s %d\n", __func__, __LINE__);
//                             // m_counter.show();
//                             // m_all_unchanged.show();
//                             // DEBUG(2, "%s %d\n", __func__, __LINE__);
//                         }
//                         else
//                         {
//                             ERROR("max_exponent_num error %s %d\n", __func__,__LINE__);
//                             exit (0);
//                         }
                        
//                         // DEBUG (2,"size num = %d\t", smooth_num.size());
//                         int null_line = m_all.make_upper_triangular();

//                         if (null_line > -1)
//                         {
//                             std::vector<int64_t> XYiters;
//                             DEBUG(3, "line %d NUll line  %d=============", __LINE__ , null_line);
//                             for (uint64_t col = 0; col <  m_all.filled; ++col)
//                             {
//                                 DEBUG (3,"matrix[%d][%d] = %ld\n",null_line,col, m_all.unit_matrix[null_line][col]);
//                                 if( m_all.unit_matrix[null_line][col] > 0)
//                                 {
//                                     DEBUG (3,"size num = %d\t", smooth_num.size());
//                                     DEBUG (3,"num = %d\t", smooth_num[col]);
//                                     DEBUG (3,"Y  = %ld\n", Y[smooth_num[col]]);
//                                     XYiters.push_back(smooth_num[col]);
//                                 }
//                             }
//                             DEBUG (2,"\n");

//                             // int found = 0;
//                             found = euclid_gcd( X, Y, XYiters, p, q, N, v_exp, p_smooth);
//                             // printf("found %lu\n", found);
//                             // m_all.show();
//                             if (found) {
//                                 DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", iter, iter_1, p, q);
//                                 // exit( null_line);
//                                 break_flag = 1;
//                                 break;
//                             } else {
//                                 int max_i = 0;
//                                 int ret = 0;
//                                 DEBUG (3,"line %d null_line %d\n",__LINE__, null_line );

//                                 max_i = m_all_unchanged.max_unit_num(m_all.unit_matrix[null_line]);
//                                 DEBUG (3," iter %d\n",max_i );

//                                 // DEBUG (3," smooth num %d\n",smooth_num[max_i]);
//                                 // DEBUG (3," Y %d\n",Y[smooth_num[max_i]]);

//                                 ret = clean_matrix(m_all_unchanged, m_all,smooth_num, max_i);
//                                 if (!ret )
//                                 {
//                                     ERROR("clean_matrix");
//                                     exit(0);
//                                 }

//                                 ret =  delete_counter_row(m_counter, v_counter, max_i);
//                                 if (!ret )
//                                 {
//                                     ERROR("delete_counter_row");
//                                     exit(0);
//                                 }

//                                 continue;
//                             }
//                         }
//                             // DEBUG(3, "%s %d\n", __func__, __LINE__);

//                         if (max_exponent_num >= 0)
//                         {
                            
//                             if (count_limit > -1)
//                             {
//                                 bin_matrix_t m_selected(p_smooth.size() + 1);
//                                 bin_matrix_t m_selected_unchanged(p_smooth.size() + 1);
//                                 std::vector<int> smooth_num_selected;
//                                 std::vector<int> smooth_num_selected_iter;

//                                 DEBUG(2, "find limit %d\n", count_limit);
//                                 m_counter.show();
//                                 m_all_unchanged.show();
//                                 for (int i = 0; i < m_counter.matrix.size(); ++i)
//                                 {
//                                     if (m_counter.matrix[i][count_limit] == 1)
//                                     {
//                                         m_selected.add_row(m_all_unchanged.matrix[i]);
//                                         smooth_num_selected.push_back(smooth_num[i]);
//                                         smooth_num_selected_iter.push_back(i);
//                                     }
//                                 }
//                                 m_selected.show();
//                                 m_selected_unchanged= m_selected;
//                                 null_line = m_selected.resolve_matrix();
//                                 // exit (0);
//                                 // int null_line = m_selected.make_upper_triangular();
//                                 std::vector<int64_t> XYiters;

//                                 if (null_line > -1)
//                                 {
//                                     // DEBUG(2, "collumn size %d\n", m_all_unchanged.collumn_size);
//                                     for (uint64_t col = 0; col <  m_selected.filled; ++col)
//                                     {
//                                         DEBUG (2,"matrix[%d][%d] = %ld\n",null_line,col, m_selected.unit_matrix[null_line][col]);
//                                         if( m_selected.unit_matrix[null_line][col] > 0)
//                                         {
//                                             DEBUG (2,"num = %d\t", smooth_num_selected[col]);
//                                             DEBUG (2,"Y  = %ld\n", Y[smooth_num_selected[col]]);
//                                             XYiters.push_back(smooth_num_selected[col]);
//                                         }
//                                     }
//                                     DEBUG (2,"\n");

//                                     // int found = 0;
//                                     found = euclid_gcd( X, Y, XYiters, p, q, N, v_exp, p_smooth);
//                                     // printf("found %lu\n", found);
//                                     m_selected.show();
//                                     if (found) {
//                                         DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", iter, iter_1, p, q);
//                                         // exit( null_line);
//                                         break_flag = 1;
//                                         break;
//                                     } else {
//                                         int max_i = 0;
//                                         int ret = 0;
//                                         DEBUG (3," null_line %d\n",null_line );
//                                         m_selected_unchanged.show();
//                                         max_i = m_selected_unchanged.max_unit_num(m_selected.unit_matrix[null_line]);
//                                         DEBUG (3," iter %d\n",max_i );
//                                         // DEBUG (3," line %d\n",smooth_num_selected_iter[max_i]);

//                                         ret = clean_matrix(m_all_unchanged, m_all,smooth_num, smooth_num_selected_iter[max_i]);
//                                         if (!ret )
//                                         {
//                                             ERROR("clean_matrix");
//                                             exit(0);
//                                         }

//                                         ret =  delete_counter_row(m_counter, v_counter, smooth_num_selected_iter[max_i]);
//                                         if (!ret )
//                                         {
//                                             ERROR("delete_counter_row");
//                                             exit(0);
//                                         }

//                                     }
//                                 } else {
//                                     ERROR ("reslove matrix failed\n");
//                                 }
//                             }
//                         }
//                         else{
//                             ERROR( "empty string \n");
//                             DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
//                             // exit(0);
//                             break_flag = 1;
//                             break;
//                         }
//                     }
//                     else
//                     {
//                         ERROR("cant add aaaaa\n");
//                         DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
//                         break_flag = 1;
//                         break;
//                     }
//                 }
//             }
//         }}

//         if(break_flag)
//             break;
//     }

//         if (!found)
//         {
//             DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \n", iter, iter_1, p, q);
//             continue;
//         }


//     }
//     }
// }




