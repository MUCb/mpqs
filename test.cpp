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
    BOOST_TEST(m1.unit_matrix_size == 5);
    BOOST_TEST(m1.filled == 0);
}


BOOST_AUTO_TEST_CASE(test_3) 
{
    int i = 1;
    bin_matrix_t m1(5);
    std::vector<uint64_t> v_exp(5);

    v_exp = {1,1,1,1,1};
 
    BOOST_TEST(m1.filled == 0); 
    m1.add_row(v_exp);
    BOOST_TEST(m1.filled == 1);
}


BOOST_AUTO_TEST_CASE(test_4) 
{
    const int matrix_size = 5;
    bin_matrix_t m1(matrix_size);
    std::vector< std::vector<uint64_t> > v_exp(matrix_size + 1, std::vector<uint64_t> (matrix_size));

    v_exp[0] = {1,1,1,1,1};
    v_exp[1] = {0,0,0,1,1};
    v_exp[2] = {1,1,1,1,0};
    v_exp[3] = {0,0,1,1,1};
    v_exp[4] = {1,1,0,1,1};
    v_exp[5] = {1,1,0,1,0};
 
 	for (int i = 0; i < matrix_size+1; ++i) {
	    BOOST_TEST(m1.add_row(v_exp[i]) == 1);
 	}
    BOOST_TEST(m1.filled == 6);
}

const int matrix_size = 5;
bin_matrix_t m1(matrix_size);

BOOST_AUTO_TEST_CASE(test_5) 
{
    std::vector< std::vector<uint64_t> > v_exp(matrix_size + 2, std::vector<uint64_t> (matrix_size));

    v_exp[0] = {1,1,1,1,1};
    v_exp[1] = {0,0,0,1,1};
    v_exp[2] = {1,1,1,1,0};
    v_exp[3] = {0,0,1,1,1};
    v_exp[4] = {1,1,0,1,1};
    v_exp[5] = {1,1,0,1,0};
    v_exp[6] = {1,1,0,0,0};
 
 	for (int i = 0; i < matrix_size+2; ++i) {
 		if(i == matrix_size + 1)
	 		BOOST_TEST(m1.add_row(v_exp[i]) == 0);
	 	else
	    	BOOST_TEST(m1.add_row(v_exp[i]) == 1);
 	}
    BOOST_TEST(m1.filled == 6);
}

BOOST_AUTO_TEST_CASE(test_6) 
{
 	for (int i = matrix_size; i >= 0; i--) {
 		if(i == matrix_size + 1)
	 		BOOST_TEST(m1.delete_row(i) == 0);
	 	else
	    	BOOST_TEST(m1.delete_row(i) == 1);
 	}
    BOOST_TEST(m1.filled == 0);
}

BOOST_AUTO_TEST_CASE(test_7) 
{
	std::vector< std::vector<uint64_t> > v_exp(matrix_size + 2, std::vector<uint64_t> (matrix_size));
    v_exp[0] = {1,1,1,1,1};
    v_exp[1] = {0,0,0,1,1};
    v_exp[2] = {1,1,1,1,0};
    v_exp[3] = {0,0,1,1,1};
    v_exp[4] = {1,1,0,1,1};
    v_exp[5] = {1,1,0,1,0};
 
 	for (int i = 0; i < matrix_size+1; ++i) {
	    	BOOST_TEST(m1.add_row(v_exp[i]) == 1);
 	}

	// m1.make_upper_triangular();
}
