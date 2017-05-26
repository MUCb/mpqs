#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>


#define PRIME_SIZE 75
 uint64_t prime[PRIME_SIZE] = { 0,  1,    2,  	        
        3,         5,         7,        11,        13,        17,        19,        23, 
       29,        31,        37,        41,        43,        47,        53,        59, 
       61,        67,        71,        73,        79,        83,        89,        97, 
      101,       103,       107,       109,       113,       127,       131,       137, 
      139,       149,       151,       157,       163,       167,       173,       179, 
      181,       191,       193,       197,       199,       211,       223,       227, 
      229,       233,       239,       241,       251,       257,       263,       269, 
      271,       277,       281,       283,       293,       307,       311,       313,    
	  317,       331,       337,       347,       349,       353,       359,       367 };  


int main ()
{

	uint64_t p;
	uint64_t q;

//*********  test1  **************
	// p = prime[28];
	// q = prime[36];
//********************************

//*********  test2  **************
	// p = prime[29];
	// q = prime[36];
//********************************

//*********  test3  **************
	p = prime[30];
	q = prime[36];
//********************************

	uint64_t N = p * q; //15347;
	uint64_t sqrt_N = 0;
	printf("p=%"PRIu64"\tq=%"PRIu64"\tp*q=N=%"PRIu64"\n", p, q, N);
	
	// take square root of N 
	{
		double tmp = sqrt(N);
		if(tmp == trunc(tmp)) 
		{
			printf("<<<[FACTOR]>>> %"PRIu64"\n", N);
			exit(0);
		}
		else
		{
			sqrt_N = trunc(tmp) + 1;
		}
		printf("sqrt of N = %"PRIu64"\n",sqrt_N );
	}

	// selecting the size of the factor base
	double size_B;
	size_B = exp (sqrt (log(N) * log(log(N))) );
	size_B = pow(size_B , sqrt(2)/4);
	printf("size of factor base size_B=%f\n", size_B);
	// case for test 2 
	// size_B = size_B -2;
	size_B = size_B;

	// selecting smooth primes 
	std::vector<uint64_t> p_smooth;
	printf("smooth numbers\n");

	//prime is 2 - special case 
	// Modulo 2, every integer is a quadratic residue.
	p_smooth.push_back(prime[2]);
	printf("%"PRIu64"\n", prime[2]);

	for (uint64_t i = 3; (p_smooth.size() < size_B) && (i < PRIME_SIZE); ++i)
	{
		uint64_t tmp = N;
		for (int j = 1; j < (prime[i]-1)/2; ++j)
		{
			tmp = (tmp * N) % prime[i];
		}
		tmp %= prime[i];
		// printf("tmp %"PRIu64"\n", tmp);

		if( tmp == 1)
		{
			p_smooth.push_back(prime[i]);
			printf("%"PRIu64"\n", prime[i]);
		}
		// break;
	}

	// selecting the sieving interval
	uint32_t M;
	M = exp (sqrt (log(N) * log(log(N))) );
	M = pow(M , 3*sqrt(2)/4);
	printf("The sieving interval M=%"PRIu32"\n", M);


	// *** construct our sieve *** //
	std::vector<uint64_t> X;
	/* fill in  sqrt(N) + 1 sqrt(N) + 2  sqrt(N) + 3 .....*/
	for (uint64_t i = 0; i <= M; ++i)
	{
		X.push_back(sqrt_N + i);
		// printf("X = %"PRIu64"\t",X[I]);
	}
	// printf("\n");

	std::vector<uint64_t> Y;
	// fill in  (Xi)^2 - N 
	for (uint64_t i = 0; i <= M; ++i)
	{
		Y.push_back(X[i]*X[i] - N);
		// printf("Y = %"PRIu64"\t",Y[i]);
	}
	// printf("\n");

	// simple sieve 
	std::vector<uint64_t> V;
	V = Y;
	std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size())) ;
	for (int j = 0; j < p_smooth.size(); ++j)
	{
		for (int i = 0; i < M; ++i)
		{
			if(V[i] == 1)
				continue;

			uint64_t tmp;
			do{
				tmp = V[i] % p_smooth[j];
				if(tmp == 0){
					V[i] = V[i] / p_smooth[j];
					v_exp[i][j] += 1; 
				}
			} while (tmp == 0);
		}
		// break;
	}

	std::vector<uint64_t> smooth_num_1;
	std::vector<uint64_t> P1;
	for (int i = 0; i < V.size(); ++i)
	{
		int nul_flag = 0;
		// printf("V = %"PRIu64"\t",V[i]);
		if(V[i] == 1)
		{
			for (int j = 0; j < p_smooth.size(); ++j)
			{
				printf("%"PRIu64"\t", v_exp[i][j]);
				if ((v_exp[i][j] % 2 )!= 0)
					nul_flag = 1;
			}
			printf("%"PRIu64"\n", Y[i]);
			if (nul_flag){
				smooth_num_1.push_back(i);
			}
			else
			{
				P1.push_back(Y[i]);
			}
		}
	}
	printf("\n");

		std::vector<uint64_t> smooth_num;
	for (int i = p_smooth.size(); i < smooth_num_1.size(); ++i)
	{
		std::vector<uint64_t> smooth_num;
		for (int j = 0; j < (p_smooth.size() -1 ); ++j)
		{
			smooth_num.push_back(smooth_num_1[j]);
		}
		smooth_num.push_back(smooth_num_1[i]);


		for (int j = 0; j < smooth_num.size(); ++j)
		{
			printf("%"PRIu64"\t", smooth_num[j]);
		}
		printf("\n");
	// just print exponent array
	// for (int i = 0; i < V.size(); ++i)
	// {
	// 	for (int j = 0; j < p_smooth.size(); ++j)
	// 	{
	// 		printf("%"PRIu64"\t", v_exp[i][j]);
	// 	}
	// 	printf("\n");
	// }



	std::vector< std::vector<uint64_t> > v_exp_mod2(smooth_num.size(), std::vector<uint64_t> (p_smooth.size()) );
	for (int i = 0; i < smooth_num.size(); ++i)
	{
		std::vector<uint64_t> tmp;
		for (int j = 0; j < v_exp[ smooth_num[i] ].size(); ++j)
		{
			v_exp_mod2[i][j] = v_exp[ smooth_num[i] ][j] % 2;
		}
	}

	// just print exponent mod 2 array
	for (int i = 0; i < v_exp_mod2.size(); ++i)
	{
		for (int j = 0; j < v_exp_mod2[i].size(); ++j)
		{
			printf("%"PRIu64"\t", v_exp_mod2[i][j]);
		}
		printf("\n");
	}
	// tern around our matrix
	std::vector< std::vector<uint64_t> > v_exp_mod2_rev(p_smooth.size(), std::vector<uint64_t> (smooth_num.size()) );
	for (int j = 0; j < v_exp_mod2.size(); ++j)
	{
		for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
		{
			// printf("%"PRIu64"\t", v_exp_mod2[j][i]);
			v_exp_mod2_rev[i][j] = v_exp_mod2[j][i];
		}
		// printf("\n");
	}


	printf("\n");
	for (int j = 0; j < v_exp_mod2_rev.size(); ++j)
	{
		for (uint64_t i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
		{
			printf("%"PRIu64"\t", v_exp_mod2_rev[j][i]);
		}
		printf("\n");
	}



	// printf("tpp1 size %d\n", tpp1.size());
	int col = 0;
	int line = 0;
	for (int i = 0; i < v_exp_mod2_rev[0].size(); ++i)
	{
		int j;
		for (j = line; j < v_exp_mod2_rev.size(); ++j)
		{
			if (v_exp_mod2_rev[j][col] == 1)
			{
				break;
			}
		}
		if(j == v_exp_mod2_rev.size() ){
			col++;
			continue;
		} 
		else if( j != line && j < v_exp_mod2_rev.size())
		{
			// printf("i = %d j = %d\n", i, j);
			for (int k = col; k < v_exp_mod2_rev[0].size(); ++k)
			{

				// printf("p1 = %d\n", tpp1[i][k]);
				// printf("p2 = %d\n", tpp1[j][k]);
				std::swap(v_exp_mod2_rev[line][k], v_exp_mod2_rev[j][k]);
			}
		}

		for (int j = line+1; j < v_exp_mod2_rev.size(); ++j)
		{
			if(v_exp_mod2_rev[j][col] != 0)
			{
				for (int k = col; k < v_exp_mod2_rev[0].size(); ++k)
				{
					v_exp_mod2_rev[j][k] += v_exp_mod2_rev[col][k];
					v_exp_mod2_rev[j][k] %= 2;
				}
			}
		}
	
	// printf("\n");
	// for (int j = 0; j < v_exp_mod2_rev.size(); ++j)
	// {
	// 	for (uint64_t i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
	// 	{
	// 		printf("%"PRIu64"\t", v_exp_mod2_rev[j][i]);
	// 	}
	// 	printf("\n");
	// }
		col++;
		line++;

	}

	printf("\n");
	for (int j = 0; j < v_exp_mod2_rev.size(); ++j)
	{
		for (uint64_t i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
		{
			printf("%"PRIu64"\t", v_exp_mod2_rev[j][i]);
		}
		printf("\n");
	}



	printf("\n");
	for (int j = v_exp_mod2_rev.size() -1 ; j > 0; --j)
	{
		uint64_t i;
		for (i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
		{
			if (v_exp_mod2_rev[j][i] != 0)
				break;
		}

		if (i == v_exp_mod2_rev[j].size())
			continue;

		for (int k = j-1 ; k >= 0; --k)
		{
			if (v_exp_mod2_rev[k][i])
			{
				for (int z = 0; z < v_exp_mod2_rev[0].size(); ++z)
				{
					v_exp_mod2_rev[k][z] += v_exp_mod2_rev[j][z];
					v_exp_mod2_rev[k][z] %= 2;
				}
			}
		}
	}



	printf("\n");

	for (int j = 0; j < v_exp_mod2_rev.size(); ++j)
	{
		for (uint64_t i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
		{
			printf("%"PRIu64"\t", v_exp_mod2_rev[j][i]);
		}
		printf("\n");
	}

	std::vector< std::vector<uint64_t> > X_exp(1, std::vector<uint64_t> (smooth_num.size()) );

	for (int j = 0; j < X_exp.size(); ++j)
	{
		for (uint64_t i = 0; i <  X_exp[j].size(); ++i)
		{
			X_exp[j][i] = -1;
		}
		// printf("\n");
	}



	for (int j = 0; j < v_exp_mod2_rev.size(); ++j)
	{
		int count = 0;
		int num = 0;
		std::vector<uint64_t> tmp;
		for (uint64_t i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
		{
			// printf("%"PRIu64"\t", v_exp_mod2_rev[j][i]);
			if (v_exp_mod2_rev[j][i] == 1)
			{	
				
				printf("i == %"PRIu64"\n", i);
				tmp.push_back(i);
				count++;
				num = i;
			}
		}

		if (!count)
			continue;
		if(count == 1){
			for (uint64_t i = 0; i <  X_exp.size(); ++i)
			{
				X_exp[i][num] = 0;
			}
		}
		if(count > 1){
			int last = -1;
			int sum = 0;
			std::vector<uint64_t> tmp1;
			for (uint64_t k = 0; k <  tmp.size(); ++k)
			{
				if (X_exp[0][tmp[k]] != -1)
				{
					sum += X_exp[0][tmp[k]];
					sum %= 2;
					last = tmp[k];
					// tmp[k] = -1;
					count--;
				}
				else
					tmp1.push_back(tmp[k]);
			}

			for (uint64_t k = 0; k <  tmp.size(); ++k)
			{
				count--;
				// printf("%d-line  count %d\n", __LINE__, count);
				if (count == 0)
				{
					
					// printf("%d-line  count %"PRIu64"\n", __LINE__, X_exp[0][tmp1[k]]);
					if(X_exp[0][tmp[k]] == -1){
						int size = X_exp.size();
						for (uint64_t i = 0; i < size ; ++i){
							sum = 0;
							for (uint64_t f = 0; f <  tmp.size(); ++f)
							{
								if (X_exp[i][tmp[f]]  != -1)
									sum += X_exp[i][tmp[f]];
								// printf("tmp %"PRIu64"\t X_exp[i][tmp[f]]%"PRIu64"\n", tmp[f], X_exp[i][tmp[f]]);
							}
							sum %= 2;
							// printf("%d-line  sum %d\n", __LINE__, sum);

							if (last == -1)
							{
								if (sum == 1)
									X_exp[i][tmp[k]] = 1;
								else
									X_exp[i][tmp[k]] = 0;
							}
							else{

								if (sum == 1)
								// if (X_exp[i][last] == 1)
									X_exp[i][tmp[k]] = 1;
								else 
									X_exp[i][tmp[k]] = 0;
								
							}
						}
						last= tmp[k];
					}
					sum += X_exp[0][tmp[k]];
					sum %= 2;
				}
				else if (count > 0)
				{
					if(X_exp[0][tmp1[k]] == -1){
						// printf("%d-line  \n", __LINE__);
						int size = X_exp.size();
						for (uint64_t i = 0; i < size ; ++i){
							X_exp[i][tmp1[k]] = 1;
							X_exp.push_back(X_exp[i]);
							X_exp[i][tmp1[k]] = 0;
						}
						last = tmp1[k];
					}
					sum += X_exp[0][tmp1[k]];
					sum %= 2;
				}

			}
		}

		// 	printf("---------\n");
		// for (int j = 0; j < X_exp.size(); ++j)
		// {
		// 	for (uint64_t i = 0; i <  X_exp[j].size(); ++i)
		// 	{
		// 		printf("%"PRIu64"\t", X_exp[j][i]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n");
	}

// exit (0);
	// exit(0);
	// 	for (int i = 0; i <  smooth_num.size(); ++i)
	// {
	// 	printf("-----%"PRIu64"\n", Y[smooth_num[i]]);
	
	// }

	for (int j = 0; j < X_exp.size(); ++j)
	{
		uint64_t sumX = 1;
		uint64_t sumY = 1;
		uint64_t sum;
		int count  = 0;
		for (int i = 0; i <  X_exp[j].size(); ++i)
		{
			if (X_exp[j][i]){
			// printf("i %d\n", i);
				count ++;
				printf("X %"PRIu64"\t", X[smooth_num[i]]);
				printf("y %"PRIu64"\n", Y[smooth_num[i]]);
				sumX *= X[smooth_num[i]];
				sumY *= Y[smooth_num[i]];
				
			}
		}
		if (count > 4){
			printf("to many arguments ---\n");
			continue;
		}
		if (sumY > 1)
		{
			double tmp = sqrt(sumY);
			if(tmp != trunc(tmp)) 
			{
				printf("error  %"PRIu64"\n", sumY);
				exit(0);
			}
			sum = sumX - tmp;
			printf("%"PRIu64"\n", sum);
			P1.push_back(sum);
		}
	}
	// 	for (int i = 0; i <  P1.size(); ++i)
	// {
	// 	printf("-----%"PRIu64"\n", P1[i]);
	
	// }

	printf("Euclidean algorithm----\n");
	for (int i = 0; i <  P1.size(); ++i)
	{
		uint64_t tmp1 = P1[i];
		uint64_t tmp2 = N;
		uint64_t tmp3 = 0;

		while (1){
			tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
			if(!tmp1 || !tmp2)
				break;
		}
		if (tmp1 > 1 ){
			printf("%"PRIu64"\n", tmp1);
			if (tmp1 == p || tmp1 == q)
				printf("found p = %"PRIu64"\n", tmp1);
		}
				
		else if (tmp2 > 1 ){
			printf("%"PRIu64"\n", tmp2);
			if (tmp2 == p || tmp2 == q)
				printf("found p = %"PRIu64"\n", tmp2);
			
		}
		printf("----\n");

	}

	// exit (0);


	}
	exit (0);


	// for (int i = 0; i < v_exp_mod2[0].size(); ++i)
	// {
	// 	if (v_exp_mod2[v_exp_mod2.size()][i] == 0)
			
	// }

	exit(0);
}

