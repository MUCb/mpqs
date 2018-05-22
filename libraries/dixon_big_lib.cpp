#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <math.h>


#include "big_2.h"
extern long long  prime[];
extern const int prime_size;


//#include "primes_10_8.h"

/*---------------------------------------------------------------*/
long long  dixon_legendre(long long   a, long long  p) {

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


long dixon_make_smooth_numbers(std::vector<long long > &p_smooth, std::vector<long long > &p_smooth_pos, double size_B, const big N)
{
    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);
    p_smooth_pos.push_back(2 -1);
	long count = 1;

    for (long i = 3; i < size_B && (i < prime_size); ++i)
    {
        long long  tmp;
        //tmp  = N;
        big one(1);
        big tmp_p( prime[i]);
    //DEBUG(2, "%s %d prime %d\n", __func__,__LINE__,prime[i]);
        big N_mod;
        N_mod = N % tmp_p;
        long long N_mod_l = N_mod.to_long();
        tmp = N_mod_l;

        if(dixon_legendre(N_mod_l, prime[i]) == 1) 
            //if( tmp == one)
            //if( tmp == 1)
        {
            p_smooth.push_back(prime[i]);
			p_smooth_pos.push_back(i-1);
            //std::cout << "tmp " << tmp << "added " << tmp_p << "\n";
            //DEBUG(2, "%llu pos %d\n", prime[i], i-1);
			count++;
        }
        //std::cout << "N5=" << N << "\n";
    }
	return count; 
}



