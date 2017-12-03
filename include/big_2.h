#ifndef BIG
#define BIG

#include <string.h>
#include <iostream>  
#include <stdexcept>
#include <math.h>
#include "log.h"
using namespace std;  
#define BIG_SIZE 20
#define DIVISION_COUNT  3
#define POSITIONAL_BASE 1000

#include "big.h"
class big_2{
public:
	int number[BIG_SIZE];
	char sign;
	char size;
	big_2(){
		for (int i=0; i<BIG_SIZE; i++)
			number[i] = 0;
		sign = 0;
		size = 0;
	}
	big_2(std::string str);
	big_2(long long n); 
	big_2& operator=(const big_2 other)
	{
		for (int i=0; i<BIG_SIZE; i++)
			number[i] = other.number[i];
		sign = other.sign;
		size = other.size;
		return *this;
	}
	big_2 operator+(const big_2 other) const;
	big_2 operator-(const big_2 other) const;
	friend std::ostream& operator<<(std::ostream& os, const big_2& obj);
	void pow10(int power); 
	big_2 operator*(const big_2 other) const;
	big_2 operator/(const big_2 other) const;
	friend big_2 div(const big_2 other);
	friend double ln(const big_2 n); 
	bool operator<(const big_2 other) const;
	bool operator>(const big_2 other) const;
	friend bool special_compare(const big_2 one, const big_2 other);
	big_2 operator%(const big_2 other) const; 
	bool operator==(const big_2 other) const;
	big_2 operator%(const long long other) const;
//	big_2 operator/(const long long  other) const{
};
big_2 squareRoot(big_2 n);
#endif
