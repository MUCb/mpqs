#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>


#define ARR_SIZE 1300
#define NUM_BORDER 999
// #define B 16
int Num_in_Arr(int num, int arr[], int size);
template<class InputIterator, class T> bool exists (InputIterator first, InputIterator last, const T& val);

int gcd(int x, int y)
{	return y ? gcd(y,x%y) : x; }
 


int main()
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

	FILE * rFile;
	char name1[30];
	sprintf(name1, "results/%d.txt", B);
	rFile = fopen (name1, "w");
	if(rFile != NULL)
	{
		for (int i = 0; i < ARR_SIZE && primers[i] > 0; ++i)
		{
			for (int j = i; j < ARR_SIZE && primers[j] > 0; ++j)
			{
				// int i = 0;
				// int j = 8;
				int p = primers[i];
				int q = primers[j];
									// std::cout <<"begin p = " << p <<" q = "<< q << std::endl;
				// double N = 0;
				int N = 0;
				N = p * q;
				// std::cout <<"N = " << N << std::endl;
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
				// double mod_N = N % B;
				
				int  x1 = 0;
				double  y1 = 0;
				x1 = sqrt(N);
				if(x1 != trunc(x1)) 
				{
					x1 = trunc(x1) + 1;
				}
								// std::cout << "sqrt N = "<< x1 << std::endl;
				int mod_x1 = x1 % B;
				int loop_old = 0;

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
				// if (x1 == N/2)
				int p_res = x1 + y1;
				int q_res = x1 - y1;
				fprintf(rFile, "p = %-5d q = %-5d N = %-10.d p = %-5d q = %-5d loop = %-10d loop_old = %-10d\n",p,q, N, p_res, std::abs(q_res), loop , loop_old);
				printf( "p = %-5d q = %-5d N = %-10.d p = %-5d q = %-5d loop = %-10d loop_old = %-10d\n",p,q, N, p_res, std::abs(q_res), loop , loop_old);
				
			}
		}
		fclose(rFile);
	}
 //	printf("Done!\n");

    return 1;
}




template<class InputIterator, class T>
  bool exists (InputIterator first, InputIterator last, const T& val)
{
  while (first!=last) {
    if (*first==val) return true;
    ++first;
  }
  return false;
}
