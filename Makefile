

##################   BOOST TESTS   ##################
dynamic_bin_matrix_test: dynamic_bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/ \
				libraries/dynamic_bin_matrix.o tests/dynamic_bin_matrix_test.cpp \
ta		-o tests/dynamic_bin_matrix_test.out


qs_remainder_test: quadratic_sieve_remainder dynamic_bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/ \
	tests/qs_remainder_test.cpp -o tests/qs_remainder_test.out \
				libraries/quadratic_sieve_remainder.o libraries/dynamic_bin_matrix.o \
				libraries/greatest_common_divisor.o 

qs_early_exp_test: quadratic_sieve_remainder dynamic_bin_matrix
	g++ -std=c++11  -Iinclude/ -I../soft/boost_1_64_0/ -lm  -L../soft/boost_1_64_0/ \
	tests/qs_early_exp_test.cpp  -o tests/qs_early_exp_test.out \
				libraries/quadratic_sieve_remainder.o libraries/dynamic_bin_matrix.o \
				libraries/greatest_common_divisor.o -lgmp 



bin_matrix_test: bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/ \
				libraries/bin_matrix.o tests/bin_matrix_test.cpp \
				-o tests/bin_matrix_test.out

gcd_test: greatest_common_divisor
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/ \
				libraries/greatest_common_divisor.o tests/gcd_test.cpp \
				-o tests/gcd_test.out

qs_test: quadratic_sieve bin_matrix
	g++ -std=c++11  -Iinclude/ \
	tests/qs_test.cpp -o tests/qs_test.out \
				libraries/quadratic_sieve.o libraries/bin_matrix.o \
				libraries/greatest_common_divisor.o  

qs_test_big: quadratic_sieve_big bin_matrix big big_2 greatest_common_divisor_big
	g++ -std=c++11  -Iinclude/ \
	tests/qs_test_big.cpp -o tests/qs_test_big.out \
				libraries/quadratic_sieve_big.o libraries/bin_matrix.o \
				libraries/greatest_common_divisor_big.o  libraries/big.o libraries/big_2.o


qs_gmp_test: quadratic_sieve quadratic_sieve_remainder_gmp
	g++ -std=c++11 -Iinclude/  \
	 tests/qs_gmp_test.cpp -o tests/qs_gmp_test.out \
	libraries/quadratic_sieve_remainder_gmp.o  libraries/dynamic_bin_matrix.o  -lmpfr -lgmp \
				libraries/greatest_common_divisor.o 
	 # -lboost_system 
				# libraries/quadratic_sieve.o libraries/bin_matrix.o \

				 


qs_basic_condBsmooth_test: quadratic_sieve greatest_common_divisor bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/   \
	tests/qs_basic_condBsmooth_test.cpp  -o tests/qs_basic_condBsmooth_test.out \
				libraries/quadratic_sieve.o libraries/bin_matrix.o \
				libraries/greatest_common_divisor.o  -lgmp


qs_unit_matrix_test: quadratic_sieve dynamic_bin_matrix
	g++ -std=c++11  -Iinclude/ -I../soft/boost_1_64_0/ -lm  -L../soft/boost_1_64_0/ \
	tests/qs_unit_matrix_test.cpp  -o tests/qs_unit_matrix_test.out \
				libraries/quadratic_sieve.o libraries/dynamic_bin_matrix.o \
				libraries/greatest_common_divisor.o -lgmp -lboost_system

qs_unit_matrix_big_test: quadratic_sieve_big dynamic_bin_matrix big_2 big greatest_common_divisor_big
	g++ -std=c++11  -Iinclude/ -I../soft/boost_1_64_0/ -lm  -L../soft/boost_1_64_0/ \
	tests/qs_unit_matrix_big_test.cpp  -o tests/qs_unit_matrix_big_test.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/greatest_common_divisor_big.o -lgmp -lboost_system

qs_unit_matrix_big_online_test: quadratic_sieve_big dynamic_bin_matrix big big_2 greatest_common_divisor_big
	g++ -std=c++11  -Iinclude/ -lm  \
	tests/qs_unit_matrix_big_online_test.cpp  -o tests/qs_unit_matrix_big_online_test.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/greatest_common_divisor_big.o -lgmp

qs_unit_matrix_big_standart_test: quadratic_sieve_big dynamic_bin_matrix big big_2 greatest_common_divisor_big
	g++ -std=c++11  -Iinclude/ -lm  \
	tests/qs_unit_matrix_big_standart_test.cpp  -o tests/qs_unit_matrix_big_standart_test.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/greatest_common_divisor_big.o  -lgmp

dixon: quadratic_sieve_big dynamic_bin_matrix big big_2 greatest_common_divisor_big
		g++ -std=c++11  -Iinclude/ -lm  \
	tests/dixon.cpp  -o tests/dixon.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/greatest_common_divisor_big.o 

dixon_qsk: quadratic_sieve_big dynamic_bin_matrix big big_2 greatest_common_divisor_big_dixon dixon_big_lib
		g++ -std=c++11  -Iinclude/ -lm  \
	tests/dixon_qsk.cpp  -o tests/dixon_qsk.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/dixon_greatest_common_divisor_big.o libraries/dixon_big_lib.o -lgmp

mpqs: quadratic_sieve_big dynamic_bin_matrix big big_2 greatest_common_divisor_big_dixon dixon_big_lib
		g++ -std=c++11  -Iinclude/ -lm  \
	tests/mpqs.cpp  -o tests/mpqs.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/dixon_greatest_common_divisor_big.o libraries/dixon_big_lib.o -lgmp


mpqs1: quadratic_sieve_big dynamic_bin_matrix big big_2 greatest_common_divisor_big
	g++ -std=c++11  -Iinclude/ -lm  \
	tests/mpqs.cpp  -o tests/mpqs.out \
				libraries/quadratic_sieve_big.o libraries/dynamic_bin_matrix.o libraries/big.o libraries/big_2.o\
				libraries/greatest_common_divisor_big.o -lgmp


dixon_number_gen:
		g++ -std=c++11  -Iinclude/ -lm  \
	dixon_number_gen.cpp  -o dixon_number_gen.out  


big_test: big big_2
	g++ -std=c++11  -Iinclude/ -lm  \
	tests/big_test.cpp -o tests/big_tests.out \
	libraries/big_2.o libraries/big.o -lboost_system

big_2_test: big_2 big
	g++ -std=c++11  -Iinclude/ -lm  \
	tests/big_2_test.cpp -o tests/big_2_tests.out \
	libraries/big_2.o libraries/big.o -lboost_system


#####################################################



#################### LIBRARIES ######################
quadratic_sieve_remainder: dynamic_bin_matrix \
				greatest_common_divisor \
				libraries/quadratic_sieve_remainder.cpp \
				include/quadratic_sieve_remainder.h \
				include/dynamic_bin_matrix.h \
				include/log.h
	g++ -std=c++11 -Iinclude/ -c libraries/quadratic_sieve_remainder.cpp \
				-o libraries/quadratic_sieve_remainder.o

quadratic_sieve_remainder_gmp: dynamic_bin_matrix \
				greatest_common_divisor \
				libraries/quadratic_sieve_remainder_gmp.cpp \
				include/quadratic_sieve_remainder_gmp.h \
				include/dynamic_bin_matrix.h \
				include/log.h
	g++ -std=c++11 -Iinclude/ -c libraries/quadratic_sieve_remainder_gmp.cpp \
				-o libraries/quadratic_sieve_remainder_gmp.o -lmpfr -lgmp 


dynamic_bin_matrix: libraries/dynamic_bin_matrix.cpp include/dynamic_bin_matrix.h include/log.h
	g++ -Iinclude/ -c libraries/dynamic_bin_matrix.cpp -o libraries/dynamic_bin_matrix.o



quadratic_sieve: bin_matrix \
				greatest_common_divisor \
				libraries/quadratic_sieve.cpp \
				include/quadratic_sieve.h \
				include/log.h
	g++ -std=c++11 -Iinclude/ -c libraries/quadratic_sieve.cpp \
				-o libraries/quadratic_sieve.o

quadratic_sieve_big: bin_matrix \
				greatest_common_divisor \
				libraries/quadratic_sieve_big.cpp \
				include/quadratic_sieve_big.h \
				include/log.h
	g++ -std=c++11 -Iinclude/ -c libraries/quadratic_sieve_big.cpp \
				-o libraries/quadratic_sieve_big.o


greatest_common_divisor: libraries/greatest_common_divisor.cpp \
						include/greatest_common_divisor.h \
						include/log.h
	g++  -std=c++11 -Iinclude/ -c libraries/greatest_common_divisor.cpp \
				-o libraries/greatest_common_divisor.o

greatest_common_divisor_big: libraries/greatest_common_divisor_big.cpp \
						include/greatest_common_divisor_big.h \
						include/log.h
	g++  -std=c++11 -Iinclude/ -c libraries/greatest_common_divisor_big.cpp \
				-o libraries/greatest_common_divisor_big.o

greatest_common_divisor_big_dixon: libraries/dixon_greatest_common_divisor_big.cpp \
						include/dixon_greatest_common_divisor_big.h \
						include/log.h
	g++  -std=c++11 -Iinclude/ -c libraries/dixon_greatest_common_divisor_big.cpp \
				-o libraries/dixon_greatest_common_divisor_big.o



bin_matrix: libraries/bin_matrix.cpp include/bin_matrix.h include/log.h
	g++ -Iinclude/ -c libraries/bin_matrix.cpp -o libraries/bin_matrix.o
	
dixon_big_lib: libraries/dixon_big_lib.cpp include/dixon_big_lib.h include/log.h
	g++ -Iinclude/ -c libraries/dixon_big_lib.cpp -o libraries/dixon_big_lib.o


big: libraries/big.cpp include/big.h include/log.h
	g++ -Iinclude/ -c libraries/big.cpp -o libraries/big.o

big_2: libraries/big_2.cpp include/big_2.h include/log.h
	g++ -Iinclude/ -c libraries/big_2.cpp -o libraries/big_2.o


test_gmp:
	g++ test_gmp.cpp -lgmp -o test_gmp

#####################################################

qs_basic: bin_matrix quadratic_sieve qs_basic.cpp
	g++ -std=c++11 -Iinclude/ \
		libraries/quadratic_sieve.o libraries/bin_matrix.o \
		libraries/greatest_common_divisor.o \
	qs_basic.cpp -o qs_basic.out
    # g++ -I../soft/boost_1_61_0/  -L../soft/boost_1_61_0/ test1.cpp -o test1

prime_gen_gmp:
	g++ -std=c++11 -g -Iinclude/ \
	prime_gen_gmp.cpp  -o prime_gen_gmp.out \
				-lgmp

prime_gen_gmp_prob:
	g++ -std=c++11 -g -Iinclude/ \
	prime_gen_gmp_prob.cpp  -o prime_gen_gmp_prob.out \
				-lgmp

clean:
	rm  -f libraries/*.o
	rm  -f tests/*.out
	rm -f ./*.out
