#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "bin_matrix.h"
#include "big_2.h"
#include "greatest_common_divisor.h"
#include "quadratic_sieve_big.h"



int make_exp_array_condBsmooth(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> Y, std::vector<long> &p_smooth, double size_B, uint32_t M,
    std::vector<long> &solution_candidates_number, std::vector<uint64_t> &v_extra_exp)
{

        std::vector<long> V;
        V = Y;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        #define FIRST_VALUE    1
        // v_exp[i].size()-1

        int print_flag = 1;
        for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        {

            if(V[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                    smooth_iter < p_smooth.size(); 
                    smooth_iter++, exponent_num++)
            {
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
                    int null_flag = 1;
                    // printf("V = %" PRIu64 "\t",V[i]);
                    for (   int exp_num = 0;
                                exp_num < v_exp[y_number].size(); 
                                exp_num++ )
                    {
                        DEBUG (3, "%ld\t", v_exp[y_number][exp_num]);
                        if ((v_exp[y_number][exp_num] % 2 )!= 0)
                            null_flag = 0;
                    }
                    DEBUG (3, "%ld\n", Y[y_number]);
                    // skip negative value !!!!
                    if (null_flag && V[y_number] > 0) {
                        solution_candidates_number.push_back(y_number);
                    } else {
                        smooth_num.push_back(y_number);
                    }
                    DEBUG (3, "\n");

                    break;
                }
            }

            // DEBUG (0, "V ===== %li \n",V[y_number]);
            if(V[y_number] != -1 && V[y_number] != 1){
                int sign_flag = 0;
                if(V[y_number] < 0 ){
                    sign_flag = 1;
                    V[y_number] *= -1;
                }
                
                double res = sqrt(V[y_number]);
                if(res == trunc(res)) {
                    v_extra_exp[y_number] = res;
                    V[y_number] /= V[y_number];
                    if(print_flag){
                        DEBUG (0, "found  ========================================= %f  number %d\n",res, y_number);
                        print_flag = 0;
                    }
                    DEBUG (2, "Y = %li\tV = %li\n",Y[y_number], V[y_number]);
                    // DEBUG (0, "iter %d\n",);

                    int null_flag = 1;
                    // printf("V = %" PRIu64 "\t",V[i]);
                    for (   int exp_num = 0;
                                exp_num < v_exp[y_number].size(); 
                                exp_num++ )
                    {
                        DEBUG (3, "%ld\t", v_exp[y_number][exp_num]);
                        if ((v_exp[y_number][exp_num] % 2 )!= 0)
                            null_flag = 0;
                    }
                    DEBUG (3, "\n");

                    if (null_flag && V[y_number] > 0) {
                        solution_candidates_number.push_back(y_number);
                        // DEBUG (2, "sol cand %d\n",solution_candidates_number.size() );
                    } else {
                        smooth_num.push_back(y_number);
                    }
                    // smooth_num.push_back(y_number);
                }
                
                if(sign_flag)
                    V[y_number] *= -1;
            }
                
        }

       if (smooth_num.size()  < size_B + 1)
        {
            //ERROR( "to small number of smooth numbbers\n");
            return 0; 
        }
    return 1;
}

// additional check by mod 8
int make_exp_array_condBsmooth_1(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> Y, std::vector<long> &p_smooth, double size_B, uint32_t M,
    std::vector<long> &solution_candidates_number, std::vector<uint64_t> &v_extra_exp)
{

        std::vector<long> V;
        V = Y;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        #define FIRST_VALUE    1
        // v_exp[i].size()-1

        int print_flag = 1;
        for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        {

            if(V[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                    smooth_iter < p_smooth.size(); 
                    smooth_iter++, exponent_num++)
            {
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
                    int null_flag = 1;
                    // printf("V = %" PRIu64 "\t",V[i]);
                    for (   int exp_num = 0;
                                exp_num < v_exp[y_number].size(); 
                                exp_num++ )
                    {
                        DEBUG (3, "%ld\t", v_exp[y_number][exp_num]);
                        if ((v_exp[y_number][exp_num] % 2 )!= 0)
                            null_flag = 0;
                    }
                    DEBUG (3, "%ld\n", Y[y_number]);
                    // skip negative value !!!!
                    if (null_flag && V[y_number] > 0) {
                        solution_candidates_number.push_back(y_number);
                    } else {
                        smooth_num.push_back(y_number);
                    }
                    DEBUG (3, "\n");

                    break;
                }
            }

            // DEBUG (0, "V ===== %li \n",V[y_number]);
            if(V[y_number] != -1 && V[y_number] != 1){
                int sign_flag = 0;
                if(V[y_number] < 0 ){
                    sign_flag = 1;
                    V[y_number] *= -1;
                }
                
                if (V[y_number] % 8 == 1 )
                {
                    double res = sqrt(V[y_number]);
                    if(res == trunc(res)) {
                        v_extra_exp[y_number] = res;
                        V[y_number] /= V[y_number];
                        if(print_flag){
                            DEBUG (0, "found  ========================================= %f  number %d\n",res, y_number);
                            print_flag = 0;
                        }
                        DEBUG (2, "Y = %li\tV = %li\n",Y[y_number], V[y_number]);
                        // DEBUG (0, "iter %d\n",);

                        int null_flag = 1;
                        // printf("V = %" PRIu64 "\t",V[i]);
                        for (   int exp_num = 0;
                                    exp_num < v_exp[y_number].size(); 
                                    exp_num++ )
                        {
                            DEBUG (3, "%ld\t", v_exp[y_number][exp_num]);
                            if ((v_exp[y_number][exp_num] % 2 )!= 0)
                                null_flag = 0;
                        }
                        DEBUG (3, "\n");

                        if (null_flag && V[y_number] > 0) {
                            solution_candidates_number.push_back(y_number);
                            // DEBUG (2, "sol cand %d\n",solution_candidates_number.size() );
                        } else {
                            smooth_num.push_back(y_number);
                        }
                        // smooth_num.push_back(y_number);
                    }
                }
                
                if(sign_flag)
                    V[y_number] *= -1;
            }
                
        }

       if (smooth_num.size()  < size_B + 1)
        {
            //ERROR( "to small number of smooth numbbers\n");
            return 0; 
        }
    return 1;
}

int make_exp_array(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> Y, std::vector<long> &p_smooth, double size_B, uint32_t M,
    std::vector<long> &solution_candidates_number)
{

        std::vector<long> V;
        V = Y;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        #define FIRST_VALUE    1
        // v_exp[i].size()-1

        for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        {
            if(V[y_number] < 0 )
                v_exp[y_number][NEGATIVE_SIGN] = 1;

            for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                    smooth_iter < p_smooth.size(); 
                    smooth_iter++, exponent_num++)
            {
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
                    int null_flag = 1;
                    // printf("V = %" PRIu64 "\t",V[i]);
                    for (   int exp_num = 0;
                                exp_num < v_exp[y_number].size(); 
                                exp_num++ )
                    {
                        DEBUG (3, "%ld\t", v_exp[y_number][exp_num]);
                        if ((v_exp[y_number][exp_num] % 2 )!= 0)
                            null_flag = 0;
                    }
                    DEBUG (3, "%ld\n", Y[y_number]);
                    // skip negative value !!!!
                    if (null_flag && V[y_number] > 0) {
                        solution_candidates_number.push_back(y_number);
                    } else {
                        smooth_num.push_back(y_number);
                    }
                    DEBUG (3, "\n");

                    break;
                }
            }
        }


        // for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        // {
        //     if(V[y_number] < 0 )
        //         v_exp[y_number][NEGATIVE_SIGN] = 1;
        // }

        // for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
        //             smooth_iter < p_smooth.size(); 
        //             smooth_iter++, exponent_num++)
        // {
        //     for (int y_num = 0; y_num < M; ++y_num)
        //     {
        //         if(V[y_num] == -1 || V[y_num] == 1)
        //             continue;

        //         long int tmp;
        //         do{
        //             tmp = V[y_num] % p_smooth[smooth_iter];
        //             DEBUG (4, "v = %10li\t",V[y_num]);
        //             DEBUG (4, "p_smooth = %li\t",p_smooth[smooth_iter]);
        //             DEBUG (4, "tmp = %li\n",tmp);
        //             if(tmp == 0){
        //                 V[y_num] = V[y_num] / p_smooth[smooth_iter];
        //                 v_exp[y_num][exponent_num] += 1; 
        //             }
        //         } while (tmp == 0);
        //     }
        //     // break;
        // }

        // std::vector<int> smooth_num;
        // std::vector<long> solution_candidates_number;
        // std::vector<uint64_t> P11;
        // for (int y_num = 0; y_num < V.size(); ++y_num)
        // {
        //     int null_flag = 1;
        //     // printf("V = %" PRIu64 "\t",V[i]);
        //     if(V[y_num] == 1 || V[y_num] == -1)
        //     {
        //         for (   int exponent_num = 0;
        //                     exponent_num < v_exp[y_num].size(); 
        //                     exponent_num++ )
        //         {
        //             DEBUG (3, "%ld\t", v_exp[y_num][exponent_num]);
        //             if ((v_exp[y_num][exponent_num] % 2 )!= 0)
        //                 null_flag = 0;
        //         }
        //         DEBUG (3, "%ld\n", Y[y_num]);
        //         // skip negative value !!!!
        //         if (null_flag && V[y_num] > 0) {
        //             solution_candidates_number.push_back(y_num);
        //         } else {
        //             smooth_num.push_back(y_num);
        //         }
        //     }
        // }
        // DEBUG (3, "\n");


        //######################### removing null exponent #####################
        // std::vector<int> deleted;
        // for (   int exponent_num = 1;
        //         exponent_num < v_exp[0].size(); 
        //         exponent_num++ )
        // {
        //     int null_flag = 1;
        //     for (int i = 0; i < smooth_num.size(); ++i)
        //     {
        //         if ((v_exp[smooth_num[i]][exponent_num] % 2 )!= 0)
        //             null_flag = 0;
        //     }

        //     if (null_flag)
        //     {
        //         deleted.push_back(exponent_num);
        //     }
        // }

        // for (int i = deleted.size() - 1 ; i >= 0 ; --i)
        // // for (int i = 0; i < deleted.size(); ++i)
        // {
        //     for (int j = 0; j < smooth_num.size(); ++j)
        //     {
        //         v_exp[smooth_num[j]].erase(v_exp[smooth_num[j]].begin() + deleted[i]);
        //     }
        //     if (deleted[i] > 0)
        //         p_smooth.erase(p_smooth.begin()+ deleted[i] - 1);
        // }
        //######################################################################
        
        if (smooth_num.size()  < size_B + 1)
        {
            //ERROR( "to small number of smooth numbbers\n");
            return 0; 
        }
    return 1;
}

void construct_xy(std::vector<long> &X, std::vector<long> &Y, long sqrt_N, long long N, long M)
{
        // for (long  i = 0; i < M; i++)
        // for (long  i = -M/2; i < M/2; i++)
        for (long  i = -M/2; i < M/2; i++)
        // for (long  i = -M*3/10; i < M*7/10; i++)
        {
            X.push_back(sqrt_N + i);
            DEBUG (4, "X%lu =%lu\n",i, sqrt_N - i );
        }

        // for (uint64_t i = 0; i <= M/2; ++i)
        // {
        //     X.push_back(sqrt_N + i);
        //     DEBUG (4, "X%llu =%llu\n",i, sqrt_N + i );
        // }
        

        DEBUG (2,"\n");
        // fill in  (Xi)^2 - N 
        for (uint64_t i = 0; i < X.size(); ++i)
        {
            DEBUG (2, "X = %lu\t",X[i]);
            long long tmp = X[i]*X[i];
            if(X[i]*X[i] < N)
                Y.push_back(tmp - N);
            else
                Y.push_back(tmp % N);
            DEBUG (2, "Y = %li\t",Y[i]);
            DEBUG (2, "\n");
        }

}


// uint64_t max value  10^19
//  N max 10^9
// p max 10^4
void make_smooth_numbers(std::vector<long long> &p_smooth, double size_B, const big_2 N)
{
    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);
    DEBUG(2, "%llu\n", prime[2]);

    for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < prime_size); ++i)
    {
        big_2 tmp;
        tmp  = N;
        big_2 one(1);
	big_2 tmp_p( prime[i]);
	//std::cout << "N=" << N << " % ";
	//std::cout << "N=" << N << "\n";
	//std::cout << tmp_p << "\t";
       big_2 N_mod;
       N_mod = N % tmp_p;
       //tmp.number[0] = 0;
	//std::cout << "N1=" << N << "\n";
	//std::cout << "=" << N_mod << "\n";
        tmp = N_mod;
	//std::cout << "tmp1=" << tmp << "\n";
        for (int j = 1; j < (prime[i]-1)/2; ++j)
        {
	//std::cout << "N2=" << N << "\n";
            //tmp = tmp * N_mod;
	//std::cout << "N23=" << N << "\n";
	//std::cout << "N32=" << N.number[0] << "\n";
            //tmp = tmp % tmp_p;
            //tmp % tmp_p;
            tmp = (tmp * N_mod) % tmp_p;
	//std::cout << "N3=" << N << "\n";
	//std::cout << "N32=" << N.number[0] << "\n";
        }
	//std::cout << "N7=" << N << "\n";
        //exit(0);
       // tmp = tmp % tmp_p;

	//std::cout << "N4=" << N << "\n";
        if( tmp == one)
        {
            p_smooth.push_back(prime[i]);
            DEBUG(2, "%llu\n", prime[i]);
        }
	//std::cout << "N5=" << N << "\n";
    }
}

int fill_matrix(bin_matrix_t &m1, std::vector<int> &smooth_num, std::vector< std::vector<uint64_t> > &v_exp)
{
    int count = 0;

    // DEBUG(3, "%s %d \n",__func__, __LINE__);
    // DEBUG(3, "%s %d filled \n",__func__, m1.filled);
    // DEBUG(3, "%s %d size \n",__func__, m1.size);
    if ((m1.row_size) == m1.filled)
        return count;

    DEBUG(4, "%s %d \n",__func__, __LINE__);
    for (int i = 0; i < smooth_num.size() && ((m1.row_size) != m1.filled); ++i) {
        // DEBUG(3, "%s %d iteration\n",__func__, i);
        // DEBUG(3, "%s %d filled \n",__func__, m1.filled);
        // DEBUG(3, "%s %d size \n",__func__, m1.size);
        // DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num[i]);
        if (smooth_num[i] != -1) {
            DEBUG(3, "%s %d  try to add %d \n",__func__, __LINE__, smooth_num[i]);
            m1.add_row(v_exp[ smooth_num[i]]);
            smooth_num[i] = -1;
            // DEBUG(3, "%s %d =added\n",__func__, smooth_num[i]);
            count++;
        }
    }
    return count;
}


void add_counter_row(bin_matrix_t &m2 ,std::vector<uint64_t> &counter ,int exponent_num)
{
    std::vector<uint64_t> tmp(counter.size());
    // for (int i = exponent_num; i < v_exp[y_number].size(); ++i)
    for (int i = exponent_num; i < counter.size(); ++i)
    {
        tmp[i] = 1;
        counter[i]++;
    }
    m2.add_row(tmp);
    // ERROR("added num %d\n", exponent_num);
/*
    int count_flag = 0;
    for (exponent_num = 1; exponent_num < counter.size(); ++exponent_num)
    {
        DEBUG(2, "counter[%d]=%lu\t", exponent_num, counter[exponent_num] ); 
        if (counter[exponent_num] == exponent_num + 2)
        {
            DEBUG(2, "flag is set \n"); 
            count_flag = 1;
            break;
        }
    }
        DEBUG(2, "\n"); 
    if (count_flag)
        return exponent_num;
    else
        return -1;*/
}

int is_counter_full(std::vector<uint64_t> &counter)
{
    int count_flag = 0;
    int exponent_num;
    for (exponent_num = 1; exponent_num < counter.size(); ++exponent_num)
    {
        DEBUG(2, "counter[%d]=%lu\t", exponent_num, counter[exponent_num] ); 
        if (counter[exponent_num] == exponent_num + 2)
        {
            DEBUG(2, "flag is set \n"); 
            count_flag = 1;
            break;
        }
    }
        DEBUG(2, "\n"); 
    if (count_flag)
        return exponent_num;
    else
        return -1;

}

big_2 prime_factorisation(big_2 Y, std::vector<long long> p_smooth, std::vector<uint64_t> &v_exp)
{
	big_2 null(0);
	big_2 one(1);
	big_2 min_one(-1);
    for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                        smooth_iter < p_smooth.size(); 
                        smooth_iter++, exponent_num++)
    {
        big_2 tmp;
        do{
            tmp = Y % p_smooth[smooth_iter];
            //DEBUG (4, "y = %10li\t",Y);
            //std::cout << "y = " << Y << "\ttmp = " << tmp << "\tp_smooth" <<  p_smooth[smooth_iter] << " \n";
            //DEBUG (4, "p_smooth = %li\t",p_smooth[smooth_iter]);
            //DEBUG (4, "tmp = %li\n",tmp);
            //std::cout << "tmp size " << (int)tmp.size << "\n";
            //std::cout << "null size " <<(int) null.size << "\n";
            if(tmp == null){
                Y = Y / p_smooth[smooth_iter];
                //std::cout<< "Y = " << Y << "\n"; 
                v_exp[exponent_num] += 1; 
            }
        } while (tmp == null);

        if(Y == one || Y == min_one)
            break;
    }
    return Y;
}

int zero_vector_mod2_check(std::vector<uint64_t> v_exp) {
    // modulo-2 division 
    int null_flag = 1;
    for (   int exponent_num = 0;
                exponent_num < v_exp.size(); 
                exponent_num++ )
    {
        DEBUG (3, "%ld\t", v_exp[exponent_num]);
        v_exp[exponent_num] %= 2;
        if (v_exp[exponent_num] != 0)
            null_flag = 0;
    }
    return null_flag;
}

int find_solution (bin_matrix_t & m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    std::vector<long> p_smooth,
                    const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N)
{

    std::vector<int64_t> P11;
    int retval = fill_matrix(m2, smooth_num_back, v_exp);
    m2.show();
    DEBUG(2, "%d 1added\n", retval);
    if (retval == 0 || m2.filled != m2.row_size)
        return -1;

    // if()

    // for (int i = 0; i < smooth_num_back.size() ; ++i) {
    //  DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num_back[i]);
    // }

    bin_matrix_t m1 = m2;
    // m2.show();
    // DEBUG(1, "----------------");

    int null_line = m1.resolve_matrix();
    // m1.show();
    // return 0;
#if 0
    WARN(1, "it should be -1 or greater. null =  %d\n", null_line);

    if (null_line > -1)
    {
        // DEBUG(2, "collumn size %d\n", m1.collumn_size);
        for (uint64_t col = 0; col <  m1.collumn_size; ++col)
        {
            DEBUG (2,"matrix[%d][%lu] = %lu\n",null_line,col, m1.unit_matrix[null_line][col]);
            if( m1.unit_matrix[null_line][col] > 0)
            {
                DEBUG (2,"num = %d\t", smooth_num[col]);
                // if (i == 0 )
                // {
                    // DEBUG (1,"Strange\n");
                    // continue;
                // } else
                // {
                    DEBUG (2,"Y  = %ld\n", Y[smooth_num[col]]);
                    P11.push_back(smooth_num[col]);
                // }
            }
        }
        DEBUG (2,"\n");

        int found = 0;
        found = euclid_gcd( X, Y, P11, p, q, N, v_exp, p_smooth);
        // printf("found %lu\n", found);
        m1.show();
        if (found) {
            return null_line;
        }
        else {

            int max_i = 0;
            max_i = m2.max_unit_num(m1.unit_matrix[null_line]);

            DEBUG (3," iter %d\n",max_i );
            m2.show();
            m2.delete_row(max_i);
            DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N);
            // DEBUG(3, "finish %d\n", null_line);
            if (null_line == -1)
                WARN(1, "failed\n");

        }
    } else {
            int max_i = 0;
            m2.show();
            m2.delete_row(max_i);
            DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N);
            // DEBUG(3, "finish %d\n", null_line);
            if (null_line == -1)
                WARN(1, "failed\n");
    }
#endif
    return null_line;
}




#if 0
int find_solution_condBsmooth (bin_matrix_t m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    std::vector<long> p_smooth,
                    const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N,
                    std::vector<uint64_t> &v_extra_exp)
{

    std::vector<int64_t> P11;
    int retval = fill_matrix(m2, smooth_num_back, v_exp);
    m2.show();
    DEBUG(2, "%d 1added\n", retval);
    if (retval == 0 || m2.filled != m2.row_size)
        return -1;

    // for (int i = 0; i < smooth_num_back.size() ; ++i) {
    //  DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num_back[i]);
    // }

    bin_matrix_t m1 = m2;

    // DEBUG(1, "--------------------------");
    int null_line = m1.resolve_matrix();
    // m1.show();
    // return 0;

    WARN(1, "it should be -1 or greater. null =  %d\n", null_line);

    if (null_line > -1)
    {
        // DEBUG(2, "collumn size %d\n", m1.collumn_size);
        for (uint64_t col = 0; col <  m1.collumn_size; ++col)
        {
            DEBUG (2,"matrix[%d][%lu] = %ld\n",null_line,col, m1.unit_matrix[null_line][col]);
            if( m1.unit_matrix[null_line][col] > 0)
            {
                DEBUG (2,"num = %d\t", smooth_num[col]);
                // if (i == 0 )
                // {
                    // DEBUG (1,"Strange\n");
                    // continue;
                // } else
                // {
                    DEBUG (2,"Y  = %ld\n", Y[smooth_num[col]]);
                    P11.push_back(smooth_num[col]);
                // }
            }
        }
        DEBUG (2,"\n");

        int found = 0;
        found = euclid_gcd_m_big( X, Y, P11, p, q, N, v_exp, p_smooth, v_extra_exp);
        // printf("found %lu\n", found);
        m1.show();
        if (found) {
            return null_line;
        }
        else {

            int max_i = 0;
            //max_i = m2.max_unit_num(m1.unit_matrix[null_line]); // temp need to return back
            max_i = smooth_num_back.size() -1;

            DEBUG (3," iter %d\n",max_i );
            m2.show();
            m2.delete_row(max_i);
            DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution_condBsmooth(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N, v_extra_exp);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == -1)
                WARN(1, "failed\n");

        }
    } else {
            int max_i = 0;
            m2.show();
            m2.delete_row(max_i);
            DEBUG (4,"===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution_condBsmooth(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N, v_extra_exp);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == -1)
                WARN(1, "failed\n");
    }

    return null_line;
}
#endif
