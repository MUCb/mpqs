//#define BOOST_TEST_MODULE QS unit maytrix Test 
//#include <boost/test/included/unit_test.hpp> 
#include <iostream>
#include "dynamic_bin_matrix.h"
// #include "primes.h"
#include "quadratic_sieve_big.h"
#include "log.h"

#include <fstream>
#include "greatest_common_divisor_big.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
//#include "primes_10_8.h"
#include "primes.h"
#include "numbers_dixon.h"
#include "big_2.h"

#include <math.h>
#include <time.h>

int showDebugMsg = 1;

int fread_number(const char * file_name, char * mystring) {
    FILE * pFile;
    pFile = fopen (file_name,"r");
    if (pFile == NULL) perror ("Error opening file");
    else {
        if ( fgets (mystring , 100 , pFile) != NULL ) {
            //puts (mystring);
        } else {
            std::cout << "error read prime numbers 1\n";
            return 0;
        }
        fclose (pFile);
    }

    // remove new line character
    char *pos;
    if ((pos=strchr(mystring, '\n')) != NULL)
        *pos = '\0';

    return 1;
}

//BOOST_AUTO_TEST_CASE(test_2) 
int main (void)
{
    int iter_1 = 5122300;
    int iter = 5561457;

    char mystring [100];
 
    time_t start;
    time_t start_gen;
    time_t finish;
    
    big one = 1;
    big null = 0;
    
    fread_number("prime_1", mystring);
    big p(mystring);
    fread_number("prime_2", mystring);
    big q(mystring);
    
 

    big N = p * q;
    big sqrt_N = 0;
    big sqrt_Nk = 0;
    big k_big = 1;
    int k = 0;
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
    //size_B = exp (0.5 * sqrt (ln(N) * log(ln(N))) );
    size_B = exp (sqrt (ln(N) * log(ln(N))) );
    //DEBUG (2,"size of factor base size_B=%f\n", ln(N));
    //DEBUG (2,"size of factor base size_B=%f\n", log(ln(N)));
    //DEBUG (2,"size of factor base size_B=%f\n", ln(N) * log(ln(N)));
    //DEBUG (2,"size of factor base size_B=%f\n",sqrt(ln(N) * log(ln(N))));
    //DEBUG (2,"size of factor base size_B=%f\n", size_B);
    size_B = pow(size_B , sqrt(2)/4);
    //size_B = pow(size_B , sqrt(2)/4);
    DEBUG (2,"size of factor base size_B=%f\n", size_B);
//return 0;
    // selecting smooth primes 
    std::vector<long long > p_smooth;
    DEBUG (2, "smooth numbers\n");
    //make_smooth_numbers_1(p_smooth, size_B, N);
    for (uint64_t i = 2; (p_smooth.size() < size_B) && (i < prime_size); ++i)
    {
        p_smooth.push_back(prime[i]);
        DEBUG(2, "%llu\n", prime[i]);
    }

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
/*(    ofstream myfile1;
    myfile1.open ("general.txt", ios::app);
    myfile1         << "\tp=" << p 
                    << "\tq=" << q 
                    << "\tN=" << N 
                    << "\tM=" <<  M
                    << "\tsize_B=" << size_B
                    << "\n";
 
   myfile1.close();
*/
    // *** construct our sieve *** //
    std::vector<big_2> X;
    //std::vector<big_2> X_sm;
    std::vector<big_2> Y;
    //std::vector<big_2> Y_sm;
    std::vector<big_2> V;

    // simple sieve 
    std::vector<long> solution_candidates_number;
    std::vector< std::vector<uint64_t> > v_exp;
    std::vector< std::vector<uint64_t> > v_exp_sm;
    //std::vector<int> smooth_num;

    bin_matrix_t m_all(p_smooth.size() + 1);
    bin_matrix_t m(p_smooth.size() + 1);

    long long x_count = 0;
    long long smooth_count = 0;
    long long eucl_count = 0;
    int exit_flag = 0;
    start = clock();
    start_gen = clock();
    for (k = 1; k < 3; ++k)
    {
        k_big = k_big + one;
        sqrt_Nk = squareRoot(N * k_big);


    for (long  j = 0, y_number = -1; j < M/2; j++){
        for (int  d = 0; d < 2; d++){
            big_2 tmp_x;
            if(d == 1 && j == 0)
                continue;
            if(d == 0 )
                tmp_x = sqrt_N -j;
                //X.push_back(sqrt_N - j);
            else
                //X.push_back(sqrt_N + j);
                tmp_x = sqrt_N + j;

            
            y_number++;
            x_count++;
            // DEBUG (2, "%s %d\n", __func__, __LINE__);
            //std::cout <<   "X" << j << " =" << X[y_number] << "\n";
            big_2 tmp_y = tmp_x*tmp_x;
            big_2 tmp_v;
            //std::cout <<   "tmp " << tmp << "\n";
            //std::cout <<   "N " << N << "\n";
            if(tmp_y < N) {
                //std::cout <<   "tmp sign " << tmp << "\n";
                //std::cout <<   "N sign " <<  N << "\n";
                tmp_y = N - tmp_y;
                tmp_y.sign = 1;
                //std::cout <<   "tmp1 " << tmp << "\n";
                //std::cout <<   "N " << N << "\n";
                
                //Y.push_back(tmp);
                
                ////Y.push_back(N-tmp);
            } else
                tmp_y = tmp_y % N;
                //Y.push_back(tmp % N);


#define NEGATIVE_SIGN    0 
#define FIRST_VALUE      1

            //v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));
            std::vector<uint64_t> v_exp_tmp(p_smooth.size() + 1);
            //V.push_back(Y[y_number]);

            if(tmp_y < null )
                v_exp_tmp[NEGATIVE_SIGN] = 1;
            //LOG(3) std:: cout << "|" << v_exp_tmp[NEGATIVE_SIGN] << "|\n";

            //big tmp_y1 ("-28512018742020686899625");
            //tmp_v = prime_factorisation(tmp_y1, p_smooth, v_exp_tmp);
            tmp_v = prime_factorisation(tmp_y, p_smooth, v_exp_tmp);


            //LOG(2) std::cout << "X = " << tmp_x << "\tY = " << tmp_y1 << " tmp_v " << tmp_v << " pers " << (j * 100) / (M/2) << "\n";
            LOG(3) std::cout << "X = " << tmp_x << "\tY = " << tmp_y << " tmp_v " << tmp_v << " pers " << (j * 100) / (M/2) << "\n";

            //return 0;
            //LOG(3) std::cout<< "y="<< tmp_y << "\tx=" << tmp_x << "\tv=" << tmp_v << "\n";
            big_2 one(1);
            big_2 min_one(-1);

            if(tmp_v == min_one || tmp_v == one){

                int null_flag = 1;
                //exit(0); 
                null_flag = zero_vector_mod2_check(v_exp_tmp);

                    DEBUG(3, "%s %d  try to add \n",__func__, __LINE__);
                if (null_flag && tmp_v > 0) { // sign check is extra !!!!
                    continue; // special case need to work
                    big_2 found = 0;
                    std::vector<int64_t> tmp;
                    tmp.push_back(y_number);
                    found = euclid_gcd_big( X, Y, tmp, p, q, N,v_exp, p_smooth);
                    if (! (found == 0)) {
                        exit_flag = 1;
                        break;
                    }
                } else {
                    Y.push_back(tmp_y);
                    X.push_back(tmp_x);
                    v_exp.push_back(v_exp_tmp);
                    smooth_count++;

                    finish = clock();
                    ofstream myfile;
                    LOG(1) std::cout << tmp_x << "\t" << tmp_y  << "\t" << (double)(finish - start) / CLOCKS_PER_SEC << "\n";
                    //myfile.open ("example.txt", ios::app);
                    //myfile << tmp_x << "\t" << tmp_y  << "\t" << (double)(finish - start) / CLOCKS_PER_SEC << "\n";
                    //for (int h = 0; h < v_exp_tmp.size(); h++)
                     //   myfile << v_exp_tmp[h];
                    //myfile << "\n";
                    //myfile.close();
                    start = clock();
                    //smooth_num.push_back(y_number);
                    //DEBUG(3, "%s %d  try to add \n",__func__, __LINE__);


                    if (m_all.add_row(v_exp_tmp) == 1){
                        m.add_row(v_exp_tmp);
                        int exponent_num = (v_exp_tmp.size() - 1);
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
                                    DEBUG (3,"num = %d\t",col);
                                    LOG(3) std::cout << "Y  = " <<  Y[col] << "\n";
                                    XYiters.push_back(col);
                                }
                            }
                            DEBUG (2,"\n");

                            eucl_count++;
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
                                //m_all.delete_row(m_all.filled -1);
                                //m.show();
                                LOG(2) std::cout << "filled =" << m_all.filled <<  "\n";
                                if (m_all.filled > m_all.collumn_size) {
                                    m_all.show();
                                    LOG(2) std::cout << "trunagular size " << m_all.triangular_v.size() << "\n";
                                    for (int j = 0; j < m_all.triangular_v.size(); j++)
                                        LOG(2) std::cout << m_all.triangular_v[j] << "\n";
                                    LOG(2) std::cout << "\n";
                                }
                                m_all.delete_row(m_all.filled - 1 );
                                m.delete_row(m_all.filled - 1 );
                                LOG(2) std::cout << "filled1 =" << m_all.filled <<  "\n";
                                if (m_all.filled > m_all.collumn_size) {
                                    m_all.show();
                                    ERROR("matrix to big aaaaa\n");
                                    exit(0);
                                }
                                //DEBUG (3,"delete matrix raw %d\n",__LINE__ );
                                //m_all.show();
                                //smooth_num.pop_back();
                                Y.pop_back();
                                X.pop_back();
                                v_exp.pop_back();
                                //exit(0);
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
    if (exit_flag)
            break;
 
    }
    if(!exit_flag)
        LOG(0) std::cout << "Fail solution i=" << iter << "\tj=" << iter_1 << " p=" << p << "\tq=" << q << "\n";

                    finish = clock();
    ofstream myfile;
                    myfile.open ("results.txt", ios::app);
    myfile         << "" << exit_flag 
                    << "\t" << p 
                    << "\t" << q 
                    << "\t" << N 
                    << "\t" <<  M
                    << "\t" << size_B
                    << "\t" << x_count 
                    << "\t" << smooth_count 
                    << "\t" << eucl_count 
                    << "\t" << (double)(finish - start_gen) / CLOCKS_PER_SEC 
                    << "\n";

    /*myfile         << "res=" << exit_flag 
                    << "\tp=" << p 
                    << "\tq=" << q 
                    << "\tN=" << N 
                    << "\tM=" <<  M
                    << "\tsize_B=" << size_B
                    << "\tx_count=" << x_count 
                    << "\tsmooth_count=" << smooth_count 
                    << "\teucl_count" << eucl_count 
                    << "\ttime=" << (double)(finish - start_gen) / CLOCKS_PER_SEC 
                    << "\n";
*/ 
                    //for (int h = 0; h < v_exp_tmp.size(); h++)
                     //   myfile << v_exp_tmp[h];
                    //myfile << "\n";
                    myfile.close();
 
    return 0;
}
