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
    std::vector<int> unit_num;
    int size;
    int filled;
    bin_matrix_t(int num);
    bin_matrix_t();
    void init_unit(void);
    void show(void);
    void add(std::vector<uint64_t> v1);
    int  make_upper_triangular(void);
    int  make_lower_triangular(void);
    int m_size(void);
    void del(int iter);
    void count_unit_num( void );
    int max_unit_num(std::vector<uint64_t> unit_v);
    int resolve_matrix( void);
};

bin_matrix_t::bin_matrix_t(){
}

bin_matrix_t::bin_matrix_t(int num) : matrix(num + 1, std::vector<uint64_t> (num)), 
                                unit_matrix(num + 1, std::vector<uint64_t> (num)),
                                unit_num(num),
                                size(num),
                                filled(0)
{
    init_unit();
}

int bin_matrix_t::m_size(void)
{
    return size;
}

void bin_matrix_t::init_unit(void)
{
    for (int i = 0; i < size + 1; ++i)
    {
        unit_num[i] = 0;
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
    for (int i = 0; i < size + 1; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            DEBUG (3,"%"PRIu64"\t", matrix[i][j]);
        }
        printf("\n");
    }

    DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int j = 0; j < size +1; ++j)
    {
        for (uint64_t i = 0; i <  size; ++i)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[j][i]);
        }
        DEBUG (3,"\n");
    }
    DEBUG (3,"\n");
}

void bin_matrix_t::add(std::vector<uint64_t> v1)
{
    // DEBUG(3, "%s %d \n",__func__, __LINE__);
    if (filled < size + 1){
        // DEBUG(3, "%s %d \n",__func__, __LINE__);
        for (int j = 0; j < v1.size() && j < size; ++j)
        {
            // DEBUG(3, "%s %d \n",__func__, __LINE__);
            matrix[filled][j] = v1[j] % 2;
            // DEBUG(3, "%s %d \n",__func__, __LINE__);
        }
        // DEBUG(3, "%s %d \n",__func__, __LINE__);
        filled++;
    }
    // DEBUG(3, "%s %d filled %d\n",__func__, __LINE__, filled);
}

void bin_matrix_t::del(int iter)
{
    if (filled > 0){
        // DEBUG(3, "%s %d \n",__func__, __LINE__);
        for (int i = iter; i < size + 1 ; ++i)
        {
            // DEBUG(3, "%s %d \n",__func__, __LINE__);
            for (int j = 0; j < size && j < size; ++j)
            {
                // DEBUG(3, "%s %d \n",__func__, __LINE__);
                if (i == (size ))
                    matrix[i][j] = 0;
                else
                matrix[i][j] = matrix[i+1][j];
            }
            
        }
        // DEBUG(3, "%s %d \n",__func__, __LINE__);
        filled--;
        DEBUG(3, "%s %d filled %d\n",__func__, __LINE__, filled);
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

        DEBUG (3,"j=%d line=%d size=%d coll=%d\n", j, line, size, col);
        if(j == size ){
            col++;
            continue;
        }
        // else if (j < line){
            // line= j;
        // }
        else if( j != line && j < size)
        {
            printf("i = %d j = %d\n", i, j);
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
                // show();
                for (int k = 0; k < size; ++k)
                // for (int k = col; k < v_exp_mod2[0].size(); ++k)
                {
                    matrix[j][k] += matrix[line][k];
                    matrix[j][k] %= 2;

                    unit_matrix[j][k] += unit_matrix[line][k];
                    // unit_matrix[j][k] %= 2;
                }
            }
            // show();
            if ( std::find(matrix[j].begin(), matrix[j].end(), 1) == matrix[j].end() )
            {

                DEBUG (1,"nULLL upper j=%d coll=%d\n", j, col);
                for (int k = 0; k < size; ++k)
                {
                    unit_matrix[size][k] += unit_matrix[j][k];
                }
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

void bin_matrix_t::count_unit_num( void )
{
    for (int i = 0; i < size; ++i)
    {
        unit_num[i] = 0;
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] == 1){
                unit_num[i] += 1;
            }
        }
    }
}

int bin_matrix_t::max_unit_num(std::vector<uint64_t> unit_v)
{
    //  count_unit_num();
    // int max_un = 0;
    // int max_iter = 0;
    // for (int i = 0; i < size; ++i)
    // {
    //  printf("%lu\t", unit_v[i]);
    //  if (unit_v[i] == 1){

    //      if(max_un == 0){
    //          max_un = unit_num[i];
    //          max_iter = i;
    //      } else if (unit_num[i] < max_un){
    //          max_un = unit_num[i];
    //          max_iter = i;
    //      }
    //  }
    // }
    // // printf("max %d\n", max_un);
    // printf("\n");
    // return max_iter;


    count_unit_num();
    int max_un = 0;
    int max_iter = 0;
    for (int i = 0; i < size; ++i)
    {
        printf("%lu\t", unit_v[i]);
        if (unit_v[i] == 1){
            if (unit_num[i] > max_un){
                max_un = unit_num[i];
                max_iter = i;
            }
        }
    }
    // printf("max %d\n", max_un);
    printf("\n");
    return max_iter;
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
                DEBUG (3,"nULLL lower %d\n", j);
                for (int k = 0; k < size; ++k)
                {
                    unit_matrix[size][k] += unit_matrix[j][k];
                }
                // printf(" smooth_num %"PRIu64"\t", smooth_num[i]);
                // P1.push_back(j);
                null_line = j;
                break;
            }
        }

    if (null_line != -1)
        break;

    show();

    }
    return null_line;

}


int bin_matrix_t::resolve_matrix()
{
    std::vector<uint64_t> P11;
    uint64_t found = 0;

    show();
    int null_line = make_upper_triangular();
    show();


    if (null_line != -1)
    {
        return null_line;
    }

    null_line = make_lower_triangular();
    show();

    if (null_line != -1)
    {
        return null_line;
    }

    printf(" last \n");
    for (int k = 0; k < size; ++k)
    {  
        if (matrix[size][k]  == 1)
        {
            for (int i = 0; i < size; ++i)
                {
                    matrix[size][i] += matrix[k][i];
                    matrix[size][i] %= 2;

                    unit_matrix[size][k] += unit_matrix[k][i];
                    unit_matrix[size][k] %= 2;
                }
        }
    }
    null_line = size;
    
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





int fill_matrix(bin_matrix_t &m1, std::vector<int> &smooth_num, std::vector< std::vector<uint64_t> > &v_exp)
{
    int count = 0;

    // DEBUG(3, "%s %d \n",__func__, __LINE__);
    // DEBUG(3, "%s %d filled \n",__func__, m1.filled);
    // DEBUG(3, "%s %d size \n",__func__, m1.size);
    if ((m1.size + 1) == m1.filled)
        return count;

    DEBUG(3, "%s %d \n",__func__, __LINE__);
    for (int i = 0; i < smooth_num.size() && ((m1.size + 1) != m1.filled); ++i) {
        // DEBUG(3, "%s %d iteration\n",__func__, i);
        // DEBUG(3, "%s %d filled \n",__func__, m1.filled);
        // DEBUG(3, "%s %d size \n",__func__, m1.size);
        // DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num[i]);
        if (smooth_num[i] != -1) {
            // DEBUG(3, "%s %d added\n",__func__, smooth_num[i]);
            m1.add(v_exp[ smooth_num[i]]);
            smooth_num[i] = -1;
            // DEBUG(3, "%s %d =added\n",__func__, smooth_num[i]);
            count++;
        }
    }
    return count;
}



int find_solution (bin_matrix_t m2, 
                    std::vector<int> &smooth_num_back, 
                    std::vector<int> &smooth_num, 
                    std::vector< std::vector<uint64_t> > &v_exp,
                    const std::vector<uint64_t>& X,
                    const std::vector<uint64_t>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N)
{

    std::vector<uint64_t> P11;
    int retval = fill_matrix(m2, smooth_num_back, v_exp);

    // for (int i = 0; i < smooth_num_back.size() ; ++i) {
    //  DEBUG(3, "%s %d smooth_num \n",__func__, smooth_num_back[i]);
    // }

    bin_matrix_t m1 = m2;
    DEBUG(2, "%d added\n", retval);
    if (retval == 0 )
        return 0;


    int null_line = m1.resolve_matrix();
    // m1.show();
    // return 0;

    if (null_line != -1)
    {
        for (uint64_t i = 0; i <  m1.m_size(); ++i)
        {
            // printf("%"PRIu64"\t", unit_matrix[null_line][i]);
            if( m1.unit_matrix[null_line][i] == 1)
            {
                DEBUG (2,"num = %d\t", smooth_num[i]);
                // DEBUG (2,"Y  = %"PRIu64"\n", Y[smooth_num[i]]);
                P11.push_back(smooth_num[i]);
            }
        }
        DEBUG (2,"\n");

        int found = 0;
        found = euclid_gcd( X, Y, P11, p, q, N);
        // printf("found %lu\n", found);
        m1.show();
        if (found) {
            return null_line;
        }
        else {

            int max_i = 0;
            max_i = m2.max_unit_num(m1.unit_matrix[null_line]);

            printf(" iter %d\n",max_i );
            m2.show();
            m2.del(max_i);
            printf("===== %d \n", smooth_num_back[max_i]);
            smooth_num_back.erase(smooth_num_back.begin() + max_i);
            smooth_num.erase(smooth_num.begin() + max_i);
            m2.show();


            // return find_solution(m2, smooth_num_back);
            null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == 0)
                ERROR("no solution");

        }
    }

    return null_line;
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
    size_B = size_B + 2;
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
    // M *= 2;
    // M += 20;
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

    std::vector<int> smooth_num;
    std::vector<uint64_t> P1;
    // std::vector<uint64_t> P11;
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

    std::vector<int> smooth_num_back = smooth_num;
    bin_matrix_t m1(p_smooth.size());

    // for (int i = 0; i < m1.m_size() + 1; ++i)
    // {
    //     // unit_num[i] = 0;
    //     m1.filled++;
    //     for (int j = 0; j < m1.m_size(); ++j)
    //     {
    //         if(i == j)
    //             m1.matrix[i][j] = 1;
    //         else
    //             m1.matrix[i][j] = 0;

    //         // DEBUG (3,"%"PRIu64"\t", unit_matrix[i][j]);
    //     }
    //     // DEBUG (3,"\n");
    // }
    // m1.filled++;
    // m1.matrix[6][1] = 1;
    // m1.matrix[6][4] = 1;
    // m1.show();
    // int null_line = m1.resolve_matrix();
    // m1.show();
    // printf("null_line %d\n",null_line );
    // m1.show();

    find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);

    printf("\n");
    printf("exit\n");
    exit (0);

    return 0;

}

