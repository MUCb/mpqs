#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "bin_matrix.h"
#include "big_2.h"
#include "greatest_common_divisor_big.h"
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

int make_exp_array(std::vector< std::vector<uint64_t> > &v_exp, std::vector<int> &smooth_num, std::vector<big_2> Y, std::vector<long long> &p_smooth, double size_B, long long  M,
    std::vector<long long > &solution_candidates_number)
{

        std::vector<big_2> V;
        V = Y;
	big_2 null = 0;
        // add sign to exponent matrix
        #define NEGATIVE_SIGN    0 
        #define FIRST_VALUE    1
        // v_exp[i].size()-1
        big_2 one(1);
        big_2 min_one(-1);


        for (int y_number = 0; y_number < v_exp.size(); ++y_number)
        {
            if(V[y_number] < null )
                v_exp[y_number][NEGATIVE_SIGN] = 1;
    
            V[y_number] = prime_factorisation(Y[y_number], p_smooth, v_exp[y_number]);

            if(V[y_number] == min_one || V[y_number] == one){

                 int null_flag = 1;
                 null_flag = zero_vector_mod2_check(v_exp[y_number]);

                 if (null_flag && V[y_number] > 0) {
                 	solution_candidates_number.push_back(y_number);
                 } else {
                        smooth_num.push_back(y_number);
                 }

            }

        }

        if (smooth_num.size()  < size_B + 1)
        {
            //ERROR( "to small number of smooth numbbers\n");
            return 0; 
        }
    return 1;
}

void construct_xy(std::vector<big_2> &X, std::vector<big_2> &Y, big_2 sqrt_N, big_2 N, long long  M)
{
	long y_number = 0;
	for (long  j = 0 ; j < M/2; j++){
		for (int  d = 0; d < 2; d++){
			if(d == 1 && j == 0)
				continue;
			if(d == 0 )
				X.push_back(sqrt_N - j);
			else
				X.push_back(sqrt_N + j);

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
			y_number++;
			//exit(0);
		}
	}
}


// uint64_t max value  10^19
//  N max 10^9
// p max 10^4
void make_smooth_numbers(std::vector<big> &p_smooth, double size_B, const big N)
{
    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);
    DEBUG(2, "%llu\n", prime[2]);

    for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < prime_size); ++i)
    {
        long long  tmp;
        //tmp  = N;
        big one(1);
	big tmp_p( prime[i]);
	//std::cout << "N=" << N << " % ";
	//std::cout << "N=" << N << "\n";
	//std::cout << tmp_p << "\n";
       big N_mod;
       N_mod = N % tmp_p;
        long long N_mod_l = N_mod.to_long();
       //tmp.number[0] = 0;
	//std::cout << "N1=" << N << "\n";
	//std::cout << "=" << N_mod << "\n";
        tmp = N_mod_l;
	//std::cout << "tmp1=" << tmp << "\n";
        for (int j = 1; j < (prime[i]-1)/2; ++j)
        {
        tmp = tmp * N_mod_l;
        //std::cout << "tmp1= " << tmp << "\t";
        //std::cout << "N23=" << N << "\n";
        //std::cout << "N32=" << N.number[0] << "\n";
        //tmp = tmp % tmp_p;
        tmp = tmp % prime[i];
        //std::cout << "tmp2= " << tmp << "\n";
 
	//std::cout << "N2=" << N << "\n";
            //tmp = tmp * N_mod;
	//std::cout << "N23=" << N << "\n";
	//std::cout << "N32=" << N.number[0] << "\n";
            //tmp = tmp % tmp_p;
            //tmp % tmp_p;
            //tmp = (tmp * N_mod) % tmp_p;
	//std::cout << "N3=" << N << "\n";
	//std::cout << "tmp=" << tmp << "\n";
        }
	//std::cout << "N7=" << N << "\n";
        //exit(0);
       // tmp = tmp % tmp_p;

	//std::cout << "N4=" << N << "\n";
        //if( tmp == one)
        if( tmp == 1)
        {
            p_smooth.push_back(tmp_p);
            //std::cout << "tmp " << tmp << "added " << tmp_p << "\n";
            DEBUG(2, "%llu\n", prime[i]);
        }
	//std::cout << "N5=" << N << "\n";
    }
}

void make_smooth_numbers_1(std::vector<long long > &p_smooth, double size_B, const big N)
{
    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);
    DEBUG(2, "%llu\n", prime[2]);

    for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < prime_size); ++i)
    {
        long long  tmp;
        //tmp  = N;
        big one(1);
        big tmp_p( prime[i]);
        big N_mod;
        N_mod = N % tmp_p;
        long long N_mod_l = N_mod.to_long();
        tmp = N_mod_l;

        if(mp_legendre_1(N_mod_l, prime[i]) == 1) 
            //if( tmp == one)
            //if( tmp == 1)
        {
            p_smooth.push_back(prime[i]);
            //std::cout << "tmp " << tmp << "added " << tmp_p << "\n";
            DEBUG(2, "%llu\n", prime[i]);
        }
        //std::cout << "N5=" << N << "\n";
    }
}


/*---------------------------------------------------------------*/
long long  mp_legendre_1(long long   a, long long  p) {

    long long  x, y, tmp;
    long long  out = 1;

    x = a;
    y = p;
    while (x) {
        while ((x & 1) == 0) {
            x = x / 2;
            if ( (y & 7) == 3 || (y & 7) == 5 )
                out = -out;
        }

        tmp = x;
        x = y;
        y = tmp;

        if ( (x & 3) == 3 && (y & 3) == 3 )
            out = -out;

        x = x % y;
    }
    if (y == 1)
        return out;
    return 0;
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

big prime_factorisation(big Y, std::vector<long long> p_smooth, std::vector<uint64_t> &v_exp)
{
	big null(0);
	big one(1);
	big min_one(-1);
    for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                        smooth_iter < p_smooth.size(); 
                        smooth_iter++, exponent_num++)
    {
        big tmp;
        long long  reminder;
        do{
            big quotient;

           
            div_rem_l(Y, p_smooth[smooth_iter], quotient, reminder);
            //tmp = Y % p_smooth[smooth_iter];
            //DEBUG (4, "y = %10li\t",Y);
            //std::cout << "y = " << Y << "\ttmp = " << tmp << "\tp_smooth " <<  p_smooth[smooth_iter] << " \n";
            //DEBUG (4, "p_smooth = %li\t",p_smooth[smooth_iter]);
            //DEBUG (4, "tmp = %li\n",tmp);
            //std::cout << "tmp size " << (int)tmp.size << "\n";
            //std::cout << "null size " <<(int) null.size << "\n";
            if(reminder == 0){
                //Y = Y / p_smooth[smooth_iter];
                Y = quotient;
                LOG(3) std::cout << "1y = " << Y << "\ttmp = " << tmp << "\tp_smooth " <<  p_smooth[smooth_iter] << " \n";
                LOG(3) std::cout << "expon num " << exponent_num <<" \n";
                //std::cout<< "Y = " << Y << "\n"; 
                v_exp[exponent_num] += 1; 
            }
        } while (reminder == 0);

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
        DEBUG (4, "%ld\t", v_exp[exponent_num]);
        v_exp[exponent_num] %= 2;
        if (v_exp[exponent_num] != 0)
            null_flag = 0;
    }
    DEBUG (4, "\n");
    return null_flag;
}

int find_solution_big (bin_matrix_t & m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    std::vector<long long> p_smooth,
                    const std::vector<big_2>& X,
                    const std::vector<big_2>& Y,
                    const big_2 &p,
                    const big_2 &q,
                    const big_2 &N)
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
    //WARN(1, "it should be -1 or greater. null =  %d\n", null_line);

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

        big_2 found = 0;
        found = euclid_gcd_big( X, Y, P11, p, q, N, v_exp, p_smooth);
        // printf("found %lu\n", found);
        m1.show();
        if (! (found == 0)) {
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
            null_line = find_solution_big(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N);
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
            null_line = find_solution_big(m2, smooth_num_back, smooth_num, v_exp, p_smooth, X, Y, p, q, N);
            // DEBUG(3, "finish %d\n", null_line);
            if (null_line == -1)
                WARN(1, "failed\n");
    }
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
