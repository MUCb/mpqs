#define BOOST_TEST_MODULE Big Numbers Test
#include <boost/test/included/unit_test.hpp> 

#include "big.h"
#include <iostream>  

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
//    big g("30234");
    std::cout << "|" << i << "|\n";
//    std::cout << g << " = ";
//    if( i < g)
//    	std::cout << "less\n";
//    else 
//    	std::cout << "bigger\n";

}




#if 0

#endif
