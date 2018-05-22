
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

#include <inttypes.h> /* for print UINT64*/

#include "log.h"
//#include "primes.h"

 extern long long  prime[];
#include "big_2.h" 

//Euclid's Algorithm, Greatest Common Divisor
big_2 dixon_euclid_gcd_big(const std::vector<big_2>& X,
                    const std::vector<big_2>& Y,
                    const std::vector<int64_t>& iterator,
                    const big_2 &p,
                    const big_2 &q,
                    const big_2 &N,
                    std::vector< std::vector<uint64_t> > v_exp,
                    std::vector<long long> p_smooth,
					double size_B
                )
{
    if (iterator.size() > 0)
    {
        DEBUG(2, "Euclidean algorithm----\n");

        big_2 sumX (1);
        big_2 sumY (1);
        // uint64_t sumYY = 1;
        uint64_t sum;

        // need a message 
        std::vector<uint64_t> tmp_v (v_exp[0].size());
        for (int j = 0; j <  iterator.size(); ++j)
        {
            for (int i = 0; i < tmp_v.size(); ++i)
            {
		    LOG (4) std::cout << v_exp[iterator[j]][i] ; 
                tmp_v[i] = tmp_v[i] + v_exp[iterator[j]][i];
	    //LOG (3) std::cout << "tmp_v " << tmp_v[i]<<  "\n"; 
            }
		    LOG (4) std::cout << "\n"; 
	    LOG (3) std::cout << "X " << X[iterator[j]] << "\tY " << Y[iterator[j]] << "\n"; 
            sumX = sumX * X[iterator[j]]; // do we need mod N ?????????????????????????????????????????????????
            //std::cout << "X iter " << X[iterator[j]] << "\n";
            //std::cout << "sum X before" << sumX << "\n";
            // sumYY *= Y[iterator[j]];

            sumX = sumX % N; 
            LOG (3) std::cout << "sum X " << sumX << "\n";
            // sumYY %= N;
            // if(sumYY < 0 )
            //     sumYY += N;
        }

        // in this way we can lost additional exp
        // sumY = 1;
	    //LOG (2) std::cout << "func  " << __func__ << "\tline " << __LINE__ << "\n"; 
        int iter_exp = 1;
        for (int j = 0; j <  size_B-1; ++j,  ++iter_exp)
        {
            //DEBUG(2, " %lu |%lu|\t", tmp_v[iter_exp], p_smooth[j]); 
		LOG (4) std::cout << " " << tmp_v[iter_exp] << "|" << prime[j+2] << "|\t"; 
            tmp_v[iter_exp] /= 2;
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            for (int i = 0; i < tmp_v[iter_exp]; ++i)
            {
                //std::cout << "iter i " << i  << "\n";
                //std::cout << "sum y before" << sumY << "\n";
                sumY = sumY * prime[j+2];
                //LOG (4) std::cout << "prime " << prime[j+2] << "\n";
                sumY = sumY % N; 
                LOG (4) std::cout << "sum y " << sumY << "\n";
                // DEBUG(2, "sumY mod  %lu \n", sumY); 
            }
            // sumY *= (pow (p_smooth[j], tmp_v[iter_exp])) % N;
            // DEBUG(2, "sumY %lu \n", sumY); 
            // sumY %= N; 
            // DEBUG(2, "sumY mod  %lu \n", sumY); 
        }
	LOG (4) std::cout <<  " \n"; 
	    //LOG (2) std::cout << "func  " << __func__ << "\tline " << __LINE__ << "\n"; 
        // DEBUG(2, "sqrt Y %" PRIu32 "\n", sumY);
                LOG (4) std::cout << "sqrt Y mod n " << sumY << "\n";
                LOG (4) std::cout << "sqrt X mod n " << sumX << "\n";
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
            big_2 tmp1;
            if (j == 0){ 
                tmp1 = sumY + sumX;
		LOG (3) std::cout <<  "firtst attept Y + X = " << tmp1 << "\n";
            }
            else{
		if (sumY < sumX)
			tmp1 = sumX - sumY;
		else
			tmp1 = sumY - sumX;// Fixme
                //tmp1 = abs(sumY - sumX);
                //DEBUG (3, "second attept Y - X = %ld\n", tmp1);
		LOG(3) std::cout <<  "second attept Y - X = " << tmp1 << "\n";
            }
            big_2 tmp2 = N;
            big_2 tmp3 = 0;

		LOG(3) std::cout <<  "tmp1 ="<<  tmp1 << "\ttmp2="<< tmp2 << "\n";
            while (!(tmp1 == 0) && !(tmp2 == 0))// FIXME
            {
                tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
		LOG(3) std::cout <<  "tmp1 ="<<  tmp1 << "\ttmp2="<< tmp2 << "\n";
            }

            if (tmp1 > 1 ){
		LOG(3) std::cout << "solution candidate " << tmp1 << "\n";
                if (tmp1 == p || tmp1 == q){
                    //DEBUG(1, "find p = %ld\n", tmp1);
                    return tmp1;
                }
            } else if (tmp2 > 1 ) {
		LOG(3) std::cout << "solution candidate " << tmp2 << "\n";
                //DEBUG(2, "solution candidate %ld\n", tmp2);
                if (tmp2 == p || tmp2 == q){
                    //DEBUG(1, "find p = %ld\n", tmp2);
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

