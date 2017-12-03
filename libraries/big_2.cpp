#include "big_2.h"
#include "big.h"
#include <math.h>

big_2::big_2(std::string _str) {
	std::string str;
	int tail = 0;
	if (_str[0] == '-'){
		sign = 1;
		tail = 1;
		str = _str.substr(1);
	} else {
		sign = 0;
		str = _str;
	}
	//std::cout << "contructor big_2: sign" <<(int) sign << "\n";
	size = str.size() / 3;
    if (str.size() % 3)
        size++;
	//std::cout << "contructor big_2: size" <<(int) size << "\n";
	//std::cout << "condtructor big_2: strlen" <<(int) str.size() << "\n";
	if (size >= (BIG_SIZE * 3)) {
		//cout << " to big_2 number " << str << "\n";
		throw "throw something";
	}
	for (int i=0, j = str.size() - 1; i<BIG_SIZE ; i++){
		number[i] = 0;
        if (j >= 0){
            for(int k=0;k<3 && j>=0 ;k++ ){
                //std::cout << "char " << str[j] << "\n";
                if (j >= 0)
                    number[i] += (str[j] -'0') * pow(10,k);
                //std::cout << "number " << number[i] << "\n";
                j--;
            } 
        }
	}
}

big_2::big_2(big n) {
    int count = 1;
    size = 0;
	for (int i=0; i<BIG_SIZE; i++){
		number[i] = 0;
	}


    for( int i = 0; i < n.size; i++) {
        number[size] += n.number[i] * count;
        std::cout << "curr number " << number[size] << "\n";
        std::cout << "n number " << n.number[i] << "\n";
        count *= 10;
        if (count == 1000) {
            count = 1;
            size++;
        }
    }
}


big_2::big_2(long long n) {
	size = 0;
	for (int i=0; i<BIG_SIZE; i++){
		number[i] = 0;
	}

	long long tmp;
	if( n < 0) {
		sign = 1;
		tmp = -n;
	} else {
		sign = 0;
		tmp = n;
	}

	//std::cout << " conteructor " << n << "\n";
	//std::cout << " tmp " << tmp << "\n";
	for( int i = 0; tmp > 0; i++){
		number[i] = tmp % 1000;
		tmp /= 1000;
		size++;
	}
	//std::cout << " size " << (int) size << "\n";
}

/* we use + operation only with numers with the same sign
 */
big_2 big_2::operator+(const big_2 other) const
{
	big_2 tmp;
	big_2 curr = *this;
	int tmp_size;
	tmp.size = size > other.size ? size : other.size;
	tmp_size = tmp.size;
	if( sign == other.sign){
		for (int i=0; i<tmp_size; i++){
			tmp.number[i] += number[i] + other.number[i];
			
				//std::cout << "operator_+ i " << i << "\n";
				//std::cout << "number+ i " << (int) tmp.number[i] << "\n";
				//std::cout << "number+ i " << (int) other.number[i] << "\n";
				//std::cout << "number+ i " << (int) number[i] << "\n";
			if(tmp.number[i] > 999){
				tmp.number[i] -= 1000;
				tmp.number[i+1] += 1;
				//std::cout << "operator+ i " << i << "\n";
				//std::cout << "operator+ n " << (int) tmp.number[i+1] << "\n";
				if( i+1 == tmp.size) {
					tmp.size++;
				}
			}
		}
	} else {
		std::cout << " operation+ different sign \n";
	}
	return tmp;
}



/* make operation- only with numbers with the same sign
 * you first number always bigger than second
 */
big_2 big_2::operator-(const big_2 other) const{
	big_2 tmp = *this;
	big_2 curr = *this;
	int tmp_size;
	tmp.size = size > other.size ? size : other.size;
	tmp_size = tmp.size;
	if( sign == other.sign){
		for (int i=0; i<tmp_size; i++){
			if(tmp.number[i] < 0) {
				tmp.number[i] += 1000;
				//curr.number[i+1] -= 1;
				tmp.number[i+1] -= 1;
			}
			
			//std::cout << "before tmp number+ i " << i << "=" << (int) tmp.number[i] << "\n";
			//std::cout << "other number " << i << "=" << (int) other.number[i] << "\n";
			tmp.number[i] = tmp.number[i] - other.number[i];
			
				//std::cout << "operator_+ i " << i << "\n";
				//std::cout << "tmp number+ i " << i << "=" << (int) tmp.number[i] << "\n";
				//std::cout << "number+ i " << (int) other.number[i] << "\n";
				//std::cout << "number+ i " << (int) number[i] << "\n";
			if(tmp.number[i] < 0){
				tmp.number[i] += 1000;
				//curr.number[i+1] -= 1;
				tmp.number[i+1] -= 1;
				//std::cout << "tmp operator+ i " << i+1 << "=" << (int) tmp.number[i+1] << "\n";
			}
			//std::cout << "operator+ i " << (int)i << "\n";
			//std::cout << "operator+ size " << (int)tmp.size<< "\n";
			if( i+1 == tmp.size && tmp.number[i] == 0) {
				for(int j = i ; j >= 0; j--) {
					if ( tmp.number[j] != 0)
						break;
					tmp.size--;
				}
				if( tmp.size == 0)
					tmp.sign = 0;
			}
			//std::cout << "operator+ size2 " <<(int) tmp.size<< "\n";
		}
	} else {
		std::cout << " operation- different sign \n";
	}

	return tmp;

}

big_2 big_2::operator*(const big_2 other) const{
	big_2 tmp;
	if (size == 0)
		return *this;
	else if (other.size == 0)
		return other;

	tmp.size = size + other.size - 1;
	int tmp_size = tmp.size;
	if( sign == other.sign)
		tmp.sign = 0; 
	else  
		tmp.sign = 1; 
/*	
	if ( size == 1 && number[0] == 1){
		int s = tmp.sign;
		tmp = other;
		tmp.sign = s;
		return tmp;
	}
	if ( other.size == 1 && other.number[0]) {
		int s = tmp.sign;
		tmp = *this;
		tmp.sign = s;
		return tmp;
	}
*/
	//std::cout << "operator * tmp_size "<< (int) tmp_size << "\n";
	int offset = 0;
	for (int i = 0; i < other.size; i++, offset++) {
		if( other.number[i] == 0)
			continue;

		for (int j = 0; j < size; j++) {
			tmp.number[j + offset] += number[j] * other.number[i];
			//std::cout << "operator * tmp number "<< (int) tmp.number[j + offset] << "\n";
			if (tmp.number[j + offset] > 999){
				int tmp_number = tmp.number[j + offset];
				tmp.number[j + offset] =  tmp_number % 1000;
				tmp.number[j + offset + 1] += tmp_number / 1000;
				//std::cout << "operator * tmp number++ "<< (int) tmp.number[j + offset +1] << "\n";
				if( j + offset + 1 == tmp.size) {
					tmp.size++;
				}
			}
		}
	}
	return tmp;
}

big_2 big_2::operator/(const big_2 other) const{
	std::cout << " other |" << other << "|\n";
	std::cout << " other size |" << (int)other.size << "|\n";
	std::cout << " this |" << *this << "|\n";
	std::cout << " this size |" <<(int)  (*this).size << "|\n";
    big divident(*this);
    big divisor(other);
	big_2 quotient;
	return quotient;
}

/* quotient is rounded to the next integer
 */
big_2 div(const big_2 divident1, const big_2 divisor1) {
	//std::cout << " other |" << other << "|\n";
	//std::cout << " this |" << *this << "|\n";
	big_2 divident = divident1;
	big_2 divisor = divisor1;
	big_2 divisor10;
	big_2 quotient;
	big_2 tmp;
	big_2 one(1);
	big_2 ten(10);
	int quot_size = 0;
	return quotient;
}


double ln(const big_2 n) {
	long long num = 0;
	double log_num = 0;
	int remain = 0;
	if ( n.size > 10 )
		remain = n.size - 10;

	for (int i = n.size - 1; i >= ( n.size - 10) && i >= 0 ; i--) {
		num *= 10;
		num += n.number[i];
	}
	log_num = log(num );
	if ( remain != 0) {
		log_num += (log(10) * remain);
	}
	//std::cout << "log num = " << log_num << "\n";
	return log_num;
}

big_2 big_2::operator%(const big_2 other) const{
	//std::cout << " other |" << other << "|\n";
	//std::cout << " this |" << *this << "|\n";
	big_2 divident = *this;
	big_2 divisor = other;
	big_2 divisor10;
	big_2 tmp(1);
	return divident;
}

big_2 big_2::operator%(const long long other) const{
	//std::cout << " other |" << other << "|\n";
	//std::cout << " this |" << *this << "|\n";
	big_2 divident = *this;
	big_2 divisor (other);
	big_2 divisor10;
	big_2 tmp(1);
	divident.sign = 0;
	divisor.sign = 0;
	return divident;
}

/*
void big_2::pow1000(int power) {
	for( int i = size - 1; i >= 0; i--) {
		number[i+power] = number[i];
		number[i] = 0;
	}
	size += power;
}
*/

void big_2::pow10(int power) {
    int power_recidue = power % 3;
    int real_power = power / 3;
    int shift = 0;
    if ( power_recidue == 0) {
        for( int i = size - 1; i >= 0; i--) {
            number[i+real_power] = number[i];
            number[i] = 0;
        }
        size += real_power;

    } else {
        //std::cout << "power_recidue = " << power_recidue << "\n";
        if ( number[size-1] < 10) 
            shift = 2;
        else if ( number[size-1] < 100)
            shift = 1;
        else 
            shift = 0;

        //std::cout << "shift = " << shift << "\n";
        int tmp_real = 0;
        int tmp_recidue = 0;
        if ( power_recidue > shift) {
            for( int i = size - 1; i >= 0; i--) {
                tmp_real = (tmp_recidue * pow(10, power_recidue )) + number[i] / pow(10, (3 - power_recidue )); 
                //std::cout << "tmp_real " << tmp_real << "\n";
                tmp_recidue = number[i] % (int ) pow(10, (3 - power_recidue )); 
                //std::cout << "tmp_recidue " << tmp_recidue << "\n";
                number[i + real_power + 1] = tmp_real;
                if (real_power > 0)
                    number[i] = 0;
                number[i + real_power ] = tmp_recidue * pow(10, power_recidue);
            }
        } else {
            for( int i = size - 1; i >= 0; i--) {
                tmp_recidue = number[i] % (int ) pow(10, (3 - power_recidue )); 
                //std::cout << "tmp_recidue " << tmp_recidue << "\n";
                if (i == 0)
                    tmp_real = tmp_recidue * pow(10, power_recidue); 
                else
                    tmp_real = tmp_recidue * pow(10, power_recidue) + number[i-1] / pow(10, 3-power_recidue); 
                //std::cout << "tmp_real " << tmp_real << "\n";
                number[i + real_power] = tmp_real;
                if (real_power > 0)
                    number[i] = 0;
                //number[i + real_power - 1] = tmp_recidue * pow(10, power_recidue);
            }
        }
        if ( power_recidue > shift) 
            size += real_power + 1;
        else
            size += real_power;
//	size += power;

    } 
}


bool special_compare(const big_2 one, const big_2 other) {
	//std::cout << "size curr |" << (int)size << "|\n";
	//std::cout << "size other |" << (int)other.size << "|\n";
	for (int i = one.size - 1, j = other.size -1 ; i >= 0 || j >= 0; i--, j--) {
		//std::cout << "number" << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
		if (one.number[i] > other.number[j]) {
		//std::cout << "number1 " << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
			return true;
		} else if (one.number[i] < other.number[j]) {
			return false;
		}
	}
	return true; 
}


bool big_2::operator<(const big_2 other) const{
	//std::cout << "size curr |" << (int)size << "|\n";
	//std::cout << "size other |" << (int)other.size << "|\n";
	if (sign == 1 && other.sign == 0)
		return true;
	else if (sign == 0 && other.sign == 1)
		return false;
	if (size < other.size) {
		return true;
	} else if ( size > other.size)
		return false;
	else {
		for (int i = size - 1; i >= 0; i--) {
			//std::cout << "number" << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
			if (number[i] < other.number[i]) {
			//std::cout << "number1 " << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
				return true;
			} else if (number[i] > other.number[i]) {
				return false;
			}
		}
	}
	return false; 
}

bool big_2::operator>(const big_2 other) const{
	if (sign == 1 && other.sign == 0)
		return true;
	else if (sign == 0 && other.sign == 1)
		return false;

	if (size > other.size)
		return true;
	else if ( size < other.size)
		return false;
	else {
		for (int i = size - 1; i >= 0; i--) {
			//std::cout << "number" << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
			if (number[i] > other.number[i]) {
			//std::cout << "number1 " << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
				return true;
			} else if (number[i] < other.number[i]) {
				return false;
			}
		}
	}
	return false; 
}

bool big_2::operator==(const big_2 other) const{
	if (size != other.size)
		return false;
	else {
		for (int i = size - 1; i >= 0; i--) {
			//std::cout << "number" << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
			if (number[i] !=  other.number[i]) {
			//std::cout << "number1 " << (int ) number[i] << " and " << (int)  other.number[i] << "\n";
				return false;
			}
		}
	}
	return true; 
}



std::ostream& operator<<(std::ostream& os, const big_2& obj){
	if ( obj.size == 0)
		os << (int) 0;

	if (obj.sign == 1)
		os << "-";
	for (int i = obj.size - 1; i>=0; i--){
		//if (obj.number[i] == -1)
		//	continue;
		//os <<"|" <<static_cast<unsigned int>(obj.number[i]);
        if (i<obj.size-1){
            if (obj.number[i]<10)
                    os << 0;
            if (obj.number[i]<100)
                    os << 0;
        }
		os <<static_cast<unsigned int>(obj.number[i]);
	    //os << "\t";  
	}
	//os << "\n";  
	//os << "size " <<(int) obj.size <<"\n";  
	//os << "sign " <<(int) obj.sign <<"\n";  
	return os;  
}

/*Returns the square root of n. Note that the function */
big_2 squareRoot(big_2 n)
{
	/*We are using n itself as initial approximation
	 *    This can definitely be improved */
	big_2 x = n;
	big_2 y = 1;
	big_2 two = 2;
	//float e = 0.000001; /* e decides the accuracy level*/
	big_2 e = 1; /* e decides the accuracy level*/
	LOG(5) std::cout << "x = " << x  << "\n"; 
	LOG(5) std::cout << "y = " << y << "\n"; 
	LOG(5) std::cout << "x - y = " << x - y << "\n"; 
	int count = 0;
	//while(x - y > e)
	while(x > y )// is this a right approach ? 
	{
		count++;
	LOG(5) std::cout << "x - y = " << x - y << "\n"; 
		LOG(5) std::cout << "while x" << x  << "\n"; 
		LOG(5) std::cout << "while y" << y  << "\n"; 
		big_2 tmp = x + y;
		LOG(5) std::cout << "while tmp" << tmp  << "\n"; 
		//std::cout << "bigger tmp" << tmp  << "\n"; 
		//x = (x + y)/two;
		x = (tmp)/two;
		y = n/x;
		LOG(5) std::cout << "while1 x" << x  << "\n"; 
		LOG(5) std::cout << "while1 y" << y  << "\n"; 
		LOG(5) std::cout << "while1 tmp" << tmp  << "\n"; 
		//if (count ==25)
		//exit(0);
	}
	return x;
}


