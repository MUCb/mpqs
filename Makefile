

##################   BOOST TESTS   ##################
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
#####################################################



#################### LIBRARIES ######################
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

qs_3: bin_matrix qs_3.cpp
	g++ -std=c++11 -Iinclude/ \
		libraries/quadratic_sieve.o libraries/bin_matrix.o \
		libraries/greatest_common_divisor.o \
	qs_3.cpp -o qs_3.out
    # g++ -I../soft/boost_1_61_0/  -L../soft/boost_1_61_0/ test1.cpp -o test1
