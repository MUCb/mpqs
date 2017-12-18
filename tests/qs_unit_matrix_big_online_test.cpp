//#define BOOST_TEST_MODULE QS unit maytrix Test 
//#include <boost/test/included/unit_test.hpp> 
#include <iostream>
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

//BOOST_AUTO_TEST_CASE(test_2) 
int main (void)
{
    int iter_1 = 5122300;
    int iter = 5561457;

 
    time_t start;
    time_t finish;
    start = clock();
    
    FILE * pFile;
    char mystring [100];
    pFile = fopen ("prime_1","r");
    if (pFile == NULL) perror ("Error opening file");
    else {
        if ( fgets (mystring , 100 , pFile) != NULL ) {
            //puts (mystring);
        } else {
            std::cout << "error read prime numbers 1\n";
            return 1;
        }
        fclose (pFile);
    }

    // remove new line character
    char *pos;
    if ((pos=strchr(mystring, '\n')) != NULL)
            *pos = '\0';
    
    big_2 p(mystring);

    //std::cout << "p " << p << "\n";

    pFile = fopen ("prime_2","r");
    if (pFile == NULL) perror ("Error opening file");
    else {
        if ( fgets (mystring , 100 , pFile) != NULL ) {
            //puts (mystring);
        } else {
            std::cout << "error read prime numbers 2\n";
            return 1;
        }
        fclose (pFile);
    }
    
    // remove new line character
    if ((pos=strchr(mystring, '\n')) != NULL)
            *pos = '\0';

    big_2 q(mystring);
    //std:cout << "q " << q << "\n";

    big_2 one = 1;
    big_2 null = 0;


    big_2 N = p * q;
    big_2 sqrt_N = 0;
    LOG(1) std::cout << "iter = " << iter 
                    << "\titer_1 " << iter_1 
                    << "\tp=" << p 
                    << "\tq=" << q 
                    << "\tN=" << N << "\n";
    //DEBUG (1, "p=%" PRIu64 "\tq=%" PRIu64 "\tp*q=N=%" PRIu64 "\n", p, q, N);
    sqrt_N = squareRoot(N);

    sqrt_N = sqrt_N + one;
    LOG(2) std::cout << "n=" << N << "\tsqrt=" << sqrt_N <<  "\n";

    // selecting the size of the factor base
    double size_B;
    //DEBUG (2,"log _B=%f\n", ln(N));
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
        //exit (0);
        return 1;
    }


    // selecting the sieving interval
    long long  M;
    M = exp (sqrt (ln(N) * log(ln(N))) );
    M = pow(M , 3*sqrt(2)/4);

    DEBUG (2, "The sieving interval M=%li\n", M);
        
    // *** construct our sieve *** //
    std::vector<big_2> X;
    std::vector<big_2> X_sm;
    std::vector<big_2> Y;
    std::vector<big_2> Y_sm;
    std::vector<big_2> V;

    // simple sieve 
    std::vector<long> solution_candidates_number;
    std::vector< std::vector<uint64_t> > v_exp;
    std::vector< std::vector<uint64_t> > v_exp_sm;
    std::vector<int> smooth_num;

    bin_matrix_t m_all(p_smooth.size() + 1);

    int exit_flag = 0;
    for (long  j = 0, y_number = -1; j < M/2; j++){
        for (int  d = 0; d < 2; d++){

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

#define NEGATIVE_SIGN    0 
#define FIRST_VALUE      1

            v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));
            V.push_back(Y[y_number]);

            if(Y[y_number] < null )
                v_exp[y_number][NEGATIVE_SIGN] = 1;
            //std:: cout << "|" << v_exp[y_number][NEGATIVE_SIGN] << "|\n";

            V[y_number] = prime_factorisation(Y[y_number], p_smooth, v_exp[y_number]);


            //std::cout<< "y="<< Y[y_number] << "\tx=" << X[y_number] << "\tv=" << V[y_number] << "\n";
            big_2 one(1);
            big_2 min_one(-1);

            if(V[y_number] == min_one || V[y_number] == one){

                int null_flag = 1;
                //exit(0); 
                null_flag = zero_vector_mod2_check(v_exp[y_number]);

                if (null_flag && V[y_number] > 0) { // sign check is extra !!!!
                    //continue;
                    big_2 found = 0;
                    std::vector<int64_t> tmp;
                    tmp.push_back(y_number);
                    found = euclid_gcd_big( X, Y, tmp, p, q, N,v_exp, p_smooth);
                    if (! (found == 0)) {
                        exit_flag = 1;
                        break;
                    }
                } else {
                    smooth_num.push_back(y_number);
                    DEBUG(3, "%s %d  try to add %li \n",__func__, __LINE__, y_number);


                    if (m_all.add_row(v_exp[y_number]) == 1){
                        int exponent_num = (v_exp[y_number].size() - 1);
                        // ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);
                        int count_flag = 0;
                        //add_counter_row(m_counter ,counter ,exponent_num);
                        // DEBUG (2,"size num = %d\t", smooth_num.size());
                        m_all.show();
                        int null_line = m_all.make_upper_triangular_static();

                        if (null_line > -1) {
                            std::vector<int64_t> XYiters;
                            DEBUG(3, "line %d NUll line  %d=============", __LINE__ , null_line);
                            for (uint64_t col = 0; col <  m_all.filled; ++col) {
                                DEBUG (3,"matrix[%d][%d] = %ld\n",null_line,col, m_all.unit_matrix[null_line][col]);
                                if( m_all.unit_matrix[null_line][col] > 0) {
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
                                std::cout << "Found solution i=" << iter << "\tj=" << iter_1 << " p=" << p << " q=" << q << "\n";
                                // exit( null_line);
                                exit_flag=1;
                                //break_flag = 1;
                                break;
                            } else {
                                m_all.delete_row(m_all.filled -1);
                                DEBUG (3,"delete matrix raw %d\n",__LINE__ );
                                m_all.show();
                                smooth_num.pop_back();
                            }
                        }

                    }
                    else
                    {
                        ERROR("cant add aaaaa\n");
                        exit(0);
                    }

                }
                DEBUG (3, "\n");
            }
        }
        if (exit_flag)
            break;
    }
    if(!exit_flag)
        LOG(0) std::cout << "Fail solution i=" << iter << "\tj=" << iter_1 << " p=" << p << "\tq=" << q << "\n";


    return 0;
}
