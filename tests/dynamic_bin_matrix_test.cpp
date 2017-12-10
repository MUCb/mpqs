#define BOOST_TEST_MODULE Bin Matrix Test
#include <boost/test/included/unit_test.hpp> 

#include "dynamic_bin_matrix.h"

int showDebugMsg = 4;
/*
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
    BOOST_TEST(m1.filled == 0);
}


BOOST_AUTO_TEST_CASE(test_3) 
{
    int i = 1;
    bin_matrix_t m1(5);
    std::vector<uint64_t> v_exp(5);

    v_exp = {1,1,1,1,1};

    BOOST_TEST(m1.filled == 0); 
    BOOST_TEST(m1.add_row(v_exp) == 1);
    BOOST_TEST(m1.filled == 1);
    m1.show();
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
    m1.show();
}

const int matrix_size = 5;
bin_matrix_t m1(matrix_size);

BOOST_AUTO_TEST_CASE(test_5) 
{
    std::vector< std::vector<uint64_t> > v_exp(matrix_size + 4, std::vector<uint64_t> (matrix_size));
    std::vector< std::vector<uint64_t> > v_exp1(1, std::vector<uint64_t> (matrix_size + 1));

    v_exp[0] = {1,1,1,1,1};
    v_exp[1] = {0,0,0,1,1};
    v_exp[2] = {1,1,1,1,0};
    v_exp[3] = {0,0,1,1,1};
    v_exp[4] = {1,1,0,1,1};
    v_exp[5] = {1,1,0,1,0};
    v_exp[6] = {1,1,0,0,0};
    v_exp[7] = {1,1,0,0,0};
    v_exp[8] = {1,1,0,0,0};

    v_exp1[0] = {1,1,1,1,1,1};

    for (int i = 0; i < matrix_size+4; ++i) {
        if(i == matrix_size + 1)
            BOOST_TEST(m1.add_row(v_exp1[0]) == 0);
        else
            BOOST_TEST(m1.add_row(v_exp[i]) == 1);
    }
    BOOST_TEST(m1.filled == 8);
    m1.show();
}



BOOST_AUTO_TEST_CASE(test_6) 
{
    // m1.show();
    BOOST_TEST(m1.delete_row(3) == 1);
    // m1.show();
}

BOOST_AUTO_TEST_CASE(test_7) 
{

    for (int i = matrix_size +1; i >= 0; i--) {
        BOOST_TEST(m1.delete_row(i) == 1);
    }
    BOOST_TEST(m1.delete_row(1) == 0);
}

const int matrix_size_10 = 10;
bin_matrix_t m2(matrix_size_10);

BOOST_AUTO_TEST_CASE(test_8) 
{
    std::vector< std::vector<uint64_t> > v_exp(4, std::vector<uint64_t> (matrix_size_10));
    v_exp[0] = {1,1,1,1,1,1,1,1,1,1};
    v_exp[1] = {0,0,0,0,0,0,0,0,1,0};
    v_exp[2] = {0,0,0,0,0,0,0,0,1,1};
    v_exp[3] = {0,0,1,1,1};
    // v_exp[4] = {1,1,0,1,1};
    // v_exp[5] = {1,1,0,1,0};



    for (int i = 0; i < 3; ++i) {
        BOOST_TEST(m2.add_row(v_exp[i]) == 1);
    }

    m2.make_upper_triangular();
    BOOST_TEST(m2.matrix[2][8] == 0);
}
*/

BOOST_AUTO_TEST_CASE(test_10) 
{
    const int matrix_size = 5;
    bin_matrix_t m1(matrix_size);
     std::vector< std::vector<uint64_t> > v_exp(matrix_size + 2, std::vector<uint64_t> (matrix_size));
     v_exp[0] = {0,1,1,1,1};
     v_exp[1] = {0,0,0,1,1};
     v_exp[2] = {1,1,1,1,0};
     v_exp[3] = {0,0,1,0,0};
     v_exp[4] = {1,1,0,1,1};
     v_exp[5] = {1,1,0,1,0};

     for (int i = 0; i < matrix_size+1; ++i) {
        BOOST_TEST(m1.add_row(v_exp[i]) == 1);
        m1.show();
        m1.make_upper_triangular_static();
     }

}


// BOOST_AUTO_TEST_CASE(test_11) 
// {

//     printf("\n\n\n\n\n");
//     std::vector< std::vector<uint64_t> > v_exp(matrix_size + 2, std::vector<uint64_t> (matrix_size));
//     v_exp[0] = {1,1,1,1,1};
//     v_exp[1] = {0,1,0,1,1};
//     v_exp[2] = {0,0,1,1,0};
//     v_exp[3] = {0,0,0,1,1};
//     v_exp[4] = {0,0,0,0,1};
//     v_exp[5] = {1,1,0,1,0};

//     for (int i = 0; i < matrix_size+1; ++i) {
//         BOOST_TEST(m1.add_row(v_exp[i]) == 1);
//     }

//     BOOST_TEST( m1.make_lower_triangular() == -1);
//     // m1.show();
//     for (int i = matrix_size; i >= 0; i--) {
//         BOOST_TEST(m1.delete_row(i) == 1);
//     }
// }



// BOOST_AUTO_TEST_CASE(test_12) 
// {

//     std::vector< std::vector<uint64_t> > v_exp(matrix_size + 2, std::vector<uint64_t> (matrix_size));
//     v_exp[0] = {1,1,1,1,1};
//     v_exp[1] = {0,1,0,1,1};
//     v_exp[2] = {0,0,0,1,0};
//     v_exp[3] = {0,0,0,1,1};
//     v_exp[4] = {0,0,0,0,1};
//     v_exp[5] = {1,1,0,1,0};

//     for (int i = 0; i < matrix_size+1; ++i) {
//         BOOST_TEST(m1.add_row(v_exp[i]) == 1);
//     }

//     BOOST_TEST( m1.make_lower_triangular() == 2);
//     // m1.show();
//     for (int i = matrix_size; i >= 0; i--) {
//         BOOST_TEST(m1.delete_row(i) == 1);
//     }
// }


// BOOST_AUTO_TEST_CASE(test_13) 
// {

//     printf("\n\n\n\n\n");
//     std::vector< std::vector<uint64_t> > v_exp(matrix_size + 2, std::vector<uint64_t> (matrix_size));
//     v_exp[0] = {1,1,1,1,1};
//     v_exp[1] = {0,1,0,1,1};
//     v_exp[2] = {1,1,0,1,0};
//     v_exp[3] = {1,0,1,1,1};
//     v_exp[4] = {0,1,0,0,1};
//     v_exp[5] = {1,1,0,1,0};

//     for (int i = 0; i < matrix_size+1; ++i) {
//         BOOST_TEST(m1.add_row(v_exp[i]) == 1);
//     }

//     m1.resolve_matrix();
//     // m1.show();
//     for (int i = matrix_size; i >= 0; i--) {
//         BOOST_TEST(m1.delete_row(i) == 1);
//     }
// }
