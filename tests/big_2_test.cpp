#define BOOST_TEST_MODULE Big Numbers Test
#include <boost/test/included/unit_test.hpp> 

#include "big_2.h"
#include <iostream>  
int showDebugMsg = 1;
#if 0
BOOST_AUTO_TEST_CASE(test_1) 
{
    big i(3203244);
    std::cout << i << "\n";

}

BOOST_AUTO_TEST_CASE(test_2) 
{
    big i("3203244");
    std::cout << i << "\n";
}

BOOST_AUTO_TEST_CASE(test_3) 
{
    big i("32123442");
    big j(2393);
    big f;
    f = i - j;
    std::cout << i << "-";
    std::cout << j << " = ";
    std::cout << f << "\n";
}

BOOST_AUTO_TEST_CASE(test_4) 
{
    big i("5322");
    big j(232);
    big f;
    f = i * j;
    std::cout << i << "*";
    std::cout << j << " = ";
    std::cout << f << "\n";
}

BOOST_AUTO_TEST_CASE(test_5) 
{
    big i("322");
    big j(232);
    big f;
    f = i / j;
    std::cout << i << "/";
    std::cout << j << " = ";
    std::cout << f << "\n";
}

BOOST_AUTO_TEST_CASE(test_6) 
{
    big i("232000001");
    big j(232);
    big f;
    f = i / j;
    std::cout << i << "/";
    std::cout << j << " = ";
    std::cout << f << "\n";
}

BOOST_AUTO_TEST_CASE(test_7) 
{
    big i("232000000");
    big j(232);
    big f;
    f = i / j;
    std::cout << i << "/";
    std::cout << j << " = ";
    std::cout << f << "\n";
}

BOOST_AUTO_TEST_CASE(test_8) 
{
    big i("23213412412");
    big j(2323);
    big f;
    f = i / j;
    std::cout << i << "/";
    std::cout << j << " = ";
    std::cout << f << "\n";
}
BOOST_AUTO_TEST_CASE(test_9) 
{
    //big i("232000100000000");
    big j(12345678);
    //big j(12345678);
    std::cout << j << "\n";
    std::cout << (int)j.size << " size\n";
    for(int i = 1; i < 10; i++) {
        j = 1234567;
        j.pow10(i);
        std::cout << (int)j.size << " size\n";
        std::cout << j << " pow\n";
    }
}

#endif 

BOOST_AUTO_TEST_CASE(test_9) 
{
    big i("232000100000000");
    std::cout << i << " ii ";
    big_2 j(i);
    //big_2 f;
    //f = i / j;
    //std::cout << i << "/";
    std::cout << j << " = ";
    //std::cout << f << "\n";
}


#if 0

BOOST_AUTO_TEST_CASE(test_12) 
{
    big i(999913);
    big j(93);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i + j;
    std::cout << i << " + ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_13) 
{
    big i(304);
    big j(4);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i % j;
    std::cout << i << " % ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_14) 
{
    big i(304);
    big j(3);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i / j;
    std::cout << i << " / ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_15) 
{
    big i(304);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = squareRoot(i);
    std::cout << i << " square root ";
    std::cout << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}



BOOST_AUTO_TEST_CASE(test_16) 
{
    big i(300999900003455234);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = ln(i);
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}


BOOST_AUTO_TEST_CASE(test_17) 
{
    big i(17);
    //std::cout << "j |" << j << "|\n";
    big j(7);
    big f;
    f = i + j;
    std::cout << i << " + ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}


BOOST_AUTO_TEST_CASE(test_18) 
{
    big i(28458691162);
    //std::cout << "j |" << j << "|\n";
    big j(2000000000);
    big f;
    f = i - j;
    std::cout << i << " - ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}


BOOST_AUTO_TEST_CASE(test_19) 
{
    big i(673);
    //std::cout << "j |" << j << "|\n";
    big j(607);
    big f;
    f = i * j;
    std::cout << i << " * ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

#endif


