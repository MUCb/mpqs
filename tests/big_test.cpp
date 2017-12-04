#define BOOST_TEST_MODULE Big Numbers Test
#include <boost/test/included/unit_test.hpp> 

#include "big.h"
#include "big_2.h"
#include <iostream>  
int showDebugMsg = 1;
#if 0
BOOST_AUTO_TEST_CASE(first_test) 
{
    std::string str1("123");
    std::string str2("-10023");

    big i(str1);
    std::cout << i;
    big g(str2);
    std::cout << g;
/*    try
    {
    	big j("-1234231423421342134123");
    }
    catch (const char *e) 
    {
	std::cout << "stack exception: " << e << std::endl;
    }
   //BOOST_TEST(i); 
    // BOOST_TEST(i == 2);*/
}
BOOST_AUTO_TEST_CASE(second_test) 
{
    big i("123");
    std::cout << i << " - ";
    big g("923");
    std::cout << g << " = ";
    i = i + g;
    std::cout << i << "\n";
}

BOOST_AUTO_TEST_CASE(third_test) 
{
    big i("30");
    big g("21");
    std::cout << i << " - ";
    std::cout << g << " = ";
    i = i - g;
    std::cout << i << "\n";
}

BOOST_AUTO_TEST_CASE(test_4) 
{
    big i("302");
    big g("21");
    std::cout << i << " - ";
    std::cout << g << " = ";
    i = i - g;
    std::cout << i << "\n";

}

BOOST_AUTO_TEST_CASE(test_5) 
{
    big i("302");
    big g("20451");
    std::cout << i << " * ";
    std::cout << g << " = ";
    i = i * g;
    std::cout << i << "\n";

}


BOOST_AUTO_TEST_CASE(test_6) 
{
    big i("30234");
    big g("30234");
    std::cout << i << " < ";
    std::cout << g << " = ";
    if( i < g)
    	std::cout << "less\n";
    else 
    	std::cout << "bigger\n";

}

BOOST_AUTO_TEST_CASE(test_7) 
{
    big i(30234);
    std::cout << "|" << i << "|\n";

}

BOOST_AUTO_TEST_CASE(test_8) 
{
    big i(30234);
    std::cout << "size " << (int) i.size << "|\n";
    i.pow10(1);
    std::cout << "|" << i << "|\n";
    std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_9) 
{
    big i(30234);
    big j(30004);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i - j;
    std::cout << "f |" << f << "|\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_10) 
{
    big i(30234);
    big j(30234);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i - j;
    std::cout << i << " - ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_11) 
{
    big i(30234);
    big j(30004);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i % j;
    std::cout << i << " % ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

BOOST_AUTO_TEST_CASE(test_12) 
{
    big i(304);
    big j(4);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = i / j;
    std::cout << i << " / ";
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
    big i(1234567891);
    //big i(6712341233);
    //std::cout << "j |" << j << "|\n";
    big j(45678);
    //big j(642307);
    big f;
    //for ( int u = 0 ; u < 10000; u++) 
    {
    f = i / j;
    std::cout << i << " / ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    }
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

#endif
BOOST_AUTO_TEST_CASE(test_20) 
{
    //big i(1234567891);
    big i(-48);
    //std::cout << "j |" << j << "|\n";
    //big j(4);
    big j(24);
    //int j = 24;
    big f;
    //for ( int u = 0 ; u < 10000; u++) 
    {
    f = i / j;
    std::cout << i << " / ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    }
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}

#if 0
BOOST_AUTO_TEST_CASE(test_21) 
{
    big_2 i(123456789123456);
    big j(i);
    //for ( int u = 0 ; u < 10000; u++) 
    //{
    //std::cout << i << " / ";
    std::cout << j << " = ";
    //std::cout << f << "\n";
    //}
    //std::cout << i << " square root ";
    //std::cout << " = ";
    //std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

}




#endif
