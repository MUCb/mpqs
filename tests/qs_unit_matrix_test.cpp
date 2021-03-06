#define BOOST_TEST_MODULE QS unit maytrix Test
#include <boost/test/included/unit_test.hpp> 


#include "dynamic_bin_matrix.h"
// #include "primes.h"
#include "quadratic_sieve.h"
#include "log.h"

#include "greatest_common_divisor.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes.h"

 #include <math.h>
#include <time.h>

int showDebugMsg = 1;

BOOST_AUTO_TEST_CASE(test_2) 
{
    //int iter = 7000;
    int iter_1 = 5000;

    //int iter_1 = 124;
    while (iter_1 < 5300 ) 
    // while (iter_1 < 78400 ) 
    {
        iter_1 += 5;
        // iter_1 += 10;
        // iter_1 = ceil(it1* (double)iter_1);
        
    int iter = iter_1 + 597;
    //int iter = 112;
    while (iter < 6000 )

    // for (int iter = 3; iter < 1000 ; iter++) 
    // for (int iter = 3; iter < 4 ; iter++) 
    // for (int iter = 10000; iter < 10200 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 10200 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 5760030 ; iter++) 
    // for (int iter = iter_1 + 1; iter < 1000 ; iter++) 
    // for (int iter = 10; iter < 11 ; iter++) 
    {
        iter += 9;
 


//    int iter = 0;
//    int iter_1 = 0;
 //   for (iter_1 = 5000; iter_1 < 6000 ; iter_1++)
 //   for (iter = 7000; iter < 9000 ; iter=iter+3) 
  //  {

        time_t start;
        time_t finish;
        start = clock();
        
        //uint64_t p = prime[200]; // k = 3 p = 10
        uint64_t p = prime[iter_1]; // k = 3 p = 10
        uint64_t q = prime[iter];
        //uint64_t q = prime[212];


        // uint64_t p = prime[900]; // k = 3 p = 10
        // uint64_t q = prime[500];

        // uint64_t p = prime[1200]; // k = 3 p = 10
        // uint64_t q = prime[1450];


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

        make_smooth_numbers(p_smooth, size_B, N);

        if ((p_smooth.size() < size_B))
        {
            //ERROR ("to small primes \n");
            DEBUG (0, "Fail solution i=%d\tj=%d p=%lu\tq=%lu\t", iter, iter_1, p, q);
            finish = clock();
            //DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
            //continue;
            exit (0);
        }
        std::vector<long> p_smooth_copy = p_smooth;


        // selecting the sieving interval
        long  M;
        M = exp (sqrt (log(N) * log(log(N))) );
        M = pow(M , 3*sqrt(2)/4);

        DEBUG (2, "The sieving interval M=%li\n", M);
        
        // *** construct our sieve *** //
        std::vector<long> X;
        std::vector<long> Y;
        std::vector<long> V;

        // simple sieve 
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp;
        std::vector< std::vector<uint64_t> > v_exp_copy;
        // std::vector<uint64_t> v_extra_exp;
        std::vector<int> smooth_num;
        // bin_matrix_t m1(p_smooth.size() + 1);
        std::vector< std::vector<uint64_t> > max_exp_count;

        bin_matrix_t m_all(p_smooth.size() + 1);
        bin_matrix_t m_counter(p_smooth.size() + 1);
        std::vector<uint64_t> counter(p_smooth.size() + 1);

        int exit_flag = 0;
        // DEBUG (2, "%s %d\n", __func__, __LINE__);
        for (long  j = 0, y_number = -1; j < M/2; j++){
        for (int  d = 0; d < 2; d++)
        {
		if(d == 1 && j == 0)
			continue;
		if(d == 0 )
			X.push_back(sqrt_N - j);
		else
			X.push_back(sqrt_N + j);
	    y_number++;
            // DEBUG (2, "%s %d\n", __func__, __LINE__);
            DEBUG (4, "X%li =%lu\n",j, X[y_number] );
            long long tmp = X[y_number]*X[y_number];
            if(tmp < N)
                Y.push_back(tmp - N);
            else
                Y.push_back(tmp % N);
            DEBUG (2, "X = %li\t",X[y_number]);
            DEBUG (2, "Y = %li\t",Y[y_number]);
            DEBUG (2, "\n");
            
            #define NEGATIVE_SIGN    0 
            #define FIRST_VALUE      1

            v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));
            v_exp_copy.push_back(std::vector<uint64_t> (p_smooth.size() + 1));;
            V.push_back(Y[y_number]);

            if(Y[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            V[y_number] = prime_factorisation(Y[y_number], p_smooth, v_exp[y_number]);


            v_exp_copy[y_number] = v_exp[y_number];

            if(V[y_number] == -1 || V[y_number] == 1){


                int null_flag = 1;
                null_flag = zero_vector_mod2_check(v_exp[y_number]);

                if (null_flag && V[y_number] > 0) { // sign check is extra !!!!
                    continue;
                    //    will be added later  ##########################
                    uint64_t found = 0;
                    std::vector<int64_t> tmp;
                    tmp.push_back(y_number);
                    found = euclid_gcd( X, Y, tmp, p, q, N,v_exp_copy, p_smooth);
                    // found = euclid_gcd( X, Y, tmp, p, q, N);
                    if (found)
                        break;
                } else 
                {
                    smooth_num.push_back(y_number);
                    DEBUG(3, "%s %d  try to add %li \n",__func__, __LINE__, y_number);


                    if (m_all.add_row(v_exp[y_number]) == 1){
                        int exponent_num = (v_exp[y_number].size() - 1);
                        // ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);

                        while (v_exp[y_number][exponent_num] == 0 && exponent_num >= 0){
                            exponent_num--;
                        }
                        if (exponent_num >= 0)
                        {
                            int count_flag = 0;
                            add_counter_row(m_counter ,counter ,exponent_num);

                           DEBUG(2, "--count_flag |%d|\n",count_flag); 
                            while ((count_flag = is_counter_full(counter)) >= 0 )
                            {
                           DEBUG(2, "count_flag |%d|\n",count_flag); 
                                bin_matrix_t m_selected(p_smooth.size() + 1);
                                bin_matrix_t m_selected_copy(p_smooth.size() + 1);
                                std::vector<int> smooth_num_selected;
                                std::vector<int> smooth_num_selected_iter;

                                //ERROR("find limit %d, p  = %d q = %d p_smooth = %d\n", exponent_num, p, q, p_smooth.size());
                                DEBUG(2, "counter \n"); 
                                for (int i = 0; i < counter.size(); ++i) {
                                    DEBUG(2, "%d\t", counter[i] ); 
                                }
                                DEBUG(2, "\n counter \n"); 
                                m_counter.show();
                                m_all.show();
                                for (int i = 0; i < m_counter.matrix.size(); ++i)
                                {
                                    if (m_counter.matrix[i][count_flag] == 1)
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
                                        DEBUG (2,"matrix[%d][%lu] = %lu\n",null_line,col, m_selected.unit_matrix[null_line][col]);
                                        if( m_selected.unit_matrix[null_line][col] > 0)
                                        {
                                            DEBUG (2,"num = %d\t", smooth_num_selected[col]);
                                            DEBUG (2,"Y  = %ld\n", Y[smooth_num_selected[col]]);
                                            P11.push_back(smooth_num_selected[col]);
                                        }
                                    }
                                    DEBUG (2,"\n");

                                    int found = 0;
                                    // found = euclid_gcd( X, Y, P11, p, q, N);
                                    found = euclid_gcd( X, Y, P11, p, q, N, v_exp_copy, p_smooth);
                                    // printf("found %lu\n", found);
                                    m_selected.show();
                                    if (found) {
                                        ERROR("find %d\t%d\t%d",p, q, m_selected.filled);
                                        //DEBUG(0, "counter \n"); 
                                        //for (int i = 0; i < counter.size(); ++i) {
                                        //    DEBUG(0, "%d\t", counter[i] ); 
                                        //}
                                       // DEBUG(0, "\n counter \n"); 
                                        exit_flag=1;
                                        break;
                                        // exit( null_line);
                                    } else {
                                        int max_i = 0;
                                        DEBUG (3," null_line %d\n",null_line );
                                        m_selected_copy.show();
                                        //max_i = smooth_num_selected_iter.size() - 1;
                                        max_i = m_selected_copy.max_unit_num(m_selected.unit_matrix[null_line]);
                                        DEBUG (3," iter %d\n",max_i );

                                        DEBUG (3," line %d\n",smooth_num_selected_iter[max_i]);

                                        //DEBUG (3," delete before \n");
                                        //m_all.show();
                                        //m_all.delete_row( smooth_num_selected_iter[max_i] );
                                        //DEBUG (3," delete after \n");
                                        //m_all.show();
                                        DEBUG (3," delete before \n");
                                        m_counter.show();
                                        m_counter.matrix[ smooth_num_selected_iter[max_i]][count_flag] = 0;
                                        DEBUG (3," delete after \n");
                                        m_counter.show();

                                        counter[count_flag]--;
                                        //for (int i = exponent_num; i < v_exp[y_number].size(); ++i) {
                                        //    counter[i]--;
                                        //}

                                        //smooth_num.erase(smooth_num.begin() + smooth_num_selected_iter[max_i]);
                                    }
                                } else { 
                                        int max_i = 0;
                                        DEBUG (3," null_line %d\n",null_line );
                                        m_selected_copy.show();
                                        max_i = smooth_num_selected_iter.size() - 1;
                                        // max_i = m_selected_copy.max_unit_num(m_selected.unit_matrix[null_line]);
                                        DEBUG (3," iter %d\n",max_i );

                                        DEBUG (3," line %d\n",smooth_num_selected_iter[max_i]);

                                        //DEBUG (3," delete before \n");
                                        //m_all.show();
                                        //m_all.delete_row( smooth_num_selected_iter[max_i] );
                                        //DEBUG (3," delete after \n");
                                        //m_all.show();
                                        DEBUG (3," delete before \n");
                                        m_counter.show();
                                        m_counter.matrix[ smooth_num_selected_iter[max_i]][count_flag] = 0;
                                        DEBUG (3," delete after \n");
                                        m_counter.show();

                                        counter[count_flag]--;
                                        //for (int i = exponent_num; i < v_exp[y_number].size(); ++i) {
                                        //    counter[i]--;
                                        //}

                                        //smooth_num.erase(smooth_num.begin() + smooth_num_selected_iter[max_i]);
                                }

                                // exit(0);

                            }
                            if (exit_flag)
                                break;

                        }
                        else{
                            ERROR( "empty string \n");
                            exit(0);
                        }

                    }
                    else
                    {
                        ERROR("cant add aaaaa\n");
                        exit(0);
                    }



                    // m1.add_row(v_exp[y_number]);
                    // for (int f = 0; f < v_exp[y_number].size(); ++f)
                    // {
                    //     printf("[%d]%lu\t", f, v_exp[y_number][f]);
                    // }
                    // printf("------\n");

                    // max_exp_count.push_back(std::vector<uint64_t> (p_smooth.size() + 1));
                    // printf("size %d\n", v_exp[y_number].size());

                    // for(int k = v_exp[y_number].size() - 1 ; k >= 0; k--){
                    //     // DEBUG (2, "%s %d\n", __func__, k);
                    //     // DEBUG (2, "%s %d\n", __func__, __LINE__);
                    //     max_exp_count[max_exp_count.size() - 1][k] = 1;
                    //     if(v_exp[y_number][k] != 0)
                    //     {
                    //         break;
                    //     }
                    // }
                            // break;

                    // for (int f = 0; f < max_exp_count.size(); ++f)
                    // {
                    //     for (int g = 0; g < max_exp_count[0].size(); ++g){
                    //         printf("%lu\t", max_exp_count[f][g]);
                    //     }
                    //     printf("\n");
                    // }
                    // break;
                    // m1.show();


                }
                DEBUG (3, "\n");
                // break;
            }
            // exit (0);
        }
	if (exit_flag)
		break;
	}
        if(!exit_flag)
         DEBUG (0, "Fail solution i=%d\tj=%d p=%lu\tq=%lu\n", iter, iter_1, p, q);


//-------------------------------------
  

/*
        std::vector<int> smooth_num_back = smooth_num;
        bin_matrix_t m1(p_smooth.size() + 1);

        // DEBUG (2, "================ p_smooth=%d\n", p_smooth.size());
        int find_res = find_solution(m1, smooth_num_back, smooth_num, v_exp, p_smooth_copy,  X, Y, p, q, N);
        BOOST_CHECK(find_res   >= 0);
        if(find_res >= 0)
        {
            DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
        finish = clock();
        DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        } else {
            DEBUG (0, "Fail solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\t \t", iter, iter_1, p, q);
                    finish = clock();
        DEBUG (0, "time %f\n", (double)(finish - start) / CLOCKS_PER_SEC);
        }
  */      
 }
    }
}
