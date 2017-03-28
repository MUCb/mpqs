#include <vector>
#include <stdint.h>
#include <stdio.h>

#include "dynamic_bin_matrix.h"
#include "greatest_common_divisor.h"
#include "quadratic_sieve_remainder.h"


#define FIRST_VALUE    1


long prime_factorisation(long  Y, std::vector<long> p_smooth, std::vector<uint64_t> &v_exp)
{
    for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                        smooth_iter < p_smooth.size(); 
                        smooth_iter++, exponent_num++)
    {
        long int tmp;
        do{
            tmp = Y % p_smooth[smooth_iter];
            DEBUG (4, "y = %10li\t",Y);
            DEBUG (4, "p_smooth = %li\t",p_smooth[smooth_iter]);
            DEBUG (4, "tmp = %li\n",tmp);
            if(tmp == 0){
                Y = Y / p_smooth[smooth_iter];
                v_exp[exponent_num] += 1; 
            }
        } while (tmp == 0);

        if(Y == -1 || Y == 1)
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

int add_counter_row(bin_matrix_t &m2 ,std::vector<uint64_t> &counter ,int exponent_num)
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
        return exponent_num;
    else
        return -1;
}


int delete_counter_row(bin_matrix_t &m2 ,std::vector<uint64_t> &counter ,int max_exponent_num, int max_i)
{
    DEBUG (3," delete before m2\n");
    m2.show();
    int ret = m2.delete_row( max_i );
    DEBUG (3," delete after m2\n");
    m2.show();
    if(!ret){
        ERROR("delete matrix row");
        return ret;
    }

    DEBUG (3,"%s %d max_exponent_num %d\n", __func__, __LINE__, max_exponent_num);
    DEBUG (3,"%s %d counter size %d\n", __func__, __LINE__, counter.size());
    if (max_exponent_num < counter.size())
    {
        for (int i = max_exponent_num; i < counter.size(); ++i) {
            counter[i]--;
            DEBUG (3,"%d\t", counter[i]);
            
        }
        DEBUG (3,"\n");
        
    }
    else
    {
        ERROR("max_exponent_num too smal\n");
        ret = 0;
    }
    return ret;
}

int make_exp_array(bin_matrix_t m2, std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<long> Y, std::vector<long> &p_smooth, double size_B, uint32_t M,
    std::vector<long> &solution_candidates_number)
{

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

                        // std::vector<int64_t> tmp;
                        // tmp.push_back(solution_candidates_number[i]);
                        // found = euclid_gcd( X, Y, tmp, p, q, N);
                        // if (found)
                        //     break;


                    } else {
                        smooth_num.push_back(y_number);


                        ERROR("filled1 %d\n", m2.filled);
                        if (m2.add_row(v_exp[y_number]) == 1){
                            ERROR("%s %d\n", __func__, __LINE__);
                            m2.show();
                            ERROR("%s %d\n", __func__, __LINE__);
                            // m2.make_upper_triangular();
                            int null_line = m2.make_upper_triangular();
                            if (null_line != -1)
                                return null_line;
                        }
                    }

                    
                    break;
                }
            }
        }
        m2.show();
        return 0; ///DEBUG  ////////////////////////////////////////////////////////////////////

        // for (int y_num = 0; y_num < V.size(); ++y_num)
        // {
        // }

        for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                    smooth_iter < p_smooth.size(); 
                    smooth_iter++, exponent_num++)
        {
            for (int y_num = 0; y_num < V.size(); ++y_num)
            {
                if(V[y_num] == -1 || V[y_num] == 1)
                    continue;

                long int tmp;
                do{
                    tmp = V[y_num] % p_smooth[smooth_iter];
                    DEBUG (4, "v = %10li\t",V[y_num]);
                    DEBUG (4, "p_smooth = %li\t",p_smooth[smooth_iter]);
                    DEBUG (4, "tmp = %li\n",tmp);
                    if(tmp == 0){
                        V[y_num] = V[y_num] / p_smooth[smooth_iter];
                        v_exp[y_num][exponent_num] += 1; 
                    }
                } while (tmp == 0);
            }
            // break;
        }

        // std::vector<int> smooth_num;
        // std::vector<long> solution_candidates_number;
        // std::vector<uint64_t> P11;
        for (int y_num = 0; y_num < V.size(); ++y_num)
        {
            int null_flag = 1;
            // printf("V = %" PRIu64 "\t",V[i]);
            if(V[y_num] == 1 || V[y_num] == -1)
            {
                for (   int exponent_num = 0;
                            exponent_num < v_exp[y_num].size(); 
                            exponent_num++ )
                {
                    DEBUG (3, "%ld\t", v_exp[y_num][exponent_num]);
                    if ((v_exp[y_num][exponent_num] % 2 )!= 0)
                        null_flag = 0;
                }
                DEBUG (3, "%ld\n", Y[y_num]);
                // skip negative value !!!!
                if (null_flag && V[y_num] > 0) {
                    solution_candidates_number.push_back(y_num);
                } else {
                    smooth_num.push_back(y_num);
                }
            }
        }
        DEBUG (3, "\n");


        //######################### removing null exponent #####################
        std::vector<int> deleted;
        for (   int exponent_num = 1;
                exponent_num < v_exp[0].size(); 
                exponent_num++ )
        {
            int null_flag = 1;
            for (int i = 0; i < smooth_num.size(); ++i)
            {
                if ((v_exp[smooth_num[i]][exponent_num] % 2 )!= 0)
                    null_flag = 0;
            }

            if (null_flag)
            {
                // DEBUG (3, "deleted =  %d\n", exponent_num);
                deleted.push_back(exponent_num);
            }
        }

        for (int i = deleted.size() - 1 ; i >= 0 ; --i)
        {
            // DEBUG (3, "deleted[i] %d\n", deleted[i]);
            for (int j = 0; j < smooth_num.size(); ++j)
            {
                // DEBUG (3, "smooth_num[j] %d\n", smooth_num[j]);
                v_exp[smooth_num[j]].erase(v_exp[smooth_num[j]].begin() + deleted[i]);
                // DEBUG (3, "%d\n", __LINE__);
            }
                // DEBUG (3, "%d\n", __LINE__);
            if (deleted[i] > 0)
                p_smooth.erase(p_smooth.begin()+ deleted[i] -1 );
        }
        //######################################################################
        
        for (int i = 0; i < smooth_num.size(); ++i)
        {
            // printf("V = %" PRIu64 "\t",V[i]);
            if(V[smooth_num[i]] == 1 || V[smooth_num[i]] == -1)
            {
                for (   int exponent_num = 0;
                            exponent_num < v_exp[smooth_num[i]].size(); 
                            exponent_num++ )
                {
                    DEBUG (3, "%ld\t", v_exp[smooth_num[i]][exponent_num]);
                    
                }
                DEBUG (3, "%ld\n", Y[smooth_num[i]]);
            }
        }
        DEBUG (3, "\n");


        if (smooth_num.size()  < size_B + 1)
        {
            ERROR( "to small number of smooth numbbers\n");
            return 0; 
        }
    return 1;
}

void construct_xy(std::vector<long> &X, std::vector<long> &Y, uint64_t sqrt_N, uint64_t N, uint32_t M)
{
        for (uint64_t i = M/2; i > 0; i = i - 1)
        {
            X.push_back(sqrt_N - i);
            DEBUG (4, "X%llu =%llu\n",i, sqrt_N - i );
        }

        for (uint64_t i = 0; i <= M/2; ++i)
        {
            X.push_back(sqrt_N + i);
            DEBUG (4, "X%llu =%llu\n",i, sqrt_N + i );
        }
        

        DEBUG (2,"\n");
        // fill in  (Xi)^2 - N 
        for (uint64_t i = 0; i < X.size(); ++i)
        {
        //     DEBUG (2, "X = %llu\t",X[i]);
            long long tmp = X[i]*X[i];
            if(X[i]*X[i] < N)
                Y.push_back(tmp - N);
            else
                Y.push_back(tmp % N);
        //     DEBUG (2, "Y = %li\t",Y[i]);
        //     DEBUG (2, "\n");
        }

}

void make_smooth_numbers(std::vector<long> &p_smooth, double size_B, uint64_t N)
{
    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);

    for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < prime_size); ++i)
    {
        uint64_t tmp = N;
        for (int j = 1; j < (prime[i]-1)/2; ++j)
        {
            tmp = (tmp * N) % prime[i];
        }
        tmp %= prime[i];

        if( tmp == 1)
        {
            p_smooth.push_back(prime[i]);
            DEBUG(2, "%llu\n", prime[i]);
        }
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


int find_solution (bin_matrix_t m2, 
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
    DEBUG(2, "%d added\n", retval);
    if (retval == 0 )
        return -1;

    // for (int i = 0; i < smooth_num_back.size() ; ++i) {
    //  DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num_back[i]);
    // }

    bin_matrix_t m1 = m2;


    int null_line = m1.resolve_matrix();
    // m1.show();
    // return 0;

    WARN(1, "it should be -1 or greater. null =  %d\n", null_line);

    if (null_line > -1)
    {
        // DEBUG(2, "collumn size %d\n", m1.collumn_size);
        for (uint64_t col = 0; col <  m1.collumn_size; ++col)
        {
            DEBUG (2,"matrix[%d][%d] = %ld\n",null_line,col, m1.unit_matrix[null_line][col]);
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
        // found = euclid_gcd( X, Y, P11, p, q, N);
        found = euclid_gcd( X, Y, P11, p, q, N, v_exp,p_smooth );
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
            null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == -1)
                WARN(1, "failed\n");
    }

    return null_line;
}