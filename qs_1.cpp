#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>


const int showDebugMsg = 3;

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


#define ERROR(fmt, arg...)  fprintf(stdout, "ERROR: "fmt"\n", ##arg);

#define DEBUG(level, fmt, arg...)                       \
    { if(showDebugMsg>=level) {                         \
        fprintf(stdout, fmt"", ##arg);       \
    } }
        // fprintf(stdout, "DEBUG: "fmt"", ##arg);       \


class bin_matrix_t {
public: 
    std::vector< std::vector<uint64_t> > matrix;
    std::vector< std::vector<uint64_t> > unit_matrix;
    int size;
    int filled;
    bin_matrix_t(int num);
    bin_matrix_t();
    void init_unit(void);
    void show(void);
    void add(std::vector<uint64_t> v1);
    int  make_upper_triangular(void);
    int  make_lower_triangular(void);
};

bin_matrix_t::bin_matrix_t(){
}

bin_matrix_t::bin_matrix_t(int num) : matrix(num, std::vector<uint64_t> (num)), 
                                unit_matrix(num, std::vector<uint64_t> (num)),
                                size(num),
                                filled(0)
{
    init_unit();
}

void bin_matrix_t::init_unit(void)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if(i == j)
                unit_matrix[i][j] = 1;
            else
                unit_matrix[i][j] = 0;

            // DEBUG (3,"%"PRIu64"\t", unit_matrix[i][j]);
        }
        // DEBUG (3,"\n");
    }
}


void bin_matrix_t::show(void){
        // just print exponent mod 2 array
    DEBUG (3,"matrix\n");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            DEBUG (3,"%"PRIu64"\t", matrix[i][j]);
        }
        printf("\n");
    }

    DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int j = 0; j < unit_matrix.size(); ++j)
    {
        for (uint64_t i = 0; i <  unit_matrix[j].size(); ++i)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
        }
        DEBUG (3,"\n");
    }
    DEBUG (3,"\n");
}

void bin_matrix_t::add(std::vector<uint64_t> v1)
{
    if (filled < size){
        for (int j = 0; j < v1.size() && j < size; ++j)
        {
            matrix[filled][j] = v1[j] % 2;
        }
        filled++;
    }
}



int  bin_matrix_t::make_upper_triangular(void)
{
    int col = 0;
    int line = 0;
    int null_line = -1;
    for (int i = 0; i < size; ++i)
    {
        int j;
        for (j = line; j < size; ++j)
        {
            if (matrix[j][col] == 1)
            {
                break;
            }
        }

        if(j == size ){
            col++;
            continue;
        }
        else if( j != line && j < size)
        {
            // printf("i = %d j = %d\n", i, j);
            for (int k = 0; k < size; ++k)
            {

                // printf("p1 = %d\n", tpp1[i][k]);
                // printf("p2 = %d\n", tpp1[j][k]);
                std::swap(matrix[line][k], matrix[j][k]);
                std::swap(unit_matrix[line][k], unit_matrix[j][k]);
            }
        }
        for (int j = line+1; j < size; ++j)
        {
            if(matrix[j][col] != 0)
            {
                for (int k = 0; k < size; ++k)
                // for (int k = col; k < v_exp_mod2[0].size(); ++k)
                {
                    matrix[j][k] += matrix[col][k];
                    matrix[j][k] %= 2;

                    unit_matrix[j][k] += unit_matrix[col][k];
                    unit_matrix[j][k] %= 2;
                }
            }
            if ( std::find(matrix[j].begin(), matrix[j].end(), 1) == matrix[j].end() )
            {
                DEBUG (1,"nULLL !!!!!!!!\n");
                // DEBUG (3," smooth_num %"PRIu64"\t", smooth_num[j]);
                // P1.push_back(j);
                null_line = j;
                break;
            }
        }

        if (null_line != -1)
            break;

        show();

            col++;
            line++;
    
    }
    return null_line;
}


int  bin_matrix_t::make_lower_triangular(void) 
{
        // printf("tpp1 size %d\n", tpp1.size());
    // int col = 0;
    // int line = 0;
    int null_line = -1;
    for (int i = size -1 ; i >= 0; --i)
    {

        // DEBUG (3," =============================== %d\n", i);
        if (matrix[i][i] != 1)
        {
            ERROR("error %d\n", i);
            continue;
        }

        for (int j = i-1; j >= 0; --j)
        {
            if(matrix[j][i] != 0)
            {
                for (int k = 0; k < size; ++k)
                // for (int k = col; k < v_exp_mod2[0].size(); ++k)
                {
                    matrix[j][k] += matrix[i][k];
                    matrix[j][k] %= 2;

                    unit_matrix[j][k] += unit_matrix[i][k];
                    unit_matrix[j][k] %= 2;
                }
            }
            if ( std::find(matrix[j].begin(), matrix[j].end(), 1) == matrix[j].end() )
            {
                DEBUG (3,"nULLL !!!!!!!!\n");
                // printf(" smooth_num %"PRIu64"\t", smooth_num[i]);
                // P1.push_back(j);
                null_line = j;
                break;
            }
        }

    if (null_line != -1)
        break;

    show();
    // DEBUG (3,"##########################################################################\n");
    // DEBUG (3,"\n");
    // for (int j = 0; j < v_exp_mod2.size(); ++j)
    // {
    //  for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
    //  {
    //      DEBUG (3,"%"PRIu64"\t", v_exp_mod2[j][i]);
    //  }
    //  DEBUG (3,"\n");
    // }

    //  DEBUG (3,"\n");
    // DEBUG (3,"unit matrix\n");
    // for (int j = 0; j < unit_matrix.size(); ++j)
    // {
    //  for (uint64_t i = 0; i <  unit_matrix[j].size(); ++i)
    //  {
    //      DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
    //  }
    //  DEBUG (3,"\n");
    // }
        // col++;
        // line++;

    }
    return null_line;

}


//Euclid's Algorithm, Greatest Common Divisor
uint64_t euclid_gcd(const std::vector<uint64_t>& X,
                    const std::vector<uint64_t>& Y,
                    const std::vector<uint64_t>& iterator,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N
                )
{
    if (iterator.size() > 0)
    {
        DEBUG(2, "Euclidean algorithm----\n");

        int32_t sumX = 1;
        int32_t sumY = 1;
        uint64_t sumYY = 1;
        uint64_t sum;

        // need a message 
        for (int j = 0; j <  iterator.size(); ++j)
        {
            DEBUG(2, "X %"PRIu64"\tY %"PRIu64"\n", X[iterator[j]], Y[iterator[j]]);
            sumX *= X[iterator[j]];
            sumYY *= Y[iterator[j]];
        }

        // take square root from YY
        if (sumYY > 1)
        {
            sumY = sqrt(sumYY);
            if(sumY != trunc(sumY)) 
            {
                ERROR(" %"PRIu64" is not a square", sumYY);
                return 0;
            }
            DEBUG(2, "sqrt Y %"PRIu32"\n", sumY);
        }
        
        // make two attempts to find a solution 
        // y + x and y - x 
        for (int j = 0; j < 2; ++j)
        {
            int64_t tmp1;
            if (j == 0){ 
                tmp1 = sumY + sumX;
                DEBUG (3, "firtst attept Y + X = %"PRIu64"\n", tmp1);
            }
            else{
                tmp1 = abs(sumY - sumX);
                DEBUG (3, "second attept Y - X = %"PRIu64"\n", tmp1);
            }
            uint64_t tmp2 = N;
            uint64_t tmp3 = 0;

            DEBUG (2, "tmp1 %"PRIu64"\ttmp2 %"PRIu64"\n", tmp1, tmp2);
            while (tmp1 && tmp2)
            {
                tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
                DEBUG (3, "tmp1 %"PRIu64"\ttmp2 %"PRIu64"\n", tmp1, tmp2);
            }

            if (tmp1 > 1 ){
                DEBUG(2, "solution candidate %"PRIu64"\n", tmp1);
                if (tmp1 == p || tmp1 == q){
                    DEBUG(1, "find p = %"PRIu64"\n", tmp1);
                    return tmp1;
                }
            } else if (tmp2 > 1 ) {
                DEBUG(2, "solution candidate %"PRIu64"\n", tmp2);
                if (tmp2 == p || tmp2 == q){
                    DEBUG(1, "find p = %"PRIu64"\n", tmp2);
                    return tmp2;
                }
            }
        }
        ERROR ("no solution ")
        return 0;

    } else {
        ERROR ("bad iterator size")
        return 0;
    }
}


int main (int argc, char *argv[])
{

    uint64_t p;
    uint64_t q;

    int p_idx;
    int q_idx;
    if (argc == 3)
    {

        p_idx = atol(argv[1]);
        q_idx = atol(argv[2]);
        DEBUG (2,"p_idx=%d\t", p_idx);
        DEBUG (2,"q_idx=%d\n", q_idx);
    }
    else {
        printf("USAGE: %s p q\n", argv[0]);
    }
    // return 0;
//*********  test1  **************
    // p = prime[28];
    // q = prime[36];// found 1 element in matrix
//********************************

//*********  test2  **************
    // p = prime[35];
    // q = prime[52];
//********************************

// *********  test3  **************
    // p = prime[35];
    // q = prime[53];
//********************************
    p = prime[p_idx];
    q = prime[q_idx];

    uint64_t N = p * q; //15347;
    uint64_t sqrt_N = 0;
    DEBUG (1,"p=%"PRIu64"\tq=%"PRIu64"\tp*q=N=%"PRIu64"\n", p, q, N);
    
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
        DEBUG (2,"sqrt of N = %"PRIu64"\n",sqrt_N );
    }

    // selecting the size of the factor base
    double size_B;
    size_B = exp (sqrt (log(N) * log(log(N))) );
    size_B = pow(size_B , sqrt(2)/4);
    DEBUG (2,"size of factor base size_B=%f\n", size_B);
    // case for test 2 
    //*********  test1  **************
    //********************************
    //*********  test2  **************
    size_B = size_B +2;
    // size_B = size_B +1;
    //********************************

    // selecting smooth primes 
    std::vector<uint64_t> p_smooth;
    DEBUG (2,"smooth numbers\n");

    //prime is 2 - special case 
    // Modulo 2, every integer is a quadratic residue.
    p_smooth.push_back(prime[2]);
    DEBUG (2,"%"PRIu64"\n", prime[2]);

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
            DEBUG (2,"%"PRIu64"\n", prime[i]);
        }
        // break;
    }

    if ((p_smooth.size() < size_B))
    {
        ERROR ("to small primes \n");
        return 0;
    }

    // selecting the sieving interval
    uint32_t M;
    M = exp (sqrt (log(N) * log(log(N))) );
    M = pow(M , 3*sqrt(2)/4);
    DEBUG (1,"The sieving interval M=%"PRIu32"\n", M);


    // *** construct our sieve *** //
    std::vector<uint64_t> X;
    /* fill in  sqrt(N) + 1 sqrt(N) + 2  sqrt(N) + 3 .....*/
    for (uint64_t i = 0; i <= M; ++i)
    {
        // if ((sqrt_N+i) == 180)
            // continue;
        X.push_back(sqrt_N + i);
    }


    DEBUG (2,"\n");
    std::vector<uint64_t> Y;
    // fill in  (Xi)^2 - N 
    for (uint64_t i = 0; i < X.size(); ++i)
    {
        DEBUG (2,"X = %"PRIu64"\t",X[i]);
        Y.push_back(X[i]*X[i] - N);
        DEBUG (2,"Y = %"PRIu64"\t",Y[i]);
        DEBUG (2,"\n");
    }

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

    std::vector<uint64_t> smooth_num;
    std::vector<uint64_t> P1;
    std::vector<uint64_t> P11;
    for (int i = 0; i < V.size(); ++i)
    {
        int nul_flag = 0;
        // printf("V = %"PRIu64"\t",V[i]);
        if(V[i] == 1)
        {
            for (int j = 0; j < p_smooth.size(); ++j)
            {
                DEBUG (3,"%"PRIu64"\t", v_exp[i][j]);
                if ((v_exp[i][j] % 2 )!= 0)
                    nul_flag = 1;
            }
            DEBUG (3,"%"PRIu64"\n", Y[i]);
            if (nul_flag){
                smooth_num.push_back(i);
            }
            else
            {
                P1.push_back(i);
            }
        }
    }
    DEBUG (3,"\n");

    uint64_t found = 0;
    
    if (P1.size() > 0)
    {
        for (int i = 0; i <  P1.size(); ++i)
        {
            
            std::vector<uint64_t> tmp;
            tmp.push_back(P1[i]);
            found = euclid_gcd( X, Y, tmp, p, q, N);
            if (found)
                break;
        }
    }
    
    P1.clear();
    if (found)
    {
        return 0;
    }


    if (smooth_num.size()  < size_B + 1)
    {
        ERROR( "to small number of smooth numbbers\n");
        return 0; 
    }
    

    // just print exponent array
    // for (int i = 0; i < V.size(); ++i)
    // {
    //  for (int j = 0; j < p_smooth.size(); ++j)
    //  {
    //      printf("%"PRIu64"\t", v_exp[i][j]);
    //  }
    //  printf("\n");
    // }


    bin_matrix_t m1(smooth_num.size());
    for (int i = 0; i < smooth_num.size(); ++i)
    {
        // std::vector<uint64_t> tmp;
        m1.add(v_exp[ smooth_num[i]] );
        // for (int j = 0; j < v_exp[ smooth_num[i] ].size(); ++j)
        // {
        //  v_exp_mod2[i][j] = v_exp[ smooth_num[i] ][j] % 2;
        // }
    }
    m1.show();
    //##########################
    // just print exponent mod 2 array
    // for (int i = 0; i < v_exp_mod2.size(); ++i)
    // {
    //  for (int j = 0; j < v_exp_mod2[i].size(); ++j)
    //  {
    //      DEBUG (3,"%"PRIu64"\t", v_exp_mod2[i][j]);
    //  }
    //  printf("\n");
    // }

    // DEBUG (3,"\n");
    // DEBUG (3,"unit matrix\n");
    // // just print and set unit matrix 
    // for (int i = 0; i < unit_matrix.size(); ++i)
    // {
    //  for (int j = 0; j < unit_matrix[i].size(); ++j)
    //  {
    //      if(i == j)
    //          unit_matrix[i][j] = 1;
    //      else
    //          unit_matrix[i][j] = 0;

    //      DEBUG (3,"%"PRIu64"\t", unit_matrix[i][j]);
    //  }
    //  DEBUG (3,"\n");
    // }
    // ############################

    // exit(0);
    // // tern around our matrix
    // std::vector< std::vector<uint64_t> > v_exp_mod2_rev(p_smooth.size(), std::vector<uint64_t> (smooth_num.size()) );
    // for (int j = 0; j < v_exp_mod2.size(); ++j)
    // {
    //  for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
    //  {
    //      // printf("%"PRIu64"\t", v_exp_mod2[j][i]);
    //      v_exp_mod2_rev[i][j] = v_exp_mod2[j][i];
    //  }
    //  // printf("\n");
    // }


    // printf("\n");
    // for (int j = 0; j < v_exp_mod2_rev.size(); ++j)
    // {
    //  for (uint64_t i = 0; i <  v_exp_mod2_rev[j].size(); ++i)
    //  {
    //      printf("%"PRIu64"\t", v_exp_mod2_rev[j][i]);
    //  }
    //  printf("\n");
    // }


    // printf("tpp1 size %d\n", tpp1.size());
    int null_line = m1.make_upper_triangular();
    /******************************
    int col = 0;
    int line = 0;
    int null_line = -1;
    for (int i = 0; i < v_exp_mod2[0].size(); ++i)
    {
        int j;
        for (j = line; j < v_exp_mod2[0].size(); ++j)
        {
            if (v_exp_mod2[j][col] == 1)
            {
                break;
            }
        }
        if(j == v_exp_mod2.size() ){
            col++;
            continue;
        } 
        else if( j != line && j < v_exp_mod2[0].size())
        {
            // printf("i = %d j = %d\n", i, j);
            for (int k = 0; k < v_exp_mod2[0].size(); ++k)
            {

                // printf("p1 = %d\n", tpp1[i][k]);
                // printf("p2 = %d\n", tpp1[j][k]);
                std::swap(v_exp_mod2[line][k], v_exp_mod2[j][k]);
                std::swap(unit_matrix[line][k], unit_matrix[j][k]);
            }
        }
        for (int j = line+1; j < v_exp_mod2[0].size(); ++j)
        {
            if(v_exp_mod2[j][col] != 0)
            {
                for (int k = 0; k < v_exp_mod2[0].size(); ++k)
                // for (int k = col; k < v_exp_mod2[0].size(); ++k)
                {
                    v_exp_mod2[j][k] += v_exp_mod2[col][k];
                    v_exp_mod2[j][k] %= 2;

                    unit_matrix[j][k] += unit_matrix[col][k];
                    unit_matrix[j][k] %= 2;
                }
            }
            if ( std::find(v_exp_mod2[j].begin(), v_exp_mod2[j].end(), 1) == v_exp_mod2[j].end() )
            {
                DEBUG (1,"nULLL !!!!!!!!\n");
                DEBUG (3," smooth_num %"PRIu64"\t", smooth_num[j]);
                // P1.push_back(j);
                null_line = j;
                break;
            }
        }

        if (null_line != -1)
            break;

        DEBUG (3,"##########################################################################\n");
        DEBUG (3,"\n");
        for (int j = 0; j < v_exp_mod2.size(); ++j)
        {
            for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
            {
                DEBUG (3,"%"PRIu64"\t", v_exp_mod2[j][i]);
            }
            DEBUG (3,"\n");
        }
    
        DEBUG (3,"\n");
        DEBUG (3,"unit matrix\n");
        for (int j = 0; j < unit_matrix.size(); ++j)
        {
            for (uint64_t i = 0; i <  unit_matrix[j].size(); ++i)
            {
                DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
            }
            DEBUG (3,"\n");
        }
            col++;
            line++;
    
    }

    **********************************************************/

    m1.show();
    /***********************************
    DEBUG (3,"\n");
    for (int j = 0; j < v_exp_mod2.size(); ++j)
    {
        for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
        {
            printf("%"PRIu64"\t", v_exp_mod2[j][i]);
        }
        printf("\n");
    }

    DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int j = 0; j < unit_matrix.size(); ++j)
    {
        for (uint64_t i = 0; i <  unit_matrix[j].size(); ++i)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
        }
        DEBUG (3,"\n");
    }
    ************************************/

    if (null_line != -1)
    {
        for (uint64_t i = 0; i <  m1.unit_matrix[null_line].size(); ++i)
        {
            // printf("%"PRIu64"\t", unit_matrix[null_line][i]);
            if( m1.unit_matrix[null_line][i] == 1)
            {
                DEBUG (3,"num = %"PRIu64"\t", smooth_num[i]);
                DEBUG (3,"Y  = %"PRIu64"\n", Y[smooth_num[i]]);
                P11.push_back(smooth_num[i]);
            }
        }
    }

                    // P1.push_back(1);
//########################################################
    found = 0;
    found = euclid_gcd( X, Y, P11, p, q, N);

    P11.clear();
    if (found)
    {
        return 0;
    }
    //#################################

    return 0;
    std::vector< std::vector<uint64_t> > v_exp_mod2(smooth_num.size(), std::vector<uint64_t> (p_smooth.size()) );
    std::vector< std::vector<uint64_t> > unit_matrix(v_exp_mod2[0].size(), std::vector<uint64_t> (v_exp_mod2[0].size()) );

{

    int null_line = m1.make_lower_triangular();
    /******************************************
    // printf("tpp1 size %d\n", tpp1.size());
    int col = 0;
    int line = 0;
    int null_line = -1;
    for (int i = v_exp_mod2[0].size() -1 ; i >= 0; --i)
    {

        DEBUG (3," =============================== %d\n", i);
        if (v_exp_mod2[i][i] != 1)
        {
            ERROR("error %d\n", i);
            continue;
        }

        for (int j = i-1; j >= 0; --j)
        {
            if(v_exp_mod2[j][i] != 0)
            {
                for (int k = 0; k < v_exp_mod2[0].size(); ++k)
                // for (int k = col; k < v_exp_mod2[0].size(); ++k)
                {
                    v_exp_mod2[j][k] += v_exp_mod2[i][k];
                    v_exp_mod2[j][k] %= 2;

                    unit_matrix[j][k] += unit_matrix[i][k];
                    unit_matrix[j][k] %= 2;
                }
            }
            if ( std::find(v_exp_mod2[j].begin(), v_exp_mod2[j].end(), 1) == v_exp_mod2[j].end() )
            {
                DEBUG (3,"nULLL !!!!!!!!\n");
                // printf(" smooth_num %"PRIu64"\t", smooth_num[i]);
                // P1.push_back(j);
                null_line = j;
                break;
            }
        }

    if (null_line != -1)
        break;

    DEBUG (3,"##########################################################################\n");
    DEBUG (3,"\n");
    for (int j = 0; j < v_exp_mod2.size(); ++j)
    {
        for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
        {
            DEBUG (3,"%"PRIu64"\t", v_exp_mod2[j][i]);
        }
        DEBUG (3,"\n");
    }

        DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int j = 0; j < unit_matrix.size(); ++j)
    {
        for (uint64_t i = 0; i <  unit_matrix[j].size(); ++i)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
        }
        DEBUG (3,"\n");
    }
        // col++;
        // line++;

    }

    *************************************************/

    m1.show();
    /******************************************
    DEBUG (3,"\n");
    for (int j = 0; j < v_exp_mod2.size(); ++j)
    {
        for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
        {
            DEBUG (3,"%"PRIu64"\t", v_exp_mod2[j][i]);
        }
        DEBUG (3,"\n");
    }

    DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int j = 0; j < unit_matrix.size(); ++j)
    {
        for (uint64_t i = 0; i <  unit_matrix[j].size(); ++i)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
        }
        DEBUG (3,"\n");
    }
    *************************************************/
    if (null_line != -1)
    {
        for (uint64_t i = 0; i <  m1.unit_matrix[null_line].size(); ++i)
        {
            // printf("%"PRIu64"\t", unit_matrix[null_line][i]);
            if( m1.unit_matrix[null_line][i] == 1)
            {
                DEBUG (2,"num = %"PRIu64"\t", smooth_num[i]);
                DEBUG (2,"Y  = %"PRIu64"\n", Y[smooth_num[i]]);
                P11.push_back(smooth_num[i]);
            }
        }
    }

// exit (0);

}



                // P1.push_back(1);
//########################################################
    found = 0;
    found = euclid_gcd( X, Y, P11, p, q, N);

    P1.clear();
    if (found)
    {
        return 0;
    }
    //#################################

    printf("\n");
    printf("exit\n");
    exit (0);

    
    for (int j = v_exp_mod2.size() -1 ; j > 0; --j)
    {
        uint64_t i;
        for (i = 0; i <  v_exp_mod2[j].size(); ++i)
        {
            if (v_exp_mod2[j][i] != 0)
                break;
        }

        if (i == v_exp_mod2[j].size())
            continue;

        for (int k = j-1 ; k >= 0; --k)
        {
            if (v_exp_mod2[k][i])
            {
                for (int z = 0; z < v_exp_mod2[0].size(); ++z)
                {
                    v_exp_mod2[k][z] += v_exp_mod2[j][z];
                    v_exp_mod2[k][z] %= 2;
                }
            }
        }
    }



    printf("\n");

    for (int j = 0; j < v_exp_mod2.size(); ++j)
    {
        for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
        {
            printf("%"PRIu64"\t", v_exp_mod2[j][i]);
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



    for (int j = 0; j < v_exp_mod2.size(); ++j)
    {
        int count = 0;
        int num = 0;
        std::vector<uint64_t> tmp;
        for (uint64_t i = 0; i <  v_exp_mod2[j].size(); ++i)
        {
            // printf("%"PRIu64"\t", v_exp_mod2[j][i]);
            if (v_exp_mod2[j][i] == 1)
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
                printf("%d-line  count %d\n", __LINE__, count);
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
                                printf("tmp %"PRIu64"\t X_exp[i][tmp[f]]%"PRIu64"\n", tmp[f], X_exp[i][tmp[f]]);
                            }
                            sum %= 2;
                            printf("%d-line  sum %d\n", __LINE__, sum);

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

            printf("---------\n");
        for (int j = 0; j < X_exp.size(); ++j)
        {
            for (uint64_t i = 0; i <  X_exp[j].size(); ++i)
            {
                printf("%"PRIu64"\t", X_exp[j][i]);
            }
            printf("\n");
        }
        // printf("\n");
    }

    //  for (int i = 0; i <  smooth_num.size(); ++i)
    // {
    //  printf("-----%"PRIu64"\n", Y[smooth_num[i]]);
    
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
    //  for (int i = 0; i <  P1.size(); ++i)
    // {
    //  printf("-----%"PRIu64"\n", P1[i]);
    
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





    // for (int i = 0; i < v_exp_mod2[0].size(); ++i)
    // {
    //  if (v_exp_mod2[v_exp_mod2.size()][i] == 0)
            
    // }

    exit(0);
}

