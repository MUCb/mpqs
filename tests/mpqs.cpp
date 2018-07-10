//#define BOOST_TEST_MODULE QS unit maytrix Test 
//#include <boost/test/included/unit_test.hpp> 
#include <iostream>
#include "dynamic_bin_matrix.h"
// #include "primes.h"
#include "quadratic_sieve_big.h"
#include "log.h"

#include <fstream>
#include "dixon_greatest_common_divisor_big.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primes_10_8.h"
#include "dixon_big_lib.h"
//#include "primes.h"
//#include "primes.h"
#include "numbers_dixon.h"
#include "big_2.h"

#include <math.h>
#include <time.h>
#include <gmp.h>
#include <gmpxx.h>


int showDebugMsg = 4;

int fread_number(const char * file_name, char * mystring) {
	FILE * pFile;
	pFile = fopen (file_name,"r");
	if (pFile == NULL) perror ("Error opening file");
	else {
		if ( fgets (mystring , 100 , pFile) != NULL ) {
			//puts (mystring);
		} else {
			std::cout << "error read prime numbers 1\n";
			return 0;
		}
		fclose (pFile);
	}

	// remove new line character
	char *pos;
	if ((pos=strchr(mystring, '\n')) != NULL)
		*pos = '\0';

	return 1;
}

//BOOST_AUTO_TEST_CASE(test_2) 
int main (void)
{
	int iter_1 = 5122300;
	int iter = 5561457;

	char mystring [100];
 
	time_t start;
	time_t start_gen;
	time_t finish;
	
	big one = 1;
	big null = 0;
	
	mpz_t p_gmp;
	mpz_t q_gmp;
	mpz_t N_gmp;
	mpz_t tmp_gmp;
	mpz_t P_gmp;
	mpz_t d_sqrt_N_gmp;
	mpz_t A_gmp;
	mpz_t B_gmp;
	mpz_t C_gmp;
	mpz_t fx_gmp;
	mpz_init(p_gmp);
	mpz_init(q_gmp);
	mpz_init(N_gmp);
	mpz_init(P_gmp);
	mpz_init(tmp_gmp);
	mpz_init(d_sqrt_N_gmp);
	mpz_init(A_gmp);
	mpz_init(B_gmp);
	mpz_init(C_gmp);
	mpz_init(fx_gmp);

	fread_number("prime_1", mystring);
	big p(mystring);
	mpz_set_str (p_gmp,  mystring, 10);
	fread_number("prime_2", mystring);
	big q(mystring);
	mpz_set_str (q_gmp,  mystring, 10);

	big N = p * q;
	big sqrt_N = 0;
	big d_sqrt_N = 0;
	big sqrt_Nk = 0;
	big Nk = 0;
	big k_big = 1;
	int k = 0;
	LOG(1) std::cout<< "p=" << p 
					<< "\tq=" << q 
					<< "\tN=" << N << "\n";
	sqrt_N = squareRoot(N);
	d_sqrt_N = squareRoot(N*2);
	LOG(2) std::cout << "sqrt 2n=" << d_sqrt_N <<  "\n";
	LOG(2) std::cout << "sqrt n=" << sqrt_N <<  "\n";

	sqrt_N = sqrt_N + one;
	LOG(2) std::cout << "n=" << N << "\tsqrt=" << sqrt_N <<  "\n";

	// selecting the size of the factor base
	double size_B;
	double L_B;
	//DEBUG (2,"log _B=%f\n", ln(N));
	//size_B = exp (0.5 * sqrt (ln(N) * log(ln(N))) );
	LOG(0) std::cout << "ln n=" << ln(N) << "\n";
	size_B = exp (sqrt (ln(N) * log(ln(N))) );
	//DEBUG (2,"size of factor base size_B=%f\n", ln(N));
	//DEBUG (2,"size of factor base size_B=%f\n", log(ln(N)));
	//DEBUG (2,"size of factor base size_B=%f\n", ln(N) * log(ln(N)));
	//DEBUG (2,"size of factor base size_B=%f\n",sqrt(ln(N) * log(ln(N))));
	//DEBUG (2,"size of factor base size_B=%f\n", size_B);
	size_B = pow(size_B , sqrt(2)/4);
	L_B = size_B;
	LOG(0) std::cout << "size n=" << size_B << "\n";
	//size_B *= 2;
	//size_B *= 3;
	LOG(0) std::cout << "size1n=" << size_B << "\n";
	//size_B = pow(size_B , sqrt(2)/4);
	DEBUG (1,"size of factor base size_B=%f\n", size_B);
//return 0;
  /*
	for (uint64_t i = 2; (p_smooth.size() < size_B) && (i < prime_size); ++i)
	{
		p_smooth.push_back(prime[i]);
		DEBUG(2, "%llu\n", prime[i]);
	}
*/
	// selecting the sieving interval
	double  M;
	double  M_orig;
	/*M = exp (sqrt (ln(N) * log(ln(N))) );
	M = pow(M , 3*sqrt(2)/4);
	*/
	//M = 2*size_B;
	//M = L_B;
	//double exp_lb = (3+0.00001)/(2+0.00001);
	//M = pow(L_B,2);
	//M = 5000;
	M = 50;
	
	big P = d_sqrt_N / M;
	LOG(2) std::cout << "P = " << P <<  "\n";
	
	//mpz_set_str (m,  "1000000000000", 10);
	//mpz_mod (xmodp, x, p);

	//big A = P*P;
	//A.pow(1);
	//N^(A-P+2)/4
	//LOG(2) std::cout << "A = " << A <<  "\n";
	//M = pow(L_B,exp_lb);
	//M = L_B*L_B*L_B;
	M_orig = M;
	//M = L_B;
	DEBUG (2, "The sieving interval M=%f\n", M);
/*(    ofstream myfile1;
	myfile1.open ("general.txt", ios::app);
	myfile1			<< "\tp=" << p 
					<< "\tq=" << q 
					<< "\tN=" << N 
					<< "\tM=" <<  M
					<< "\tsize_B=" << size_B
					<< "\n";
 
   myfile1.close();
*/
		std::vector<long long > p_smooth;
		DEBUG (2, "smooth numbers\n");
		long p_size = dixon_make_smooth_numbers_2(p_smooth, size_B, N);
		LOG (2) std:: cout << "smooth size " << p_size << "\n";
	// *** construct our sieve *** //
	std::vector<big_2> X;
	//std::vector<big_2> X_sm;
	std::vector<big_2> Y;
	//std::vector<big_2> Y_sm;
	std::vector<big_2> V;

	bin_matrix_t m_all(p_smooth.size()+1);
	// simple sieve 
	std::vector<long> solution_candidates_number;
	std::vector< std::vector<uint64_t> > v_exp;
	std::vector< std::vector<uint64_t> > v_exp_sm;
	//std::vector<int> smooth_num;

	long long x_count = 0;
	long long smooth_count = 0;
	long long eucl_count = 0;
	int exit_flag = 0;
	start = clock();
	start_gen = clock();

/*	  std::vector<big> sqrt_Nk;
	for (k = 0; k < (size_B); ++k) {
		k_big = numbers_dixon[k];
		sqrt_Nk.push_back(squareRoot(N * k_big));
	}
*/
	//bin_matrix_t m(size_B+1);
	//for (k = 0; k < (4*size_B); ++k)
	int size_K = L_B*L_B*L_B;
	//int size_K = L_B*L_B;
	std::vector<int> count_dixon(size_K);
		LOG(3) std::cout << "size K = " << size_K << "\n";
		//exit(0);
	mpz_mul(N_gmp, p_gmp,q_gmp);
	gmp_printf ("N %Zd\n",N_gmp);
	mpz_mul_ui(tmp_gmp, N_gmp,2);
	gmp_printf ("double N %Zd\n",tmp_gmp);
	mpz_sqrt(d_sqrt_N_gmp, tmp_gmp);
	gmp_printf ("d_sqrt %Zd\n",d_sqrt_N_gmp);
	mpz_div_ui(P_gmp, d_sqrt_N_gmp, M+k);
	//mpz_div_ui(P_gmp, d_sqrt_N_gmp, 5000+k);
	gmp_printf ("P %Zd\n",P_gmp);
	mpz_sqrt(P_gmp, P_gmp);
	gmp_printf ("P %Zd\n",P_gmp);
	mpz_sub_ui(P_gmp, P_gmp,10);
	gmp_printf ("sub 10  %Zd\n",P_gmp);

	for (k = 0; k < 4; ++k)
	//for (k = 1; k < 6090; k++)
	//for (int k1 = 0; k1 < 6090; k1=k1+10)
	//for (k = 1; k < size_K; ++k)
	{
		//k = k1;
		int missed = 0;
	//for (int k2 = 0; k2 < 10; k2=k2+1)
	{
		//k += 1;
		//if(k==3) k=31;
	mpz_nextprime(P_gmp,P_gmp);
	if (mpz_probab_prime_p (P_gmp, 1) == 2){
	gmp_printf ("111 %Zd\n",P_gmp);
	} else {
		mpz_nextprime(P_gmp,P_gmp);
	gmp_printf ("222 %Zd\n",P_gmp);
	}
	while (mpz_legendre(N_gmp,P_gmp) != 1){
		mpz_nextprime(P_gmp,P_gmp);
	gmp_printf ("333 %Zd\n",P_gmp);
	}

	gmp_printf ("g %Zd\n",P_gmp);
	// a = p^2
	mpz_mul(A_gmp, P_gmp,P_gmp);
	gmp_printf ("A %Zd\n",A_gmp);
	//b = N^((p^2-p+2)/4) mod p^2
	//p^2-p
	mpz_sub(tmp_gmp, A_gmp,P_gmp);
	//p^2-p+2
	mpz_add_ui(tmp_gmp, tmp_gmp,2);
	//(p^2-p+2)/4
	mpz_div_ui(tmp_gmp, tmp_gmp,4);
	//N^(p^2-p+2)/4a mod p^2
	mpz_powm(tmp_gmp,N_gmp, tmp_gmp,A_gmp);
	mpz_set(B_gmp,tmp_gmp);
	gmp_printf ("B %Zd\n",B_gmp);

	// c = (b^2-n)/a
	mpz_mul(tmp_gmp,B_gmp,B_gmp);
	gmp_printf ("special B %Zd\n",B_gmp);
	mpz_sub(tmp_gmp,tmp_gmp,N_gmp);
	mpz_div(C_gmp,tmp_gmp,A_gmp);
	gmp_printf ("C %Zd\n",C_gmp);
	//mpz_mod(tmp_gmp,tmp_gmp,A_gmp);
	//gmp_printf ("%Zd\n",tmp_gmp);
	//mpz_mod(tmp_gmp,N_gmp,A_gmp);
	//gmp_printf ("%Zd\n",tmp_gmp);
	char test[200];
	mpz_get_str(test,10, C_gmp);
	printf("test string %s\n",test);
	big C_big(test);
	std::cout << "C big " << C_big << "\n";
	mpz_get_str(test,10, B_gmp);
	///gmp_printf ("special B %Zd\n",B_gmp);
	//printf("test string B %s\n",test);
	big B_big(test);
	std::cout << "B big " << B_big << "\n";
	mpz_get_str(test,10, A_gmp);
	big A_big(test);
	std::cout << "A big " << A_big << "\n";
 



		// selecting smooth primes 
		std::vector<long long > p_smooth_pos;
		//k_big = k;
		//LOG(0) std::cout << "K_big = " << k_big << "\n";
		//k_big = numbers_dixon[k];
		//Nk = N*k_big;
		

		//LOG(3) std::cout << "NK = " << Nk << "\n";
		//DEBUG (2, "smooth numbers\n");
		//long p_size = dixon_make_smooth_numbers_2(p_smooth, size_B, Nk);
		//LOG (2) std:: cout << "smooth size " << p_size << "\n";
		//LOG (0) std:: cout << "smooth size " << size_B << "\n";
		//sqrt_Nk = squareRoot(Nk);
		

		//LOG(3) std::cout << "K = " << k_big << "\n";
		//LOG(3) std::cout << "sqrt NK = " << sqrt_Nk << "\n";



	//make_smooth_numbers_1(p_smooth, size_B, N);
	//double fa;
	//LOG (2) std::cout << "The sieving interval M=" << fa << "\n";
	//M *= 4*fa*0.001; // need to check
	//fa = (4*p_size*p_size)/size_B/size_B; // need to check
	//fa = p_size/size_B; // need to check
	//fa *= fa;
	//M = M_orig * fa; // need to check
	//LOG (0) std::cout << "The sieving interval fa=" << fa << "\n";
	LOG (2) std::cout << "The sieving interval M=" << M << "\n";

	for (long  j = 0, y_number = -1; j < M; j++){
		for (int  d = 0; d < 2; d++){

			big tmp_x;
			big tmp_y;
			if(d == 1 && j == 0)
				continue;
			if(d == 0 ){
				tmp_x = j;
				tmp_y = A_big*tmp_x*tmp_x + B_big*tmp_x*2;
				if(C_big <0) {
						C_big.sign = 0;
						tmp_y = tmp_y - C_big;
						C_big.sign = 1;
				}
				else {
						tmp_y = tmp_y + C_big;
				}
				
				//X.push_back(sqrt_N - j);
			}
			else {
				//X.push_back(sqrt_N + j);
				tmp_x = j;
				tmp_y = A_big*tmp_x*tmp_x - B_big*tmp_x*2;
				if(C_big <0) {
						C_big.sign = 0;
						tmp_y = tmp_y - C_big;
						C_big.sign = 1;
				}
				else {
						tmp_y = tmp_y + C_big;
				}
				tmp_x = -j;
				//tmp_y = A_big*tmp_x*tmp_x - B_big*tmp_x*2+ C_big;
			}
				//tmp_x = sqrt_N + j;

			
			y_number++;
			x_count++;
			// DEBUG (2, "%s %d\n", __func__, __LINE__);
			//std::cout <<	 "X" << j << " =" << X[y_number] << "\n";
			//tmp_y = tmp_y * A_big;
			//tmp_y = tmp_y % N;
			big tmp_v;
			LOG (4) std::cout <<	 "tmp_y " << tmp_y << "\n";
			//std::cout <<	 "N " << N << "\n";
		/*	
			if(tmp_y < N) {
				//std::cout <<	 "tmp sign " << tmp << "\n";
				//std::cout <<	 "N sign " <<  N << "\n";
				tmp_y = N - tmp_y;
				tmp_y.sign = 1;
			LOG (4) std::cout <<	 "tmp_y " << tmp_y << "\n";
				//std::cout <<	 "tmp1 " << tmp << "\n";
				//std::cout <<	 "N " << N << "\n";
				
				//Y.push_back(tmp);
				
				////Y.push_back(N-tmp);
			} else {
				tmp_y = tmp_y % N;
			LOG (4) std::cout <<	 "tmp_y " << tmp_y << "\n";
				//Y.push_back(tmp % N);
			}
*/

#define NEGATIVE_SIGN	 0 
#define FIRST_VALUE		 1

			//v_exp.push_back(std::vector<uint64_t> (p_smooth.size() + 1));
            std::vector<uint64_t> v_exp_tmp(p_smooth.size() + 1);
			//std::vector<uint64_t> v_exp_tmp(p_size + 1);
			//std::vector<uint64_t> v_exp_ext(size_B + 1);
			//V.push_back(Y[y_number]);

			if(tmp_y < null )
				v_exp_tmp[NEGATIVE_SIGN] = 1;
			//LOG(3) std:: cout << "|" << v_exp_tmp[NEGATIVE_SIGN] << "|\n";

			//big tmp_y1 ("-28512018742020686899625");
			//tmp_v = prime_factorisation(tmp_y1, p_smooth, v_exp_tmp);
		LOG (2) std:: cout << "smooth size " << p_size << "\n";
			tmp_v = prime_factorisation(tmp_y, p_smooth, v_exp_tmp);

//exit(0);
			//LOG(2) std::cout << "X = " << tmp_x << "\tY = " << tmp_y1 << " tmp_v " << tmp_v << " pers " << (j * 100) / (M/2) << "\n";
			LOG(3) std::cout << "X = " << tmp_x << "\tY = " << tmp_y 
					<< " tmp_v " << tmp_v 
					<< " pers " << (j * 100) / (M/2) 
					<< "\n";

			//return 0;
			//LOG(3) std::cout<< "y="<< tmp_y << "\tx=" << tmp_x << "\tv=" << tmp_v << "\n";
			big_2 one(1);
			big_2 min_one(-1);

			if(tmp_v == min_one || tmp_v == one){

				int null_flag = 1;
				//exit(0); 
				null_flag = zero_vector_mod2_check(v_exp_tmp);

					DEBUG(3, "%s %d  try to add \n",__func__, __LINE__);
				if (null_flag && tmp_v > 0) { // sign check is extra !!!!
					continue; // special case need to work
					big_2 found = 0;
					std::vector<int64_t> tmp;
					tmp.push_back(y_number);
					found = dixon_euclid_gcd_big( X, Y, tmp, p, q, N,v_exp, p_smooth, size_B);
					if (! (found == 0)) {
						exit_flag = 1;
						break;
					}
				} else {
					Y.push_back(tmp_y);
					X.push_back(tmp_x);

					finish = clock();
					count_dixon[k]++;
					ofstream myfile;
					LOG(1) std::cout << tmp_x << "\t" << tmp_y	<< "\t" << (double)(finish - start) / CLOCKS_PER_SEC << "\n";
					// myfile.open ("example.txt", ios::app);
					// myfile << k_big	<< "\t" << tmp_x << "\t" << tmp_y  << "\t" << (double)(finish - start) / CLOCKS_PER_SEC << "\n";
					// for (int h = 0; h < v_exp_tmp.size(); h++)
					//	  myfile << v_exp_tmp[h];
					// myfile << "\n";
					// myfile.close();
					start = clock();
					//v_exp_ext[NEGATIVE_SIGN] = v_exp_tmp[NEGATIVE_SIGN];
					//for(int g = 1; g < p_smooth_pos.size(); g++) {
					//	v_exp_ext[p_smooth_pos[g-1]] = v_exp_tmp[g];
					//	LOG(1) std::cout << p_smooth_pos[g] << "\t" << v_exp_tmp[g] << "\n";
					//}
					//smooth_num.push_back(y_number);
					//DEBUG(3, "%s %d  try to add \n",__func__, __LINE__);
					v_exp.push_back(v_exp_tmp);
					smooth_count++;


					if (m_all.add_row(v_exp_tmp) == 1){
						//m.add_row(v_exp_tmp);
						//int exponent_num = (v_exp_tmp.size() - 1);
						// ERROR("exp %d exp_num %d\n", v_exp[y_number][exponent_num], exponent_num);
						int count_flag = 0;
						//add_counter_row(m_counter ,counter ,exponent_num);
						// DEBUG (2,"size num = %d\t", smooth_num.size());
						m_all.show();
						int null_line = m_all.make_upper_triangular_static();

		//return 0;
						if (null_line > -1) {
							std::vector<int64_t> XYiters;
							DEBUG(3, "line %d NUll line  %d=============", __LINE__ , null_line);
							for (uint64_t col = 0; col <  m_all.filled; ++col) {
								DEBUG (3,"matrix[%d][%d] = %ld\n",null_line,col, m_all.unit_matrix[null_line][col]);
								if( m_all.unit_matrix[null_line][col] > 0) {
									DEBUG (3,"num = %d\t",col);
									LOG(3) std::cout << "Y	= " <<	Y[col] << "\n";
									XYiters.push_back(col);
								}
							}
							DEBUG (2,"\n");

							eucl_count++;
							big found = 0;
							found = dixon_euclid_gcd_big( X, Y, XYiters, p, q, N, v_exp, p_smooth, size_B);
							// printf("found %lu\n", found);
							// m_all.show();
							if (found.size != 0) {
								std::cout << "Found solution i=" << iter << "\tj=" << iter_1 << " p=" << p << " q=" << q << "\n";
								// exit( null_line);
								exit_flag=1;
								//break_flag = 1;
								break;
							} else {
								//m_all.delete_row(m_all.filled -1);
								//m.show();
								LOG(2) std::cout << "filled =" << m_all.filled <<  "\n";
								if (m_all.filled > m_all.collumn_size) {
									m_all.show();
									LOG(2) std::cout << "trunagular size " << m_all.triangular_v.size() << "\n";
									for (int j = 0; j < m_all.triangular_v.size(); j++)
										LOG(2) std::cout << m_all.triangular_v[j] << "\n";
									LOG(2) std::cout << "\n";
								}
								m_all.delete_row(m_all.filled - 1 );
								//m.delete_row(m_all.filled - 1 );
								LOG(2) std::cout << "filled1 =" << m_all.filled <<	"\n";
								if (m_all.filled > m_all.collumn_size) {
									m_all.show();
									ERROR("matrix to big aaaaa\n");
									exit(0);
								}
								//DEBUG (3,"delete matrix raw %d\n",__LINE__ );
								//m_all.show();
								//smooth_num.pop_back();
								Y.pop_back();
								X.pop_back();
								v_exp.pop_back();
								//exit(0);
							}
						}

					}
					else
					{
						ERROR("cant add aaaaa\n");
						exit(0);
					}

				}
				DEBUG (3, "\n");
			}
			if (exit_flag)
			break;
		}
	if (exit_flag)
			break;
			}
	LOG(0) std::cout << "dixon count " << count_dixon[k] << "\n";
	//if(count_dixon[k] < 1){
	//		missed++;
	//		if(missed > 1){
	//			break;
	//		}
	//} else {
	//	missed = 0;
	//}
	//if (exit_flag)
	//		break;
 
	}
	if (exit_flag)
			break;
 
	}
	if(!exit_flag)
		LOG(0) std::cout << "Fail solution i=" << iter << "\tj=" << iter_1 << " p=" << p << "\tq=" << q << "\n";

					finish = clock();
	ofstream myfile;
					myfile.open ("results.txt", ios::app);
	myfile		   << "" << exit_flag 
					<< "\t" << p 
					<< "\t" << q 
					<< "\t" << N 
					<< "\t" <<	M
					<< "\t" << size_B
					<< "\t" << x_count 
					<< "\t" << smooth_count 
					<< "\t" << k 
					<< "\t" << eucl_count 
					<< "\t" << (double)(finish - start_gen) / CLOCKS_PER_SEC 
					<< "\n";
	/*myfile		 << "res=" << exit_flag 
					<< "\tp=" << p 
					<< "\tq=" << q 
					<< "\tN=" << N 
					<< "\tM=" <<  M
					<< "\tsize_B=" << size_B
					<< "\tx_count=" << x_count 
					<< "\tsmooth_count=" << smooth_count 
					<< "\teucl_count" << eucl_count 
					<< "\ttime=" << (double)(finish - start_gen) / CLOCKS_PER_SEC 
					<< "\n";
*/ 
					//for (int h = 0; h < v_exp_tmp.size(); h++)
					 //   myfile << v_exp_tmp[h];
					//myfile << "\n";
					myfile.close();

					 myfile.open ("dixon_count.txt", ios::app);
					 for (int i = 0; i < size_K; ++i)
					 {
						myfile << "\t" << count_dixon[i];
					 }
					myfile << "\n";
					myfile.close();
				   

 
	return 0;
}
