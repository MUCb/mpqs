#include <stdio.h>
#include <gmp.h>
#include <unistd.h>


int main (){
    mpz_t integ;
    char * str;
    int p = 1000;
    mpz_init (integ);
    mpz_init_set_si(integ , p);
    mpz_get_str(str, 10, integ);
    printf("%s\n", str);
    mpz_clear (integ);
    // sleep(10000);
}