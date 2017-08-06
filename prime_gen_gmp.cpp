#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
#include <gmpxx.h>

// #define PRIMES_SIZE 999999

int main (){
	// const unsigned int sumX = 999999;
	// mpz_t primes[sumX];
	mpz_t prime;
	// mpz_class A[sumX];
	// primes = (mpz_t *) malloc(sizeof(mpz_t) * PRIMES_SIZE);

	mpz_t m;
	mpz_t m1;
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
	// mpz_set_str (m,  "999999999999999999999999999999", 10);
	mpz_set_str (m,  "1000000000000000000000000000038", 10);
	mpz_set_str (m1, "1000000000000000000000000000100", 10);
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
	
	printf("%s %d\n", __func__, __LINE__);

	mpz_t i_sqrt;
	mpz_init(i_sqrt);
	// mpz_sqrt(i_sqrt, i);
	// mpz_add_ui(i_sqrt, i_sqrt, 1);
	

	for ( m; mpz_cmp(m,m1) < 0; mpz_add_ui(m, m, 1)){
		bool not_prime = false;
		bool finish = false;

		gmp_printf ("checking %Zd,\n",m);
		mpz_sqrt(i_sqrt, m);
		mpz_add_ui(i_sqrt, i_sqrt, 1);


		mpz_set_ui(i,2);
		if(mpz_divisible_p(m, i) != 0){
			// gmp_printf ("prime %Zd,\n",m);
			continue;
		}

		for (mpz_set_ui(i,3) ; mpz_cmp(i,i_sqrt) < 0; mpz_add_ui(i, i, 2))
		// // // for (mpz_init_set_ui(i, 4); mpz_cmp(i,m) < 0; mpz_add_ui(i, i, 1))
	    {
	    	if(mpz_divisible_p(m, i) != 0){
				// gmp_printf ("not prime ==== %Zd\n",i);
			    not_prime = true;
				break;
			}

	    	if (mpz_cmp(i,i_sqrt) > 0)
	    	{
	    		finish = true;
	    		break;
	    	}
	    }

	    if(not_prime == false){
			gmp_printf ("prime %Zd,\n",m);
			// mpz_set(primes[prime_current], i);
	    	// fseek(fd, 0, SEEK_END);
	    	// break;
			// mpz_out_str(fd, 10, i);
			// prime_current++;
			// fputs("\n", fd);
					// return 0;
		}
	}

 //    	mpz_t i_sqrt;
	// 	mpz_init(i_sqrt);
 //    	mpz_sqrt(i_sqrt, i);
 //    	mpz_add_ui(i_sqrt, i_sqrt, 1);
 //    	bool not_prime = false;
 //    	bool finish = false;

	// 	for (int j = 1; j < exp; ++j)
	// 	{
	// 		char fn[30];
	// 		sprintf(fn, "primes/10x%d.txt", j);
	// 		FILE * fd_t = fopen(fn, "r");
	// 		if(fd_t == NULL) 
	// 		{
	// 	      	perror("Error opening file");
	// 	      	return(-1);
	// 	    }

	// 	    while( fgets (str , 60 , fd_t) != NULL){
	// 	    	mpz_set_str (prime, str, 10);
	// 	    	if(mpz_divisible_p(i, prime) != 0){
	// 					// gmp_printf ("not prime ==== %Zd\n",i);
	// 	    			not_prime = true;
	// 	    			break;
	// 	    	}

	// 	    	if (mpz_cmp(prime,i_sqrt) > 0)
	// 	    	{
	// 	    		finish = true;
	// 	    		break;
	// 	    	}

	// 	    }

	// 		fclose(fd_t);

	// 		if(finish == true)
	// 			break;

	// 	    if(not_prime == true)
	// 	    	break;
	// 	}

	//     if(not_prime == false){
	// 		gmp_printf ("prime %Zd,\n",i);
 //    		// mpz_set(primes[prime_current], i);
	//     	// fseek(fd, 0, SEEK_END);
	//     	// break;
 //    		mpz_out_str(fd, 10, i);
	// 		// prime_current++;
	// 		fputs("\n", fd);
	// 				// return 0;
	// 	}

	// }
	// fclose(fd);

	// free(primes);
}
