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
    int collumn_size;
    int row_size;
    int unit_matrix_size;
    int filled;
    bin_matrix_t(int size);
    bin_matrix_t();
    void init_unit(void);
    void show(void);
    int  make_upper_triangular(void);
    int  make_lower_triangular(void);
    // int m_size(void);
    void add_row(std::vector<uint64_t> v1);
    void delete_row(int iter);
    void count_unit_num( void );
    int max_unit_num(std::vector<uint64_t> selected_row);
    int resolve_matrix( void);
};

bin_matrix_t::bin_matrix_t(){
}

bin_matrix_t::bin_matrix_t(int size) : matrix(size + 1 , std::vector<uint64_t> (size)), 
                                unit_matrix(size, std::vector<uint64_t> (size)),
                                unit_num(size + 1),
                                collumn_size(size),
                                row_size(size + 1),
                                unit_matrix_size(size),
                                filled(0)
{
    init_unit();
}

// int bin_matrix_t::m_size(void)
// {
//     return rasize;
// }

void bin_matrix_t::init_unit(void)
{
    // don't feel the last row
    for (int row = 0; row < unit_matrix_size; ++row)
    {
        unit_num[row] = 0;
        for (int col = 0; col < unit_matrix; ++col)
        {
            if(row == col)
                unit_matrix[row][col] = 1;
            else
                unit_matrix[row][col] = 0;

            DEBUG (4,"%ld\t", unit_matrix[row][col]);
        }
        DEBUG (4,"\n");
    }
}


void bin_matrix_t::show(void){
        // just print exponent mod 2 array
    DEBUG (3,"matrix\n");
    for (int row = 0; row < row_size; ++row)
    {
        for (int col = 0; col < collumn_size; ++col)
        {
            DEBUG (3,"%lu\t", matrix[row][col]);
        }
        printf("\n");
    }

    DEBUG (3,"\n");
    DEBUG (3,"unit matrix\n");
    for (int row = 0; row < unit_matrix_size; ++row)
    {
        for (uint64_t col = 0; col <  unit_matrix_size; ++col)
        {
            DEBUG (3,"%"PRIu64"\t", unit_matrix[row][col]);
        }
        DEBUG (3,"\n");
    }
    DEBUG (3,"\n");
}

void bin_matrix_t::add_row(std::vector<uint64_t> row_v)
{
    // DEBUG(3, "%s %d \n",__func__, __LINE__);
    if (filled < row_size){
        // DEBUG(3, "%s %d \n",__func__, __LINE__);
        for (int col = 0; col < row_v.size() && col < collumn_size; ++col) {
            // DEBUG(3, "%s %d \n",__func__, __LINE__);
            matrix[filled][col] = row_v[col] % 2;
            // DEBUG(3, "%s %d \n",__func__, __LINE__);
        }
        // DEBUG(3, "%s %d \n",__func__, __LINE__);
        filled++;
    }
    // DEBUG(3, "%s %d filled %d\n",__func__, __LINE__, filled);
}

void bin_matrix_t::delete_row(int row_number)
{
    if (filled > 0){
        DEBUG(4, "%s %d\n",__func__, __LINE__);
        for (int row = row_number; row < unit_matrix_size  ; ++row)
        {
            DEBUG(4, "%s %d \n",__func__, __LINE__);
            for (int col = 0; col < unit_matrix_size; ++col)
            {
                DEBUG(4, "%s %d \n",__func__, __LINE__);
                if (row == (size ))
                    matrix[row][col] = 0;
                else
                matrix[row][col] = matrix[row+1][col];
            }
            
        }
        DEBUG(4, "%s %d \n",__func__, __LINE__);
        filled--;
        DEBUG(4, "%s %d filled %d\n",__func__, __LINE__, filled);
    }
}



int  bin_matrix_t::make_upper_triangular(void)
{
    int current_col = 0;
    int current_row = 0;
    int null_line = -1;
    for (int i = 0; i < unit_matrix_size ; ++i)
    {

        int row_nonnull;
        // find first non zero value. it will be in row.
        for (row_nonnull = current_row; row_nonnull < unit_matrix_size; ++row_nonnull)
        {
            if (matrix[row_nonnull][current_col] == 1)
                break;
        }

        DEBUG (3,"row_nonnull=%d current_row=%d size=%d current_col=%d\n", row_nonnull, current_row, (size-1), current_col);

        // row should be less then unit_matrix_size , otherwise all value are zero
        if(row_nonnull == unit_matrix_size ){
            ERROR ("We havn't find values in column %d \n", current_col);
            current_col++;
            continue;
        } else if( row_nonnull > current_row && row_nonnull < unit_matrix_size) {
            DEBUG(3, "i = %d row_nonnull = %d\n", i, row_nonnull);
            matrix[row_nonnull].swap(matrix[current_row]);
            unit_matrix[row_nonnull].swap(unit_matrix[current_row]);
        }

        // remove all value under the first one
        for (int row = current_row + 1; row < unit_matrix_size; ++row) {
            if(matrix[row][current_col] != 0) {
                // DEBUG(3, "CHAECK r = %d row=%d\n", r, row);
                // show();
                for (int col = 0; col < unit_matrix_size; ++col) {
                    
                    // DEBUG(3, "matrix r = %d c=%d m=%ld\n", r, c, matrix[r][c]);
                    matrix[row][col] += matrix[current_row][col];
                    matrix[row][col] %= 2;
                    // DEBUG(3, "matrix r = %d c=%d m=%ld\n", r, c, matrix[r][c]);

                    unit_matrix[row][col] += unit_matrix[current_row][col];
                    // unit_matrix[j][k] %= 2;
                }
            }

            // show();
            if ( std::find(matrix[row].begin(), matrix[row].end(), 1) == matrix[row].end() ) {
                // if (flag_n == 1) {
                //     DEBUG (1,"zero r=%d\n", r);
                //     matrix[r][size-1] = 1;
                //     flag_n = 0;
                //     null_line = (-r)-10;
                //     break;
                // } else {
                    DEBUG (1,"nULLL upper j=%d coll=%d\n", row, current_col);
                    // for (int c = 0; c < size-1; ++c) {
                        // unit_matrix[size - 1][c] += unit_matrix[r][c];
                    // }
                    DEBUG (3," smooth_num \n");
                    // P1.push_back(j);
                    null_line = row;
                    break;
                    
                // }
            }
            // show();
            // if (flag_n == 1) {
                // matrix[r][size-1] = 1;
            // }
        }

        if (null_line != -1)
            break;
        show();
            current_col++;
            current_row++;
    
    }
    return null_line;
}

void bin_matrix_t::count_unit_num( void )
{
    for (int row = 0; row < unit_matrix_size; ++row)
    {
        unit_num[row] = 0;
        for (int cal = 0; cal < size; ++cal)
        {
            if (matrix[row][cal] == 1){
                unit_num[row] += 1;
            }
        }
    }
}

int bin_matrix_t::max_unit_num(std::vector<uint64_t> selected_row)
{
    count_unit_num();
    int max_unit = 0;
    int max_iter = 0;
    for (int iter = 0; iter < unit_matrix_size; ++iter)
    {
        printf("%lu\t", selected_row[iter]);
        if (selected_row[iter] == 1){
            if (unit_num[iter] > max_unit){
                max_unit = unit_num[iter];
                max_iter = iter;
            }
        }
    }
    // printf("max %d\n", max_unit);
    printf("\n");
    return max_iter;
}



int  bin_matrix_t::make_lower_triangular(void) 
{
    // printf("tpp1 size %d\n", tpp1.size());
    int null_line = -1;
    for (int i = unit_matrix_size ; i > 0; --i)
    {
        if (matrix[i][i] != 1) {
            ERROR("we have zero value in main diagonal, line: %d\n", i);
            continue;
        }

        for (int row = i-1; row >= 0; --row)
        {
            DEBUG(3, "DEBUG row=%d\n", row);
            if(matrix[row][i] != 0)
            {
                DEBUG(3, "DEBUG1\n");
                for (int col = 0; col < size; ++col) {
                    matrix[row][col] += matrix[i][col];
                    matrix[row][col] %= 2;

                    unit_matrix[row][col] += unit_matrix[i][col];
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
                    /   /     unit_matrix[size -1][c] += unit_matrix[r][c];
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
            m1.add_row(v_exp[ smooth_num[i]]);
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
            m2.delete_row(max_i);
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
        m2.delete_row(max_i);
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
            m2.delete_row(max_i);
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
    #define NEGATIVE_SIGN    0 // need to change the sign name !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    #define FIRST_VALUE    1
    // v_exp[i].size()-1
    for (int y_number = 0; y_number < v_exp.size(); ++y_number)
    {
        if(Y[y_number] < 0 )
            v_exp[y_number][NEGATIVE_SIGN] = 1;
    }

    for (   int smooth_iter = 0, exponent_num = FIRST_VALUE ; 
                smooth_iter < p_smooth.size(); 
                smooth_iter++, exponent_num++)
    {
        for (int y_num = 0; y_num < M; ++y_num)
        {
            if(V[y_num] == -1 || V[y_num] == 1)
                continue;

            long int tmp;
            do{
                tmp = V[y_num] % p_smooth[smooth_iter];
                DEBUG (2,"v = %10li\t",V[y_num]);
                DEBUG (2,"p_smooth = %li\t",p_smooth[smooth_iter]);
                DEBUG (2,"tmp = %li\n",tmp);
                if(tmp == 0){
                    V[y_num] = V[y_num] / p_smooth[smooth_iter];
                    v_exp[y_num][exponent_num] += 1; 
                }
            } while (tmp == 0);
        }
        // break;
    }
    std::vector<int> smooth_num;
    std::vector<long> solution_candidates_number;
    // std::vector<uint64_t> P11;
    for (int y_num = 0; y_num < V.size(); ++y_num)
    {
        int null_flag = 1;
        // printf("V = %"PRIu64"\t",V[i]);
        if(V[y_num] == 1 || V[y_num] == -1)
        {
            for (   int exponent_num = FIRST_VALUE;
                        exponent_num < v_exp[y_num].size(); 
                        exponent_num++ )
            {
                DEBUG (3,"%ld\t", v_exp[y_num][exponent_num]);
                if ((v_exp[y_num][exponent_num] % 2 )!= 0)
                    null_flag = 0;
            }
            DEBUG (3,"%ld\n", Y[y_num]);
            // skip negative value !!!!
            if (null_flag && V[y_num] > 0) {
                solution_candidates_number.push_back(y_num);
            } else {
                smooth_num.push_back(y_num);
            }
        }
    }
    DEBUG (3,"\n");

    uint64_t found = 0;
    
    if (solution_candidates_number.size() > 0)
    {
        DEBUG (3,"%s:%d\n", __func__, __LINE__);
        for (int i = 0; i <  solution_candidates_number.size(); ++i)
        {
            DEBUG (3,"check %ld\n", Y[solution_candidates_number[i]]);

            if ( Y[solution_candidates_number[i]] > 0 ){

                std::vector<int64_t> tmp;
                tmp.push_back(solution_candidates_number[i]);
                found = euclid_gcd( X, Y, tmp, p, q, N);
                if (found)
                    break;
            }
        }
    }
    solution_candidates_number.clear();
    if (found)
    {
        return 0;
    }

    return 0;
    


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

    // find_solution(m1, smooth_num_back, smooth_num, v_exp, X, Y, p, q, N);

    printf("\n");
    printf("exit\n");
    exit (0);

    return 0;
}

