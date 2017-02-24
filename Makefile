

##################   BOOST TESTS   ##################
dynamic_bin_matrix_test: dynamic_bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/  -L../soft/boost_1_62_0/ \
				libraries/dynamic_bin_matrix.o tests/dynamic_bin_matrix_test.cpp \
				-o tests/dynamic_bin_matrix_test.out


qs_remainder_test: quadratic_sieve_remainder dynamic_bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/  -L../soft/boost_1_62_0/ \
	tests/qs_remainder_test.cpp -o tests/qs_remainder_test.out \
				libraries/quadratic_sieve_remainder.o libraries/dynamic_bin_matrix.o \
				libraries/greatest_common_divisor.o 

qs_early_exp_test: quadratic_sieve_remainder dynamic_bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/ -lm  -L../soft/boost_1_62_0/ \
	tests/qs_early_exp_test.cpp -o tests/qs_early_exp_test.out \
				libraries/quadratic_sieve_remainder.o libraries/dynamic_bin_matrix.o \
				libraries/greatest_common_divisor.o 



bin_matrix_test: bin_matrix
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/  -L../soft/boost_1_62_0/ \
				libraries/bin_matrix.o tests/bin_matrix_test.cpp \
				-o tests/bin_matrix_test.out

gcd_test: greatest_common_divisor
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/  -L../soft/boost_1_62_0/ \
				libraries/greatest_common_divisor.o tests/gcd_test.cpp \
				-o tests/gcd_test.out

qs_test: quadratic_sieve
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/  -L../soft/boost_1_62_0/ \
	tests/qs_test.cpp -o tests/qs_test.out \
				libraries/quadratic_sieve.o libraries/bin_matrix.o \
				libraries/greatest_common_divisor.o 

qs_basic_extra_exp_test: quadratic_sieve
	g++ -std=c++11 -Iinclude/ -I../soft/boost_1_62_0/  -L../soft/boost_1_62_0/ \
	tests/qs_basic_extra_exp_test.cpp -o tests/qs_basic_extra_exp_test.out \
				libraries/quadratic_sieve.o libraries/bin_matrix.o \
				libraries/greatest_common_divisor.o 

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


#####################################################

qs_basic: bin_matrix quadratic_sieve qs_basic.cpp
	g++ -std=c++11 -Iinclude/ \
		libraries/quadratic_sieve.o libraries/bin_matrix.o \
		libraries/greatest_common_divisor.o \
	qs_basic.cpp -o qs_basic.out
    # g++ -I../soft/boost_1_61_0/  -L../soft/boost_1_61_0/ test1.cpp -o test1


clean:
	rm  -f libraries/*.o
	rm  -f tests/*.out
	rm -f ./*.out