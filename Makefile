
test1:
	g++ -I../soft/boost_1_61_0/  -L../soft/boost_1_61_0/ test.cpp -o test.out
    # g++ -I../soft/boost_1_61_0/  -L../soft/boost_1_61_0/ test1.cpp -o test1

bin_matrix: libraries/bin_matrix.cpp include/bin_matrix.h
	g++ -Iinclude/ -c libraries/bin_matrix.cpp -o libraries/bin_matrix.o

qs_3: bin_matrix qs_3.cpp
	g++ -Iinclude/  libraries/bin_matrix.o qs_3.cpp -o qs_3.out
    # g++ -I../soft/boost_1_61_0/  -L../soft/boost_1_61_0/ test1.cpp -o test1
