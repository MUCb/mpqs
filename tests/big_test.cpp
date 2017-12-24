#define BOOST_TEST_MODULE Big Numbers Test
#include <boost/test/included/unit_test.hpp> 

#include "big.h"
#include "big_2.h"
#include <iostream>  
int showDebugMsg = 6;
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
    big i(30434);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = squareRoot(i);
    std::cout << i << " square root ";
    std::cout << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

    BOOST_TEST(f == 174);
}

BOOST_AUTO_TEST_CASE(test_17) 
{
    big i(219042);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = squareRoot(i);
    std::cout << i << " square root ";
    std::cout << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

    BOOST_TEST(f == 468);
}

BOOST_AUTO_TEST_CASE(test_18) 
{
    big i(2119044);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = squareRoot(i);
    std::cout << i << " square root ";
    std::cout << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

    BOOST_TEST(f == 1455);
}

BOOST_AUTO_TEST_CASE(test_19) 
{
    big i(21230001904);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = squareRoot(i);
    std::cout << i << " square root ";
    std::cout << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

    BOOST_TEST(f == 145703);
}


BOOST_AUTO_TEST_CASE(test_20) 
{
    big i(212300011234904);
    //std::cout << "j |" << j << "|\n";
    big f;
    f = squareRoot(i);
    std::cout << i << " square root ";
    std::cout << " = ";
    std::cout << f << "\n";
    //std::cout << "size " << (int) i.size << "|\n";

    BOOST_TEST(f == 14570518);
}

BOOST_AUTO_TEST_CASE(test_21) 
{
    big N("-7357940320521467587");
    big p("4483");
    big res("-1641298309284289");
    big tmp;
    //N_mod = 454;
    tmp = N / p;
   std::cout << "N_mod |" << tmp << "|\n";
    BOOST_TEST(tmp == res);
    //std::cout << "size " << (int) i.size << "|\n";
   //std::cout << "N7=" << N << "\n";
    //exit(0);
    // tmp = tmp % tmp_p;

}

BOOST_AUTO_TEST_CASE(test_22) 
{
    big N("-7357940320521467587");
    big p("4483");
    big res(0);
    big tmp;
    //N_mod = 454;
    tmp = N % p;
   std::cout << "N_mod |" << tmp << "|\n";
    BOOST_TEST(tmp == res);
    //std::cout << "size " << (int) i.size << "|\n";
   //std::cout << "N7=" << N << "\n";
    //exit(0);
    // tmp = tmp % tmp_p;

}

BOOST_AUTO_TEST_CASE(test_23) 
{
    big N("1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    double res=0;
    double  tmp;
    tmp = ln(N);
    //N_mod = 454;
   std::cout << "log n |" << tmp << "|\n";
   std::cout << sqrt(log(tmp) *ln(N)) << "\n";
   std::cout << (long long ) exp(0.5 *sqrt(log(tmp) *ln(N))) << "\n";
    //std::cout << "size " << (int) i.size << "|\n";
   //std::cout << "N7=" << N << "\n";
    //exit(0);
    // tmp = tmp % tmp_p;

}

BOOST_AUTO_TEST_CASE(test_24) 
{
    big N("392344232342342423423");
    big res("167310973280316598");
    long long p = 2345;
    big quotient;
    long long  reminder;

    div_rem_l(N, p, quotient, reminder);
    BOOST_TEST(reminder == 1113);
    BOOST_TEST(quotient == res);
    std::cout << N <<  "/" << p << "|\n";
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";
}

BOOST_AUTO_TEST_CASE(test_25) 
{
    big N("392344232342342423423234234234545453563553453");
    big res("167310973280316598474726752338825353332005");
    long long p = 2345;
    big quotient;
    long long  reminder;

    div_rem_l(N, p, quotient, reminder);
    std::cout << N <<  "/" << p << "|\n";
    BOOST_TEST(reminder == 1728);
    BOOST_TEST(quotient == res);
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";
}

BOOST_AUTO_TEST_CASE(test_26) 
{
    big N("-7357940320521467587");
    long long  p = 4483;
    big quotient;
    long long  reminder;

    big res("-1641298309284289");
    //N_mod = 454;
    div_rem_l(N, p, quotient, reminder);
    BOOST_TEST(reminder == 0);
    BOOST_TEST(quotient == res);
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";

}

BOOST_AUTO_TEST_CASE(test_27) 
{
    big N(304);
    long long  p = 3;
    big quotient;
    long long  reminder;

    big res("101");
   //std::cout << "j |" << j << "|\n";
    big f;
    div_rem_l(N, p, quotient, reminder);
    BOOST_TEST(reminder == 1);
    BOOST_TEST(quotient == res);
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";

}

BOOST_AUTO_TEST_CASE(test_28) 
{

    big N(304);
    long long  p = 4;
    big quotient;
    long long  reminder;

    big res("76");
   //std::cout << "j |" << j << "|\n";
    div_rem_l(N, p, quotient, reminder);
    BOOST_TEST(reminder == 0);
    BOOST_TEST(quotient == res);
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";

}

BOOST_AUTO_TEST_CASE(test_29) 
{

    big N(-304);
    long long  p = 4;
    big quotient;
    long long  reminder;

    big res("-76");
   //std::cout << "j |" << j << "|\n";
    div_rem_l(N, p, quotient, reminder);
    BOOST_TEST(reminder == 0);
    BOOST_TEST(quotient == res);
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";

}


BOOST_AUTO_TEST_CASE(test_30) 
{
    big N(30234);
    long long  p = 30004;
    big quotient;
    long long  reminder;

    big res("1");
   //std::cout << "j |" << j << "|\n";
    div_rem_l(N, p, quotient, reminder);
    BOOST_TEST(reminder == 230);
    BOOST_TEST(quotient == res);
    std::cout << "quotient |" << quotient << "|\n";
    std::cout << "reminder |" << reminder << "|\n";
}


#if 0

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
#if 0
BOOST_AUTO_TEST_CASE(test_20) 
{
    big i(2149700);
    big null(0);
    big j(2);
    big f;
    f = i % j;
    std::cout << i << " % ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    BOOST_TEST(f == null);
}
BOOST_AUTO_TEST_CASE(test_21) 
{
    big i(48);
    big null(0);
    big j(24);
    big f;
    f = i % j;
    std::cout << i << " % ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    BOOST_TEST(f == null);
}
BOOST_AUTO_TEST_CASE(test_22) 
{
    big i(-480000);
    big null(0);
    big j(24);
    big f;
    f = i % j;
    std::cout << i << " % ";
    std::cout << j << " = ";
    std::cout << f << "\n";
    BOOST_TEST(f == null);
}



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
