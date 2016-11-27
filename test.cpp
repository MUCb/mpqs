#define BOOST_TEST_MODULE My Test 1
#include <boost/test/included/unit_test.hpp> 

#include "bin_matrix.h"

BOOST_AUTO_TEST_CASE(first_test) 
{
  int i = 1;
  BOOST_TEST(i); 
  // BOOST_TEST(i == 2);

  
}

BOOST_AUTO_TEST_CASE(test_2) 
{
    int i = 1;
    bin_matrix_t m1(5);
    BOOST_TEST(m1.collumn_size == 5); 
    BOOST_TEST(m1.row_size == 6);
}