#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
#include <gmpxx.h>

// #define PRIMES_SIZE 999999

int main (){
	mpz_t m;
	mpz_t m1;
	mpz_t iter;
	mpz_t iter_2;
	mpz_init(m);
	mpz_init(m1);
	mpz_init(iter);
	mpz_init(iter_2);

    mpf_t f;
    mpf_init (f);
    /*
    mpz_set_str (m,       "1000", 10);
    mpz_set_str (m1,       "1000", 10);
	mpz_set_str (iter,  "200", 10);
*/
    /* 10^14 */
    /*
	mpz_set_str (m,       "7373030", 10);
	mpz_set_str (iter,  "2000", 10);
	mpz_set_str (m,       "1000000", 10);
	mpz_set_str (iter,  "2000", 10);
*/


    /*
	mpz_set_str (m,       "100000000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "100000", 10);
	mpz_set_str (iter,  "2000", 10);
	
*/

    /*
	mpz_set_str (m,       "4779830000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "10000", 10);
	mpz_set_str (iter,  "2000", 10);
	
*/


    /*
	mpz_set_str (m,       "13010000", 10);
	mpz_set_str (iter,  "2000", 10);
	mpz_set_str (iter_2,  "100000", 10);
	
	mpz_set_str (m,       "10010000", 10);
	mpz_set_str (iter,  "2000", 10);
	mpz_set_str (iter_2,  "100000", 10);
	

*/
    /*
	mpz_set_str (m,       "10000", 10);
	mpz_set_str (iter,  "2000", 10);
	//mpz_set_str (iter_2,  "100000", 10);
	
	mpz_set_str (m,       "10000000000", 10);
	mpz_set_str (iter,  "2000", 10);
	mpz_set_str (iter_2,  "100000", 10);
	
*/

    /* 10^16 */
    /*
	mpz_set_str (m,       "100000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "160000000000", 10);
	mpz_set_str (iter,  "2000", 10);


*/
    /*
	mpz_set_str (m,       "1700000000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "1000000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "10300000", 10);
	mpz_set_str (iter,  "2000", 10);


*/
    /* 10^20 */
    /*
	mpz_set_str (m,       "1000000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
    /*
	mpz_set_str (m,       "100000000000", 10);
	mpz_set_str (iter,  "2000", 10);
	mpz_set_str (m,       "100000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
	mpz_set_str (m,       "1000000000000", 10);
	mpz_set_str (iter,  "2000", 10);
    /*
	mpz_set_str (m,       "10000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
    /* 10^18 */

    /*
	mpz_set_str (m,       "373000000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "1635000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
    /*
	mpz_set_str (m,       "10000000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "10000000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/

    /*
	mpz_set_str (m,       "1000000", 10);
	mpz_set_str (iter,  "2000", 10);

	mpz_set_str (m,       "100000000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/

    /* 10^22 */
    /*
	mpz_set_str (m,       "100000000000", 10);
	mpz_set_str (iter,  "2000", 10);
	
    mpz_set_str (m,       "10000000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
     /*
	mpz_set_str (m,       "1000000000000", 10);
	mpz_set_str (iter,  "2000", 10);
	
    mpz_set_str (m,       "1000000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
      /*
	mpz_set_str (m,       "10000000000000", 10);
	mpz_set_str (iter,  "2000", 10);
	
    mpz_set_str (m,       "100000000", 10);
	mpz_set_str (iter,  "2000", 10);

*/
 
    mpf_set_z (f, iter);
            mpz_set(m1, m);
    int count = 0;
    for (int i = 0; i < 2; i++) {
        //mpz_add(m, m, iter_2);
        for (int i = 0; i <  5; i++) {
            count ++;
            mpz_add(m, m, iter);
            //mpz_set(m, m1);
            //mpz_mul_ui(m, m, 13);
            //mpz_mdiv_ui(m, m, 10);
            //if(count > 5) {
            //    mpz_mul_ui(iter,iter, 2);
            //    count = 0;
            //}
            mpz_nextprime(m1,m);
            gmp_printf ("%Zd\n",m1);
        }
    }
	//mpz_set_str (m,  "3563359734431362578", 10);
	//mpz_set_str (m,  "58372837485639274836", 10);
    //mpz_nextprime(m1,m);
	// const unsigned int sumX = 999999;
	//gmp_printf ("prime %Zd,\n",m1);
    return 0;
    /*
	// mpz_t primes[sumX];
	mpz_t prime;
	// mpz_class A[sumX];
	// primes = (mpz_t *) malloc(sizeof(mpz_t) * PRIMES_SIZE);

	mpz_init(prime);
	mpz_init(m1);
	mpz_init(m);
	// mpz_init_set_ui(primes[0], 2);
	// mpz_init_set_ui(primes[1], 3);

	char str[60];
	// int prime_current = 2;

	// printf("%s %d\n", __func__, __LINE__);

	// gmp_printf ("%Zd,\n",primes[0]);
	// gmp_printf ("%Zd,\n",primes[1]);
	char file_name[30];
	int exp = 9;
	// mpz_set_str (m,  "328743894789234987348237432787", 10);
	// mpz_set_str (m1, "328743894789234987348237432987", 10);

	mpz_set_str (m,  "328543", 10);
	mpz_set_str (m1, "328643", 10);
	// mpz_ui_pow_ui(m,10, exp);
	// sprintf(file_name, "primes/10x%d.txt", exp);
	// printf("%s %d\n", __func__, __LINE__);

	// FILE * fd = fopen(file_name, "w+");
	// if(fd == NULL) 
 //   {
 //      perror("Error opening file");
 //      return(-1);
 //   }
	// fputs("2\n", fd);
	// fputs("3\n", fd);
	// return 0;

	mpz_t i;
	mpz_init(i);
	// mpz_set_ui(i, 10);
	
	// printf("%s %d\n", __func__, __LINE__);

	mpz_t i_sqrt;
	mpz_init(i_sqrt);
	// mpz_sqrt(i_sqrt, i);
	// mpz_add_ui(i_sqrt, i_sqrt, 1);
	

	for ( m; mpz_cmp(m,m1) < 0; mpz_add_ui(m, m, 1)){
		bool not_prime = false;
		bool finish = false;

		// gmp_printf ("checking %Zd,\n",m);

		int ret = mpz_probab_prime_p (m, 20);

		if (ret == 2){
			gmp_printf ("prime %Zd,\n",m);
			// continue;
		}
		else if (ret == 1){
			ret = mpz_probab_prime_p (m, 20);
			if (ret == 2){
				gmp_printf ("prime %Zd,\n",m);
				// continue;
			} else if (ret == 1){
				gmp_printf ("don't know %Zd,\n",m);
			} else {
				// gmp_printf ("not prime %Zd,\n",m);
			}
		} else {
			// gmp_printf ("not prime %Zd,\n",m);
		}
	}
	*/	
}
