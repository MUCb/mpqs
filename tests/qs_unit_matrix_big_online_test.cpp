#define BOOST_TEST_MODULE QS unit maytrix Test 
#include <boost/test/included/unit_test.hpp> 

#include "dynamic_bin_matrix.h"
// #include "primes.h"
#include "quadratic_sieve_big.h"
#include "log.h"

#include "greatest_common_divisor_big.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes_10_8.h"
#include "big_2.h"

#include <math.h>
#include <time.h>

int showDebugMsg = 1;

BOOST_AUTO_TEST_CASE(test_2) 
{
    //int iter_1 = 5005;
    int iter_1 = 5000;
    //int iter_1 = 124;
    while (iter_1 < 5300 ) 
    //while (iter_1 < 78400 ) 
    {
        iter_1 += 5;
        // iter_1 += 10;
        // iter_1 = ceil(it1* (double)iter_1);
        
    int iter = iter_1 + 597;
    //int iter = 5719;
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
        //iter += 36;
 


//    int iter = 0;
//    int iter_1 = 0;
 //   for (iter_1 = 5000; iter_1 < 6000 ; iter_1++)
 //   for (iter = 7000; iter < 9000 ; iter=iter+3) 
  //  {

        time_t start;
        time_t finish;
        start = clock();
        
        //big p(prime[13123]);
        big_2 p(prime[iter_1]);
        //big q(prime[18123]);
        big_2 q(prime[iter]);
 
        //big p = str1;
        //big q = str2;
        big_2 one = 1;
        big_2 null = 0;


        big_2 N = p * q;
        big_2 sqrt_N = 0;
        uint64_t sqrt_Nk = 0;
        uint64_t k = 1;
	LOG(1) std::cout << "iter = " << iter << "\titer_1 " << iter_1 << "\tp=" << p << "\tq=" << q << "\tN=" << N << "\n";
        //DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
        sqrt_N = squareRoot(N);

        sqrt_N = sqrt_N + one;
	LOG(2) std::cout << "n=" << N << "\tsqrt=" << sqrt_N <<  "\n";

        // selecting the size of the factor base
        double size_B;
        DEBUG (2,"log _B=%f\n", ln(N));
     //exit(0);
        size_B = exp (sqrt (ln(N) * log(ln(N))) );
        size_B = pow(size_B , sqrt(2)/4);
        DEBUG (2,"size of factor base size_B=%f\n", size_B);
        // selecting smooth primes 
        std::vector<long long> p_smooth;
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
        std::vector<long long> p_smooth_copy = p_smooth;


        // selecting the sieving interval
        long long  M;
        M = exp (sqrt (ln(N) * log(ln(N))) );
        M = pow(M , 3*sqrt(2)/4);

        DEBUG (2, "The sieving interval M=%li\n", M);
        
        // *** construct our sieve *** //
        std::vector<big_2> X;
        std::vector<big_2> Y;
        std::vector<big_2> V;

        // simple sieve 
        std::vector<long> solution_candidates_number;
        std::vector< std::vector<uint64_t> > v_exp;
        std::vector< std::vector<uint64_t> > v_exp_copy;
        // std::vector<uint64_t> v_extra_exp;
        std::vector<int> smooth_num;
        // bin_matrix_t m1(p_smooth.size() + 1);
        std::vector< std::vector<uint64_t> > max_exp_count;

        bin_matrix_t m_all_unchanged(p_smooth.size() + 1);
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
	    //std::cout <<   "X" << j << " =" << X[y_number] << "\n";
            big_2 tmp = X[y_number]*X[y_number];
	    //std::cout <<   "tmp " << tmp << "\n";
		//std::cout <<   "N " << N << "\n";
            if(tmp < N) {
		//std::cout <<   "tmp sign " << tmp << "\n";
		//std::cout <<   "N sign " <<  N << "\n";
		tmp = N - tmp ;
		tmp.sign = 1;
		//std::cout <<   "tmp1 " << tmp << "\n";
		//std::cout <<   "N " << N << "\n";
                Y.push_back(tmp);
                //Y.push_back(N-tmp);
            } else
                Y.push_back(tmp % N);
            LOG(2) std::cout << "X = " << X[y_number] << "\tY = " << Y[y_number] << "\n";
            //exit(0);
            #define NEGATIVE_SIGN    0 
            #define FIRST_VALUE      1

            v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));
            v_exp_copy.push_back(std::vector<uint64_t> (p_smooth.size() + 1));;
            V.push_back(Y[y_number]);

            if(Y[y_number] < null )
                v_exp[y_number][NEGATIVE_SIGN] = 1;
	    //std:: cout << "|" << v_exp[y_number][NEGATIVE_SIGN] << "|\n";

            V[y_number] = prime_factorisation(Y[y_number], p_smooth, v_exp[y_number]);


		//std::cout<< "y="<< Y[y_number] << "\tx=" << X[y_number] << "\tv=" << V[y_number] << "\n";
            v_exp_copy[y_number] = v_exp[y_number];
	    big_2 one(1);
	    big_2 min_one(-1);

            if(V[y_number] == min_one || V[y_number] == one){

                int null_flag = 1;
           //exit(0); 
                null_flag = zero_vector_mod2_check(v_exp[y_number]);

                if (null_flag && V[y_number] > 0) { // sign check is extra !!!!
                    continue;
                    //    will be added later  ##########################
                    big_2 found = 0;
                    std::vector<int64_t> tmp;
                    tmp.push_back(y_number);
                    found = euclid_gcd_big( X, Y, tmp, p, q, N,v_exp_copy, p_smooth);
                    // found = euclid_gcd( X, Y, tmp, p, q, N);
                    if (! (found == 0))
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
// added
                        // DEBUG (2,"size num = %d\t", smooth_num.size());
                        int null_line = m_all.make_upper_triangular();

                        if (null_line > -1)
                        {
                            std::vector<int64_t> XYiters;
                            DEBUG(3, "line %d NUll line  %d=============", __LINE__ , null_line);
                            for (uint64_t col = 0; col <  m_all.filled; ++col)
                            {
                                DEBUG (3,"matrix[%d][%d] = %ld\n",null_line,col, m_all.unit_matrix[null_line][col]);
                                if( m_all.unit_matrix[null_line][col] > 0)
                                {
                                    DEBUG (3,"size num = %d\t", smooth_num.size());
                                    DEBUG (3,"num = %d\t", smooth_num[col]);
				    LOG(3) std::cout << "Y  = " <<  Y[smooth_num[col]] << "\n";
                                    XYiters.push_back(smooth_num[col]);
                                }
                            }
                            DEBUG (2,"\n");

                            big found = 0;
                            found = euclid_gcd_big( X, Y, XYiters, p, q, N, v_exp, p_smooth);
                            // printf("found %lu\n", found);
                            // m_all.show();
                            if (found.size != 0) {
                                DEBUG (0, "Found solution i=%d\tj=%d p=%" PRIu64 "\tq=%" PRIu64 "\n", iter, iter_1, p, q);
                                // exit( null_line);
                                exit_flag=1;
                                //break_flag = 1;
                                break;
                            } else {
                                int max_i = 0;
                                int ret = 0;
                                DEBUG (3,"line %d null_line %d\n",__LINE__, null_line );

                                max_i = m_all_unchanged.max_unit_num(m_all.unit_matrix[null_line]);
                                DEBUG (3," iter %d\n",max_i );

                                // DEBUG (3," smooth num %d\n",smooth_num[max_i]);
                                // DEBUG (3," Y %d\n",Y[smooth_num[max_i]]);

                                ret = clean_matrix(m_all_unchanged, m_all,smooth_num, max_i);
                                if (!ret )
                                {
                                    ERROR("clean_matrix");
                                    exit(0);
                                }

                                ret =  delete_counter_row(m_counter, v_counter, max_exponent_num, max_i);
                                if (!ret )
                                {
                                    ERROR("delete_counter_row");
                                    exit(0);
                                }

                                continue;
                            }
                        }
                        // DEBUG(3, "%s %d\n", __func__, __LINE__);
// added

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
                                            LOG(2) std::cout << "Y  = " << Y[smooth_num_selected[col]] << "\n";
                                            P11.push_back(smooth_num_selected[col]);
                                        }
                                    }
                                    DEBUG (2,"\n");

                                    big_2 found = 0;
                                    // found = euclid_gcd( X, Y, P11, p, q, N);
                                    found = euclid_gcd_big( X, Y, P11, p, q, N, v_exp_copy, p_smooth);
                                    // printf("found %lu\n", found);
                                    m_selected.show();
                                    if (found.size != 0) {
					LOG(0) std::cout << "find " << p << "\t" << q << "\t" << m_selected.filled<< "\n";
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
        LOG(0) std::cout << "Fail solution i=" << iter << "\tj=" << iter_1 << " p=" << p << "\tq=" << q << "\n";

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
