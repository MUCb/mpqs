
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

#include <inttypes.h> /* for print UINT64*/

#include "log.h"

//Euclid's Algorithm, Greatest Common Divisor
uint64_t euclid_gcd(const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const std::vector<int64_t>& iterator,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N
                )
{
    if (iterator.size() > 0)
    {
        DEBUG(2, "Euclidean algorithm----\n");

        int32_t sumX = 1;
        int32_t sumY = 1;
        uint64_t sumYY = 1;
        uint64_t sum;

        // need a message 
        for (int j = 0; j <  iterator.size(); ++j)
        {
            DEBUG(2, "X %lu\tY %ld\n", X[iterator[j]], Y[iterator[j]]);
            sumX *= X[iterator[j]];
            sumYY *= Y[iterator[j]];
        }

        // take square root from YY
        if (sumYY > 1)
        {
            sumY = sqrt(sumYY);
            if(sumY != trunc(sumY)) 
            {
                ERROR(" %"PRIu64" is not a square", sumYY);
                return 0;
            }
            DEBUG(2, "sqrt Y %"PRIu32"\n", sumY);
        }
        
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
                tmp1 = abs(sumY - sumX);
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
        WARN (1, "no solution ")
        return 0;

    } else {
        ERROR ("bad iterator size")
        return 0;
    }
}