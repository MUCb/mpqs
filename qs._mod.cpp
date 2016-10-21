#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>

 uint64_t prime[75] = { 0,  1,    2,  	        
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

	//	------choose BASE 
	const int B = 10;
	int table_x[B] = {0};
	std::vector<int> table_sqr_x;
	// -------filling the table (x^2)mod_B 
	for (int i = 0; i < B; ++i)
	{
		table_x[i] = (i*i) % B;
		// std::cout << "num = "<<table_x[i] <<"  ";
		// ------selection only different residues
		if(exists (table_sqr_x.begin(), table_sqr_x.end(), table_x[i]))  
		{ 
			// std::cout<<"find" << "\n";
		}
		else 
		{
			// std::cout << "not found\n";   
			table_sqr_x.push_back(table_x[i]);
		}
	}

	// std::cout << table_sqr_x.size()<<std::endl;
	std::vector<int> table_sqr_x_N(table_sqr_x.size());



	

	//########################################################################


	//####################     read primers from file      ###################
	int primers[ARR_SIZE] = {0};
	FILE * pFile;
	pFile = fopen ("numbers.txt", "r");
	if(pFile != NULL)
	{
		int counter = 0;
		while(!feof(pFile))
		{
			fscanf(pFile, "%d", &primers[counter++]);
	    }
		// printf("counter = |%d|\n", counter);    
		fclose(pFile);
	}
	else 
	{
		fprintf(stderr,"error: could not open file\n");
	}
	//########################################################################
 

		// #########  modification #############
			// int N = 213;
			int mod_N = N % B;
			// std::cout <<"mod_N = " << mod_N << std::endl;
			
			// ------the number of possible residues of N
			std::vector<int> table_sqr_x_N_sqrt;
			// double residual_sqrt = 0;
			for (int i = 0; i < table_sqr_x.size(); ++i)
			{
				int j = 0;
				j = table_sqr_x[i] - mod_N;
				if (j < 0 ) 
					j += B;
				table_sqr_x_N[i] = j % B;
				if(exists (table_sqr_x.begin(), table_sqr_x.end(), table_sqr_x_N[i])) 
				// residual_sqrt = sqrt(table_sqr_x_N[i]);
				// if(residual_sqrt == trunc(residual_sqrt)) 
				{
					table_sqr_x_N_sqrt.push_back(table_sqr_x[i]);
							// std::cout << "find sqrt = "<<table_sqr_x_N[i] << " from = "<< table_sqr_x[i] << std::endl;
				}

				// std::cout<< table_sqr_x_N[i]<<std::endl;
			}

			std::vector<int> final_x;
			for (int i = 0; i < B; ++i)
			{
				for (int j = 0; j < table_sqr_x_N_sqrt.size(); ++j)	
				{
					if (table_x[i] == table_sqr_x_N_sqrt[j])
					{
						final_x.push_back(i);
							// std::cout << i <<"  find\n";
						break;
					}
				}
				// std::cout <<"hahan\n";
			}

		//###################################### 

				std::vector<int> final_x_ost;
				for (int j = 0; j < (final_x.size() - 1); ++j)
				{
									// std::cout<< "j = " << j  << " final = " << final_x[j]<< std::endl;
					final_x_ost.push_back(final_x[j+1] - final_x[j] );
				}
				// std::cout << "last = " << final_x[final_x.size()-1]<< std::endl;
				final_x_ost.push_back(B + final_x[0] - final_x[final_x.size()-1]);
				for (int j = 0; j < final_x_ost.size(); ++j)
				{
									// std::cout << "ost = " << final_x_ost[j] << std::endl;
				} 

				
				int ost_count = 0;
				std::vector<int>::iterator it;
				while(1)
				{
					if(exists(final_x.begin(), final_x.end(),(x1 % B)) )
					{
										// std::cout << "find first x1 = " << x1 << " x1 mod B = "<< x1%B << std::endl;
						it = std::find(final_x.begin(), final_x.end(), (x1 % B));
						break;
					}
					loop_old ++;
					x1++;
					if(x1 > N) 
					{
						std::cout << "error find x1 == N\n"; 
					}
				}
				// std::cout << "The element following " << *it << '\n';
				int nPosition = distance (final_x.begin (), it);
									// std::cout << "nPosition " << nPosition << '\n';
				// return 0;


				// fprintf(rFile, "x = %f  ", x1);
				int loop = 0;  


				
				while (x1 < N/2)
				{
					// std::cout << "check1\n";
					if(exists(final_x.begin(), final_x.end(),(x1 % B)) )
					{
						// std::cout<< "check2\n";
						y1 = x1 * x1 - N;
						y1 = sqrt(y1);
						// fprintf(rFile, "y = %f  ", y1);
						// printf("x = %d y = %f\n",x1 ,y1);
						loop++;
						if(y1 == trunc(y1))
						{ 
							// printf("find y1 = %f x1 = %d\n", y1, x1); 
							break;
						}
					}else 
					{
						std::cout << "bad x = " << x1 << std::endl;
						return 0;
					}
					// x1 += 1;
					x1 += final_x_ost[nPosition];
					loop_old += final_x_ost[nPosition];
					nPosition++;
					if(nPosition >= final_x_ost.size()) { nPosition = 0;}
				}









	uint64_t N = 16157;
	uint64_t sqrtN = 0;
	double tmp = sqrt(N);
	if(tmp == trunc(tmp)) 
	{
		printf("<<<[FACTOR]>>> %"PRIu64"\n", N);
	}
	else
	{
		sqrtN = trunc(tmp) + 1;
	}



	double fN = N;
	double fN1;
	double lnN = 0.0;
	double lnlnN = 0.0;
	lnN = log(fN);
	lnlnN = log(lnN);
	fN = lnN * lnlnN;
	fN = sqrt(fN);
	fN1 = exp(fN);
	fN = fN / 2;
	fN = exp(fN);

	uint64_t P = 0;
	uint64_t A = 0;
	P = trunc(fN);
	A = trunc(fN1);
	P = 30;
	/* if N to small M will be wrong, please consider a pen and paper instead */
	printf("P = %"PRIu64"\n", P);
	printf("A = %"PRIu64"\n", A);

	std::vector<uint64_t> tt;
	std::vector<uint64_t> tt2;
	for (uint64_t i = 0; i <= A; ++i)
	{
		// printf("p = %"PRIu64"\n",sqrtN + i);
		tt.push_back(sqrtN + i);
	}
	printf("%s:%d\n", __FILE__, __LINE__);
	for (uint64_t i = 0; i <  tt.size(); ++i)
	{
		// printf("p = %"PRIu64"\n",(tt[i]*tt[i]) - N);
		tt2.push_back((tt[i]*tt[i]) - N);
	}

	// for (uint64_t i = 0; i <  tt2.size(); ++i)
	// {
	// 	printf("p = %"PRIu64"\n",tt2[i]);
	// }

	

	std::vector< std::vector<uint64_t> > tpp;
	std::vector<uint64_t> tp;
	tp.push_back(2);
	
	{
		std::vector<uint64_t> tmp(tt2.size());
		tpp.push_back(tmp);
	}

	for (uint64_t p = 3; prime[p] < P; ++p)
	{
	// printf("p1 = : %"PRIu64"\n", prime[p]);
		uint64_t Nmodp = N % prime[p];
	// printf("Nmodp: %"PRIu64"\n", Nmodp);
		uint64_t tmp = Nmodp; 
		for (uint64_t i = 2; i <= (prime[p]- 1)/2; ++i)
		{
			// printf("i = %d\n", i);
			tmp = (tmp * Nmodp ) % prime[p];
		}
		// printf("tmp = %"PRIu64"\n", tmp);
		if( tmp == 1)
		{
			tp.push_back(prime[p]);
			printf("p = %"PRIu64"\n", prime[p]);
			std::vector<uint64_t> pv(tt2.size());
			tpp.push_back(pv);
		}
	}
	// return 0;


	for (uint64_t j = 0; j <  tp.size(); ++j)
	{	
		int flag = 1;
		while(flag)
		{
			flag = 0;
			for (uint64_t i = 0; i <  tt2.size(); ++i)
			{
				if((tt2[i] % tp[j])  == 0)
				{
					flag = 1;
					tt2[i] = tt2[i] / tp[j];
					tpp[j][i] += 1;
				}
			}
			
		}
	}

	for (uint64_t i = 0; i <  tt2.size(); ++i)
	{
		if(tt2[i] == 1){
			printf("%"PRIu64"\t",tt[i]);
			printf("%"PRIu64"\t",tt2[i]);
			printf("%"PRIu64"\t", tpp[0][i]);
			printf("%"PRIu64"\t", tpp[1][i]);
			printf("%"PRIu64"\t", tpp[2][i]);
			printf("%"PRIu64"\t", tpp[3][i]);
			printf("%"PRIu64"\n", tpp[4][i]);
			
		}

	}


	// 	std::vector<uint64_t> ttmodp;
	// 	for (uint64_t i = 0; i <  tt.size(); ++i)
	// 	{
	// 		 tt[i] % 
	// 		if (! std::find(ttmodp.begin(), ttmodp.end(), tt[i]) != ttmodp.end())
	// 		{
	// 			ttmodp.push_back()
	// 		}

	// 		// printf("p = %"PRIu64"\n",sqrtN + i);
	// 		tt2.push_back(sqrtN*sqrtN - N);
	// 	}

	// 	int degree = 1;
	// 	uint64_t t1 = 1;
	// 	uint64_t p = tp[i];
	// 	printf("11p = %"PRIu64"\n", tp[i]);
	// 		printf("p = %"PRIu64"\n", p);
	// 		printf("max = %"PRIu64"\n", tt[tp.size()-1]);
	// 		printf("min = %"PRIu64"\n", tt[0]);

	// 	while(true)
	// 	{
	// 		int flag = 0;
	// 		p = tp[i];
	// 		for (int j = 1; j < degree; ++j)
	// 		{
	// 			p *= tp[i];
	// 		}
	// 		printf("p = %"PRIu64"\n", p);
	// 		if(p> 5000)
	// 			return 0;
	// 		uint64_t Nmodp = N % p;
	// 		printf("Nmodp = %"PRIu64"\n", Nmodp);
	// 		fN = 1;
	// 	// printf("%s:%d\n", __FILE__, __LINE__);

	// 		int g = 0;
	// 		while(true)
	// 		{
	// 			fN = sqrt(Nmodp);
	// 			fN1 = trunc(fN);
	// 			printf("Nmodp1 = %"PRIu64"\n", Nmodp);
	// 			printf("fN = %f\n", fN);
	// 			// printf("trunc = %f\n", trunc(fN));
	// 			// return 0;
	// 			g++;
	// 			if(g > 100)
	// 				break;
	// 			if(fN == fN1)
	// 			{

	// 				printf("fN = %f\n", fN);
	// 				printf("tt0 = %"PRIu64"\n", tt[0]);
	// 				printf("tt1 = %"PRIu64"\n", tt[tp.size()-1]);
	// 				if((fN <= tt[0]) && (fN >= tt[tp.size()-1]))// errror
	// 				{
	// 					flag = 1;
	// 					break;
	// 				}
					
	// 			}
	// 			// else
	// 			// {
	// 			// }
	// 			Nmodp += tp[i];
				
	// 		}
	// 		printf("t1 = %f\n", fN);
	// 		return 0;
	// 		if (flag)
	// 		{
	// 			break;
	// 		}
	// 		t1 = fN;
	// 		degree++;
	// 	}
	// 	printf("t11 = %"PRIu64"\n", t1);
	// 	printf("degree = %d\n", --degree);
	// }
}

