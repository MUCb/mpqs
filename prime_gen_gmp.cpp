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
	mpz_init(prime);
	// mpz_init_set_ui(primes[0], 2);
	// mpz_init_set_ui(primes[1], 3);

	char str[60];
	// int prime_current = 2;

	mpz_set_str (m, "999999999999999", 10);

	// gmp_printf ("%Zd,\n",primes[0]);
	// gmp_printf ("%Zd,\n",primes[1]);
	FILE * fd = fopen("primes.txt", "w+");
	if(fd == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }

	fputs("2\n", fd);
	fputs("3\n", fd);
	// return 0;
	mpz_t i;
	for (mpz_init_set_ui(i, 4); mpz_cmp(i,m) < 0; mpz_add_ui(i, i, 1))
	// // // for (mpz_init_set_ui(i, 4); mpz_cmp(i,m) < 0; mpz_add_ui(i, i, 1))
    {
    	// seek(fd, 0, SEEK_END);
    	fseek(fd, 0, SEEK_SET);
		bool not_prime = false;
		mpz_t sqrt;
		mpz_init(sqrt);	
    	mpz_sqrt (sqrt, i);
    	mpz_add_ui(sqrt, sqrt, 1);
    	int j;

		// gmp_printf ("%Zd,\n",i);
    	// for (j = 0; mpz_cmp(primes[j],sqrt) < 0 && j < prime_current; j++)
	    // {
		size_t red_b;
	    	// while( (red_b = mpz_inp_str (prime , fd, 60 )) && red_b != 0){
	    	while( fgets (str , 60 , fd) != NULL){
	    		// printf("%s == \n", str);
				mpz_set_str (prime, str, 10);
		    	// fseek(fd, red_b, SEEK_SET);
		   		if(mpz_divisible_p(i, prime) != 0){
						// gmp_printf ("not prime ==== %Zd\n",i);
		    			not_prime = true;
		    			break;
		    	}

	    	}
		    	if(not_prime == false){
					gmp_printf ("prime %Zd,\n",prime);
		    		// mpz_set(primes[prime_current], i);
			    	fseek(fd, 0, SEEK_END);
			    	// break;
		    		mpz_out_str(fd, 10, i);
					// prime_current++;
					fputs("\n", fd);
					// return 0;
		    	}


		// 		// gmp_printf ("check  %Zd\n",primes[j]);
	 
	 //    	}

	 //    	// if(prime_current >= PRIMES_SIZE)
	 //    	// {
	 //    	// 	printf("ERROR to samll array\n");
	 //    	// 	return 0;
	 //    	// }
    		
    	// }
		// gmp_printf ("swrt %Zd i %Zd\n",sqrt, i);

		
	}
	fclose(fd);

	// free(primes);
}
