#define BOOST_TEST_MODULE GCD Test
#include <boost/test/included/unit_test.hpp> 

#include "greatest_common_divisor.h"

int showDebugMsg = 0;

BOOST_AUTO_TEST_CASE(test_1) 
{
    int i = 1;

    uint64_t p = 11;
    uint64_t q = 79;
    uint64_t N = p * q;
    uint64_t sqrt_N = trunc(sqrt(N)) + 1;

    // selecting the sieving interval
    uint32_t M;
    M = exp (sqrt (log(N) * log(log(N))) );
    M = pow(M , 3*sqrt(2)/4);

    std::vector<long> X;
    for (uint64_t i = M/2; i > 0; i = i - 1) {
        X.push_back(sqrt_N - i);
    }
    for (uint64_t i = 0; i <= M/2; ++i) {
        X.push_back(sqrt_N + i);
    }

    std::vector<long> Y;
    for (uint64_t i = 0; i < X.size(); ++i) {
        Y.push_back(X[i]*X[i] - N);
    }

    std::vector<int64_t> P11;
    P11.push_back(33);
    P11.push_back(39);

    euclid_gcd( X, Y, P11, p, q, N);

    BOOST_TEST(euclid_gcd( X, Y, P11, p, q, N) == 11); 
    // BOOST_TEST(i == 2);
}