#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
#include <gmpxx.h>

// #define PRIMES_SIZE 999999

int main (){
	mpz_t p;
	mpz_t p_orig;
	mpz_t q;
	mpz_t q_orig;
	mpz_t N;
	mpz_t iter_p;
	mpz_t iter_q;
	mpz_init(p);
	mpz_init(p_orig);
	mpz_init(q);
	mpz_init(q_orig);
	mpz_init(N);
	mpz_init(iter_p);
	mpz_init(iter_q);

    mpz_t f;
    mpz_t f1;
    mpz_init (f);
    mpz_init (f1);
	//mpz_set_str (m,       "1000000000000", 10);
	mpz_set_str (p,       "323213898970910797", 10);
	mpz_set_str (q,       "430874390872398017", 10);
	mpz_set_str (iter_p,  "20000", 10);
	mpz_set_str (iter_q,  "50000", 10);

   // mpf_set_z (f, iter);
            mpz_nextprime(p,p);
            mpz_nextprime(q,q);
    mpz_set(p_orig, p);
    mpz_set(q_orig, q);
    gmp_printf ("%Zd %Zd \n",p_orig, q_orig);
    int count = 0;
    for (int i = 0; i < 2; i++) {
        //mpz_add(m, m, iter_2);
        for (int i = 0; i <  5; i++) {
            count ++;
            mpz_add(p, p, iter_p);
            mpz_add(q, q, iter_q);
            //mpz_set(m, m1);
            //mpz_mul_ui(m, m, 13);
            //mpz_mdiv_ui(m, m, 10);
            //if(count > 5) {
            //    mpz_mul_ui(iter,iter, 2);
            //    count = 0;
            //}
            mpz_nextprime(p,p);
            mpz_nextprime(q,q);
            mpz_mul(N, q, p);
            mpz_sub(f, p, p_orig);
            mpz_sub(f1, q, q_orig);
            gmp_printf ("%Zd %Zd %Zd %Zd %Zd\n",p, f, q, f1, N);
        }
    }
	//mpz_set_str (m,  "3563359734431362578", 10);
	//mpz_set_str (m,  "58372837485639274836", 10);
    //mpz_nextprime(m1,m);
	// const unsigned int sumX = 999999;
	//gmp_printf ("prime %Zd,\n",m1);
    return 0;
}
