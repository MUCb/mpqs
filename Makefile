

##################   BOOST TESTS   ##################
dynamic_bin_matrix_test: dynamic_bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/ \
				libraries/dynamic_bin_matrix.o tests/dynamic_bin_matrix_test.cpp \
				-o tests/dynamic_bin_matrix_test.out


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

qs_test: quadratic_sieve
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_64_0/  -L../soft/boost_1_64_0/  -lgmp \
	tests/qs_test.cpp -o tests/qs_test.out \
				libraries/quadratic_sieve.o libraries/bin_matrix.o \
				libraries/greatest_common_divisor.o -lgmp 


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

qs_unit_matrix_big_test: quadratic_sieve dynamic_bin_matrix big
	g++ -std=c++11  -Iinclude/ -I../soft/boost_1_64_0/ -lm  -L../soft/boost_1_64_0/ \
	tests/qs_unit_matrix_big_test.cpp  -o tests/qs_unit_matrix_big_test.out \
				libraries/quadratic_sieve.o libraries/dynamic_bin_matrix.o libraries/big.o\
				libraries/greatest_common_divisor.o -lgmp -lboost_system


big_test: big
	g++ -std=c++11  -Iinclude/ -lm  \
	tests/big_test.cpp -o tests/big_tests.out \
	libraries/big.o -lboost_system


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


greatest_common_divisor: libraries/greatest_common_divisor.cpp \
						include/greatest_common_divisor.h \
						include/log.h
	g++  -std=c++11 -Iinclude/ -c libraries/greatest_common_divisor.cpp \
				-o libraries/greatest_common_divisor.o


bin_matrix: libraries/bin_matrix.cpp include/bin_matrix.h include/log.h
	g++ -Iinclude/ -c libraries/bin_matrix.cpp -o libraries/bin_matrix.o

big: libraries/big.cpp include/big.h include/log.h
	g++ -Iinclude/ -c libraries/big.cpp -o libraries/big.o


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
