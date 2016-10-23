#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>


#include <unistd.h>

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

bin_matrix_t::bin_matrix_t(int num) : matrix(num , std::vector<uint64_t> (num)), 
                                unit_matrix(num , std::vector<uint64_t> (num)),
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
    // don't feel the last raw
    for (int r = 0; r < size-1; ++r)
    {
        unit_num[r] = 0;
        for (int c = 0; c < size; ++c)
        {
            if(r == c)
                unit_matrix[r][c] = 1;
            else
                unit_matrix[r][c] = 0;

            DEBUG (4,"%ld\t", unit_matrix[r][c]);
        }
        DEBUG (4,"\n");
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
    for (int j = 0; j < size; ++j)
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
    if (filled < size){
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
        DEBUG(4, "%s %d\n",__func__, __LINE__);
        for (int i = iter; i < size -1  ; ++i)
        {
            DEBUG(4, "%s %d \n",__func__, __LINE__);
            for (int j = 0; j < size; ++j)
            {
                DEBUG(4, "%s %d \n",__func__, __LINE__);
                if (i == (size ))
                    matrix[i][j] = 0;
                else
                matrix[i][j] = matrix[i+1][j];
            }
            
        }
        DEBUG(4, "%s %d \n",__func__, __LINE__);
        filled--;
        DEBUG(4, "%s %d filled %d\n",__func__, __LINE__, filled);
    }
}



int  bin_matrix_t::make_upper_triangular(void)
{
    int col = 0;
    int raw = 0;
    int null_line = -1;
    for (int i = 0; i < size -1 ; ++i)
    {

        int r;
        // find first non zero value. it will be in r.
        for (r = raw; r < size -1; ++r)
        {
            if (matrix[r][col] == 1)
            {
                break;
            }
        }

        DEBUG (3,"r=%d raw=%d size=%d coll=%d\n", r, raw, (size - 1), col);

        // r should be less then (size -2 ), otherwise all value are zero
        if(r == (size - 1) ){
            col++;
            continue;
        } else if( r != raw && r < (size - 2)) {
            DEBUG(3, "i = %d r = %d\n", i, r);
            for (int c = 0; c < size; ++c)
            {
                // printf("p1 = %d\n", tpp1[i][k]);
                // printf("p2 = %d\n", tpp1[j][k]);
                std::swap(matrix[raw][c], matrix[r][c]);
                std::swap(unit_matrix[raw][c], unit_matrix[r][c]);
            }
        }

        for (int r = raw + 1; r < (size - 1); ++r) {
            if(matrix[r][col] != 0) {
                // DEBUG(3, "CHAECK r = %d raw=%d\n", r, raw);
                // show();
                for (int c = 0; c < size; ++c) {
                    
                    // DEBUG(3, "matrix r = %d c=%d m=%ld\n", r, c, matrix[r][c]);
                    matrix[r][c] += matrix[raw][c];
                    matrix[r][c] %= 2;
                    // DEBUG(3, "matrix r = %d c=%d m=%ld\n", r, c, matrix[r][c]);

                    unit_matrix[r][c] += unit_matrix[raw][c];
                    // unit_matrix[j][k] %= 2;
                }
            }
            // show();
            int flag_n = 0;
            if (matrix[r][size-1] == 1) {
                flag_n = 1;
                matrix[r][size-1] = 0;
            }

            // show();
            if ( std::find(matrix[r].begin(), matrix[r].end(), 1) == matrix[r].end() ) {
                if (flag_n == 1) {
                    DEBUG (1,"zero r=%d\n", r);
                    matrix[r][size-1] = 1;
                    flag_n = 0;
                    null_line = (-r)-10;
                    break;
                } else {
                    DEBUG (1,"nULLL upper j=%d coll=%d\n", r, col);
                    // for (int c = 0; c < size-1; ++c) {
                        // unit_matrix[size - 1][c] += unit_matrix[r][c];
                    // }
                    DEBUG (3," smooth_num \n");
                    // P1.push_back(j);
                    null_line = r;
                    break;
                    
                }
            }
            // show();
            if (flag_n == 1) {
                matrix[r][size-1] = 1;
            }
        }

        if (null_line != -1)
            break;
        show();
            col++;
            raw++;
    
    }
    return null_line;
}

void bin_matrix_t::count_unit_num( void )
{
    for (int i = 0; i < (size -1); ++i)
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
    for (int i = 0; i < (size - 1); ++i)
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
    for (int i = size - 2 ; i >= 1; --i)
    {

        // DEBUG (3," =============================== %d\n", i);
        if (matrix[i][i] != 1)
        {
            ERROR("error %d\n", i);
            continue;
        }

        for (int r = i-1; r >= 0; --r)
        {
            DEBUG(3, "DEBUG r=%d\n", r);
            if(matrix[r][i] != 0)
            {
                DEBUG(3, "DEBUG1\n");
                for (int c = 0; c < size; ++c) {
                    matrix[r][c] += matrix[i][c];
                    matrix[r][c] %= 2;

                    unit_matrix[r][c] += unit_matrix[i][c];
                    // unit_matrix[r][c] %= 2;  // ???????
                }
            }

            int flag_n = 0;
            if (matrix[r][size-1] == 1) {
                flag_n = 1;
                matrix[r][size-1] = 0;
            }

            if ( std::find(matrix[r].begin(), matrix[r].end(), 1) == matrix[r].end() )
            {
                DEBUG (1,"zzzero\n");
                // show();
                if (flag_n == 1)
                {
                    DEBUG (1,"zzzero\n");
                    matrix[r][size-1] = 1;
                    flag_n = 0;
                    null_line = (-r)-10;
                    break;
                }
                else{
                    DEBUG (3,"nULLL lower %d\n", r);
                    // for (int c = 0; c < size; ++c) {
                    //     unit_matrix[size -1][c] += unit_matrix[r][c];
                    // }
                    DEBUG (3," smooth_num\n");
                    // P1.push_back(j);
                    null_line = r;
                    break;
                }
                show();
            }
            if (flag_n == 1) {
                matrix[r][0] = 1;
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
    DEBUG(2, "upper triangular\n");
    show();


    if (null_line != -1) {
        return null_line;
    }

    exit(0);

    null_line = make_lower_triangular();
    DEBUG(2, "lower triangular\n");
    show();

    if (null_line != -1) {
        return null_line;
    }

    printf(" last \n");
    for (int c = 0; c < size -2; ++c) {
        if (matrix[size - 1][c]  == 1) {
            for (int r = 0; r < size; ++r) {
                matrix[size - 1][r] += matrix[c][r];
                matrix[size - 1][r] %= 2;

                unit_matrix[size - 1][c] += unit_matrix[c][r];
                unit_matrix[size - 1][c] %= 2;
            }
        }
    }
    if(matrix[size-1][size-1] != 0 ) {
        ERROR("no resolv\n");
    } else{
        null_line = size -1;
    }
    printf(" last \n");
    
    return null_line;

}


//Euclid's Algorithm, Greatest Common Divisor
uint64_t euclid_gcd(const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const std::vector<int64_t>& iterator,
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
            DEBUG(2, "X %lu\tY %ld\n", X[iterator[j]], Y[iterator[j]]);
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
                DEBUG (3, "firtst attept Y + X = %ld\n", tmp1);
            }
            else{
                tmp1 = abs(sumY - sumX);
                DEBUG (3, "second attept Y - X = %ld\n", tmp1);
            }
            uint64_t tmp2 = N;
            uint64_t tmp3 = 0;

            DEBUG (2, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            while (tmp1 && tmp2)
            {
                tmp1 > tmp2 ? tmp1 = tmp1 % tmp2 : tmp2 = tmp2 % tmp1;
                DEBUG (3, "tmp1 %ld\ttmp2 %ld\n", tmp1, tmp2);
            }

            if (tmp1 > 1 ){
                DEBUG(2, "solution candidate %ld\n", tmp1);
                if (tmp1 == p || tmp1 == q){
                    DEBUG(1, "find p = %ld\n", tmp1);
                    return tmp1;
                }
            } else if (tmp2 > 1 ) {
                DEBUG(2, "solution candidate %ld\n", tmp2);
                if (tmp2 == p || tmp2 == q){
                    DEBUG(1, "find p = %ld\n", tmp2);
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
    if ((m1.size) == m1.filled)
        return count;

    DEBUG(4, "%s %d \n",__func__, __LINE__);
    for (int i = 0; i < smooth_num.size() && ((m1.size) != m1.filled); ++i) {
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
                    const std::vector<long>& X,
                    const std::vector<long>& Y,
                    const uint64_t &p,
                    const uint64_t &q,
                    const uint64_t &N)
{

    std::vector<int64_t> P11;
    int retval = fill_matrix(m2, smooth_num_back, v_exp);
    m2.show();
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


    if (null_line > -1)
    {
        for (uint64_t i = 0; i <  m1.m_size(); ++i)
        {
            printf("%ld\n", m1.unit_matrix[null_line][i]);
            if( m1.unit_matrix[null_line][i] > 0)
            {
                DEBUG (2,"num = %d\t", smooth_num[i]);
                // if (i == 0 )
                // {
                    // DEBUG (1,"Strange\n");
                    // continue;
                // } else
                // {
                    DEBUG (2,"Y  = %ld\n", Y[smooth_num[i]]);
                    P11.push_back(smooth_num[i]);
                // }
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
                ERROR("failed ");

        }
    }
    else if (null_line < -1)
    {
        int max_i = -(null_line + 10);
        // m2.show();
        m2.del(max_i);
        printf("===== %d \n", smooth_num_back[max_i]);
        smooth_num_back.erase(smooth_num_back.begin() + max_i);
        smooth_num.erase(smooth_num.begin() + max_i);

        null_line = find_solution(m2, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);
            DEBUG(3, "finish %d\n", null_line);
            if (null_line == 0)
                ERROR("failed ");
    }
    else
    {
            int max_i = 0;
            // printf(" debug\n");
            // printf(" debug\n");
            // max_i = m2.max_unit_num(m1.unit_matrix[null_line]);
            // printf(" debug\n");

            // printf(" iter %d\n",max_i );
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
                ERROR("failed ");
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
    // size_B = size_B + 2;
    // size_B = size_B +1;
    //********************************

    // selecting smooth primes 
    std::vector<long> p_smooth;
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
    std::vector<long> X;

    for (uint64_t i = M/2; i > 0; i = i - 1)
    {
        // if ((sqrt_N+i) == 180)
            // continue;
        X.push_back(sqrt_N - i);
        DEBUG (3,"X%"PRIu64" =%"PRIu64"\n",i, sqrt_N - i );
        // sleep(1000);
    }

    /* fill in  sqrt(N) + 1 sqrt(N) + 2  sqrt(N) + 3 .....*/
    for (uint64_t i = 0; i <= M/2; ++i)
    {
        // if ((sqrt_N+i) == 180)
            // continue;
        X.push_back(sqrt_N + i);
        DEBUG (3,"X%"PRIu64" =%"PRIu64"\n",i, sqrt_N + i );
    }



    DEBUG (2,"\n");
    std::vector<long> Y;
    // fill in  (Xi)^2 - N 
    for (uint64_t i = 0; i < X.size(); ++i)
    {
        DEBUG (2,"X = %"PRIu64"\t",X[i]);
        Y.push_back(X[i]*X[i] - N);
        DEBUG (2,"Y = %li\t",Y[i]);
        DEBUG (2,"\n");
    }
    // simple sieve 
    std::vector<long> V;
    V = Y;
    std::vector< std::vector<uint64_t> > v_exp(Y.size(), std::vector<uint64_t> (p_smooth.size() + 1)) ;

    // add sign to exponent matrix
    for (int i = 0; i < v_exp.size(); ++i)
    {
        if(Y[i] < 0 )
            v_exp[i][v_exp[i].size()-1] = 1;
    }

    for (int j = 0; j < p_smooth.size(); ++j)
    {
        for (int i = 0; i < M; ++i)
        {
            if(V[i] == -1 || V[i] == 1)
                continue;

            long int tmp;
            do{
                tmp = V[i] % p_smooth[j];
                DEBUG (2,"v = %10li\t",V[i]);
                DEBUG (2,"p_smooth = %li\t",p_smooth[j]);
                DEBUG (2,"tmp = %li\n",tmp);
                // if (tmp < 0 )
                // {
                //     tmp = p_smooth[j] + tmp;
                // }
                if(tmp == 0){
                    V[i] = V[i] / p_smooth[j];
                    v_exp[i][j] += 1; 
                }
            } while (tmp == 0);
        }
        // break;
    }

    std::vector<int> smooth_num;
    std::vector<long> P1;
    // std::vector<uint64_t> P11;
    for (int i = 0; i < V.size(); ++i)
    {
        int nul_flag = 0;
        // printf("V = %"PRIu64"\t",V[i]);
        if(V[i] == 1 || V[i] == -1)
        {
            for (int j = 0; j < (p_smooth.size()); ++j)
            {
                DEBUG (3,"%ld\t", v_exp[i][j]);
                if ((v_exp[i][j] % 2 )!= 0)
                    nul_flag = 1;
            }
            DEBUG (3,"%ld\n", Y[i]);
            if (nul_flag){
                    smooth_num.push_back(i);
            }
            else
            {
            // skip negative value !!!!
            if (V[i] == 1 )
                    P1.push_back(i);
            }
        }
    }
    DEBUG (3,"\n");

    uint64_t found = 0;
    
    if (P1.size() > 0)
    {
        DEBUG (3,"%s:%d\n", __func__, __LINE__);
        for (int i = 0; i <  P1.size(); ++i)
        {
            DEBUG (3,"check %ld\n", Y[P1[i]]);

            if ( Y[P1[i]] > 0 ){

                std::vector<int64_t> tmp;
                tmp.push_back(P1[i]);
                found = euclid_gcd( X, Y, tmp, p, q, N);
                if (found)
                    break;
            }
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
    bin_matrix_t m1(p_smooth.size() + 1);
    // m1.show();
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

