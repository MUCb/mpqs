
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

#include <inttypes.h> /* for print UINT64*/

#include "log.h"

//#include <gmp.h>

//Euclid's Algorithm, Greatest Common Divisor
uint64_t euclid_gcd(const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const std::vector<int64_t>& iterator,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long> p_smooth
                )
{
    if (iterator.size() > 0)
    {
        DEBUG(2, "Euclidean algorithm----\n");

        uint64_t sumX = 1;
        uint64_t sumY = 1;
        // uint64_t sumYY = 1;
        uint64_t sum;

        // need a message 
        std::vector<uint64_t> tmp_v (v_exp[0].size());
        for (int j = 0; j <  iterator.size(); ++j)
        {
            for (int i = 0; i < tmp_v.size(); ++i)
            {
                tmp_v[i] = tmp_v[i] + v_exp[iterator[j]][i];
            }

            DEBUG(2, "X %lu\tY %ld\n", X[iterator[j]], Y[iterator[j]]); 
            sumX *= X[iterator[j]]; // do we need mod N ?????????????????????????????????????????????????
            // sumYY *= Y[iterator[j]];

            sumX %= N; 
            // sumYY %= N;
            // if(sumYY < 0 )
            //     sumYY += N;
        }

        // in this way we can lost additional exp
        // sumY = 1;
        int iter_exp = 1;
        for (int j = 0; j <  p_smooth.size(); ++j,  ++iter_exp)
        {
            DEBUG(2, " %lu |%lu|\t", tmp_v[iter_exp], p_smooth[j]); 
            tmp_v[iter_exp] /= 2;
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            for (int i = 0; i < tmp_v[iter_exp]; ++i)
            {
                sumY *= p_smooth[j];
                sumY %= N; 
                // DEBUG(2, "sumY mod  %lu \n", sumY); 
            }
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            // DEBUG(2, "sumY %lu \n", sumY); 
            // sumY %= N; 
            // DEBUG(2, "sumY mod  %lu \n", sumY); 
        }
        DEBUG(2, " \n"); 
        // DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
        DEBUG(2, "sqrt Y mod n %lu\n", sumY);
        DEBUG(2, "sqrt X mod n %lu\n", sumX);
        if(sumX == sumY)
        {
            WARN (1, "Fail solution\n")
            return 0;
        }




        // // take square root from YY
        // if (sumYY > 1)
        // {
        //     sumY = sqrt(sumYY);
        //     if(sumY != trunc(sumY)) 
        //     {
        //         ERROR(" %" PRIu64 " is not a square", sumYY);
        //         return 0;
        //     }
        //     DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
        // }
        
        // make two attempts to find a solution 
        // y + x and y - x 
        for (int j = 0; j < 2; ++j)
        {
            int64_t tmp1;
            if (j == 0){ 
                tmp1 = sumY + sumX;
                DEBUG (3, "firtst attept Y + X = %ld\n", tmp1);
            }
            else{
                //tmp1 = abs(sumY - sumX);
                tmp1 = sumY - sumX;
		if (tmp1 < 0)
			tmp1 *= -1;
        
                DEBUG (3, "second attept Y - X = %ld\n", tmp1);
            }
            uint64_t tmp2 = N;
            uint64_t tmp3 = 0;

            DEBUG (2, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            while (tmp1 && tmp2)
            {
                tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
                DEBUG (3, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            }

            if (tmp1 > 1 ){
                DEBUG(2, "solution candidate %ld\n", tmp1);
                if (tmp1 == p || tmp1 == q){
                    DEBUG(1, "find p = %ld\n", tmp1);
                    return tmp1;
                }
            } else if (tmp2 > 1 ) {
                DEBUG(2, "solution candidate %ld\n", tmp2);
                if (tmp2 == p || tmp2 == q){
                    DEBUG(1, "find p = %ld\n", tmp2);
                    return tmp2;
                }
            }
        }
        WARN (1, "no solution\n")
        return 0;

    } else {
        ERROR ("bad iterator size")
        return 0;
    }
}

/*

// uint64_t max value  10^19
// since we need to (x*x mod n ) *x mod N 
// x*x  is unlimited 
// restrixt is N < 10^19
// p max 10^8
//Euclid's Algorithm, Greatest Common Divisor
// we get y by multiplying exponents values.
uint64_t euclid_gcd_m_big(const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const std::vector<int64_t>& iterator,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long> p_smooth,
                    std::vector<uint64_t> v_extra_exp
                )
{
    if (iterator.size() > 0)
    {
        DEBUG(2, "Euclidean algorithm----\n");

        uint64_t sumX = 1;
        mpz_t sumX_mp;
        mpz_init_set_si(sumX_mp , 1);
        uint64_t sumY = 1;
        // uint64_t sumYY = 1;
        uint64_t sum;

        // need a message 
        std::vector<uint64_t> tmp_v (v_exp[0].size());
        for (int j = 0; j <  iterator.size(); ++j)
        {
            for (int i = 0; i < tmp_v.size(); ++i)
            {
                tmp_v[i] = tmp_v[i] + v_exp[iterator[j]][i];
                
            }

            DEBUG(2, "X %lu\tY %ld\n", X[iterator[j]], Y[iterator[j]]); 
            // sumX *= X[iterator[j]];
            mpz_mul_si (sumX_mp, sumX_mp, X[iterator[j]]);
            // sumX %= N; 
            mpz_mod_ui(sumX_mp, sumX_mp, N);

            // DEBUG(2, "sumx %ld\n", sumX); 
            // sumYY *= Y[iterator[j]];

            if(v_extra_exp[iterator[j]] > 0)
                sumY *= v_extra_exp[iterator[j]];

            // sumYY %= N;
            // if(sumYY < 0 )
            //     sumYY += N;
        }
         sumX = mpz_get_si(sumX_mp);

        // in this way we can lost additional exp
        // sumY = 1;
        DEBUG(2, "sumY %lu \n", sumY); 
        int iter_exp = 1;
        for (int j = 0; j <  p_smooth.size(); ++j,  ++iter_exp)
        {
            DEBUG(2, " %lu |%lu|\t", tmp_v[iter_exp], p_smooth[j]); 
            tmp_v[iter_exp] /= 2;
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            for (int i = 0; i < tmp_v[iter_exp]; ++i)
            {
                sumY *= p_smooth[j];
                sumY %= N; 
            }
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            // DEBUG(2, "sumY %lu \n", sumY); 
            // sumY %= N; 
            // DEBUG(2, "sumY mod  %lu \n", sumY); 
        }
        DEBUG(2, " \n"); 
        // DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
        DEBUG(2, "sqrt Y mod n %lu\n", sumY);
        DEBUG(2, "sqrt X mod n %lu\n", sumX);
        if(sumX == sumY)
        {
            WARN (1, "Fail solution\n")
            return 0;
        }



        // take square root from YY
        // if (sumYY > 1)
        // {
        //     sumY = sqrt(sumYY);
        //     if(sumY != trunc(sumY)) 
        //     {
        //         ERROR(" %" PRIu64 " is not a square", sumYY);
        //         return 0;
        //     }
        //     DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
        // }
        
        // make two attempts to find a solution 
        // y + x and y - x 
        for (int j = 0; j < 2; ++j)
        {
            uint64_t tmp1;
            if (j == 0){ 
                tmp1 = sumY + sumX;
                DEBUG (3, "firtst attept Y + X = %lu\n", tmp1);
            }
            else{
//                tmp1 = abs(sumY - sumX);
                tmp1 = sumY - sumX;
		if (tmp1 < 0)
			tmp1 *= -1;

                DEBUG (3, "second attept Y - X = %lu\n", tmp1);
            }
            uint64_t tmp2 = N;
            uint64_t tmp3 = 0;

            DEBUG (2, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            while (tmp1 && tmp2)
            {
                tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
                DEBUG (3, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            }

            if (tmp1 > 1 ){
                DEBUG(2, "solution candidate %ld\n", tmp1);
                if (tmp1 == p || tmp1 == q){
                    DEBUG(1, "find p = %ld\n", tmp1);
                    return tmp1;
                }
            } else if (tmp2 > 1 ) {
                DEBUG(2, "solution candidate %ld\n", tmp2);
                if (tmp2 == p || tmp2 == q){
                    DEBUG(1, "find p = %ld\n", tmp2);
                    return tmp2;
                }
            }
        }
        WARN (1, "no solution\n")
        return 0;

    } else {
        ERROR ("bad iterator size")
        return 0;
    }
}
*/



// uint64_t max value  10^19
// since we need to (x*x mod n ) *x mod N 
// max value of p and q should be 6 , because 6 + 6+ 6 = 18 < 10^19
//  N max 10^12
// p max 10^6
//Euclid's Algorithm, Greatest Common Divisor
// we get y by multiplying exponents values.
uint64_t euclid_gcd_m(const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const std::vector<int64_t>& iterator,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long> p_smooth,
                    std::vector<uint64_t> v_extra_exp
                )
{
    if (iterator.size() > 0)
    {
        DEBUG(2, "Euclidean algorithm----\n");

        uint64_t sumX = 1;
        uint64_t sumY = 1;
        // uint64_t sumYY = 1;
        uint64_t sum;

        // need a message 
        std::vector<uint64_t> tmp_v (v_exp[0].size());
        for (int j = 0; j <  iterator.size(); ++j)
        {
            for (int i = 0; i < tmp_v.size(); ++i)
            {
                tmp_v[i] = tmp_v[i] + v_exp[iterator[j]][i];
                
            }

            DEBUG(2, "X %lu\tY %ld\n", X[iterator[j]], Y[iterator[j]]); 
            sumX *= X[iterator[j]];
            sumX %= N; 
            // DEBUG(2, "sumx %ld\n", sumX); 
            // sumYY *= Y[iterator[j]];

            if(v_extra_exp[iterator[j]] > 0)
                sumY *= v_extra_exp[iterator[j]];

            // sumYY %= N;
            // if(sumYY < 0 )
            //     sumYY += N;
        }

        // in this way we can lost additional exp
        // sumY = 1;
        DEBUG(2, "sumY %lu \n", sumY); 
        int iter_exp = 1;
        for (int j = 0; j <  p_smooth.size(); ++j,  ++iter_exp)
        {
            DEBUG(2, " %lu |%lu|\t", tmp_v[iter_exp], p_smooth[j]); 
            tmp_v[iter_exp] /= 2;
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            for (int i = 0; i < tmp_v[iter_exp]; ++i)
            {
                sumY *= p_smooth[j];
                sumY %= N; 
            }
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            // DEBUG(2, "sumY %lu \n", sumY); 
            // sumY %= N; 
            // DEBUG(2, "sumY mod  %lu \n", sumY); 
        }
        DEBUG(2, " \n"); 
        // DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
        DEBUG(2, "sqrt Y mod n %lu\n", sumY);
        DEBUG(2, "sqrt X mod n %lu\n", sumX);
        if(sumX == sumY)
        {
            WARN (1, "Fail solution\n")
            return 0;
        }



        // take square root from YY
        // if (sumYY > 1)
        // {
        //     sumY = sqrt(sumYY);
        //     if(sumY != trunc(sumY)) 
        //     {
        //         ERROR(" %" PRIu64 " is not a square", sumYY);
        //         return 0;
        //     }
        //     DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
        // }
        
        // make two attempts to find a solution 
        // y + x and y - x 
        for (int j = 0; j < 2; ++j)
        {
            int64_t tmp1;
            if (j == 0){ 
                tmp1 = sumY + sumX;
                DEBUG (3, "firtst attept Y + X = %ld\n", tmp1);
            }
            else{
                //tmp1 = abs(sumY - sumX);
                tmp1 = sumY - sumX;
		if (tmp1 < 0)
			tmp1 *= -1;
                DEBUG (3, "second attept Y - X = %ld\n", tmp1);
            }
            uint64_t tmp2 = N;
            uint64_t tmp3 = 0;

            DEBUG (2, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            while (tmp1 && tmp2)
            {
                tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
                DEBUG (3, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            }

            if (tmp1 > 1 ){
                DEBUG(2, "solution candidate %ld\n", tmp1);
                if (tmp1 == p || tmp1 == q){
                    DEBUG(1, "find p = %ld\n", tmp1);
                    return tmp1;
                }
            } else if (tmp2 > 1 ) {
                DEBUG(2, "solution candidate %ld\n", tmp2);
                if (tmp2 == p || tmp2 == q){
                    DEBUG(1, "find p = %ld\n", tmp2);
                    return tmp2;
                }
            }
        }
        WARN (1, "no solution\n")
        return 0;

    } else {
        ERROR ("bad iterator size")
        return 0;
    }
}
