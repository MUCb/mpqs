#ifndef BIG
#define BIG

#include <string.h>
#include <iostream>  
#include <stdexcept>
using namespace std;  
#define BIG_SIZE 20

class big{
public:
	char number[BIG_SIZE];
	char sign;
	char size;
	big(){
		for (int i=0; i<BIG_SIZE; i++)
			number[i] = 0;
		sign = 0;
		size = 0;
	}
	big(std::string str);
	big(long long n); 
	big& operator=(const big other)
	{
		for (int i=0; i<BIG_SIZE; i++)
			number[i] = other.number[i];
		sign = other.sign;
		size = other.size;
		return *this;
	}
	big operator+(const big other) const;
	big operator-(const big other) const;
	friend std::ostream& operator<<(std::ostream& os, const big& obj);
	void pow10(int power); 
	big operator*(const big other) const;
	big operator/(const big other) const;
	friend big div(const big other);
	friend double ln(const big n); 
	bool operator<(const big other) const;
	bool operator>(const big other) const;
	big operator%(const big other) const; 
	bool operator==(const big other) const;
};
big squareRoot(big n);
#endif
