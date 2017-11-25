#include "big_2.h"
#include <math.h>

big::big(std::string _str) {
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
	//std::cout << "contructor big: sign" <<(int) sign << "\n";
	size = str.size() / 3;
    if (str.size() % 3)
        size++;
	//std::cout << "contructor big: size" <<(int) size << "\n";
	//std::cout << "condtructor big: strlen" <<(int) str.size() << "\n";
	if (size >= (BIG_SIZE * 3)) {
		//cout << " to big number " << str << "\n";
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

big::big(long long n) {
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
big big::operator+(const big other) const
{
	big tmp;
	big curr = *this;
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
big big::operator-(const big other) const{
	big tmp = *this;
	big curr = *this;
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

big big::operator*(const big other) const{
	big tmp;
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

big big::operator/(const big other) const{
	std::cout << " other |" << other << "|\n";
	std::cout << " other size |" << (int)other.size << "|\n";
	std::cout << " this |" << *this << "|\n";
	std::cout << " this size |" <<(int)  (*this).size << "|\n";
	big divident = *this;
	big divisor = other;
	big divisor10;
	big quotient;
	//big tmp;
	big one(1);
	big ten(10);
	int quot_size = 0;
	if (divident.sign == divisor.sign) {
		if ( divident.sign == 1) {
			divident.sign = 0;
			divisor.sign = 0;
		}
	} else {
		if ( divident.sign == 1){
			divident.sign = 0;
		} else {
			divisor.sign = 0;
		}
		quot_size = 0;
	}


	if ( divident > divisor) {
		int diff = divident.size - divisor.size - 1; 
		std::cout << " divisor |" << divisor << "|\n";
		std::cout << " divident |" << divident << "|\n";

		int part_divident = 0;
		int part_divisor = 0;
		int part_quotient = 0;
		big part_quotient_count = 0;
		//int part_divisor = 0;

		int j;
		int count = 0;
		part_divisor = divisor.number[divisor.size - 1];
        std::cout << "part_divisor |" << part_divisor << "|\n";
		//for(j = divisor.size - 1, count = 0; j >= 0, count < DIVISION_COUNT; j--, count++) {
		//	part_divisor = part_divisor * POSITIONAL_BASE + divisor.number[j];
		//}

        //int divident_iter = divident.size - 1;
        for(int divident_iter = divident.size - 1; divident_iter >= (divisor.size -1); divident_iter--){ 
            //std::cout << "debug " << __func__ << " " << __LINE__ << "\n"; 

            part_divident = divident.number[divident_iter];
            std::cout << "part_divident |" << part_divident << "|\n";

            if (part_divident < part_divisor){
                divident_iter--;
                std::cout << "divident_iter |" << divident_iter << "|\n";
                if ( divident_iter < 0){
                    std::cout << "error pertator/ divident less than divisor\n";
                    return quotient;
                } else {
                    part_divident = (part_divident * 1000) + divident.number[divident_iter];
                }
            }
            //part_divident++; // need add check for equal numbers
            part_quotient = part_divident / part_divisor;
            part_quotient_count = (part_quotient_count * 1000) + part_quotient;

            std::cout << "part_quotient |" << part_quotient << "|\n";
            part_divisor =  part_divisor - (part_quotient * part_divident);
        }


        std::cout << "part_quotient_count |" << part_quotient_count << "|\n";
        std::cout << "part_quotient_count1 |" << (part_quotient_count * divisor) << "|\n";
        quotient = divident - (part_quotient_count * divisor);
        std::cout << "part_quotient_count |" << part_quotient_count << "|\n";
        std::cout << " divident |" << divident << "|\n";
        //divident = divident - part_quotient_count;
        std::cout << " quotient |" << quotient << "|\n";
        while( divisor < quotient){
            quotient = quotient - divisor;
            part_quotient_count = part_quotient_count + one;
        }
        quotient = part_quotient_count;

#if 0
		part_divisor++;
        int align = 0;
		for (int iter = 0; iter < divident.size - divisor.size + DIVISION_COUNT; iter++) {
			int i;
			for( i = divident.size - 1 - (iter * DIVISION_COUNT) - align , count = 0; i >= 0, count < DIVISION_COUNT; i--, count++) {
				part_divident = part_divident * POSITIONAL_BASE + divident.number[i];
			}
			if (part_divident < part_divisor){
                align++;
				part_divident = part_divident * POSITIONAL_BASE + divident.number[i];
            }

			std::cout << "part_divident |" << part_divident << "|\n";
			part_quotient = part_divident / part_divisor;
			//part_quotient = (part_quotient * DIVISION_COUNT) + part_divident / part_divisor;
			part_quotient_count = (part_quotient_count *( pow((double) POSITIONAL_BASE , DIVISION_COUNT) )) + part_quotient;
			std::cout << "part_quotient |" << part_quotient << "|\n";
			std::cout << "part_quotient_count |" << part_quotient_count << "|\n";

		    part_divident = part_divident - (part_quotient * part_divisor);
		    std::cout << "part_quotient res |" << part_divident << "|\n";
		}

#endif
		//if (divident.size != 0)
		//	quotient = quotient + one;
	} else {
		quotient = one;
	}
	return quotient;
}

/* quotient is rounded to the next integer
 */
big div(const big divident1, const big divisor1) {
	//std::cout << " other |" << other << "|\n";
	//std::cout << " this |" << *this << "|\n";
	big divident = divident1;
	big divisor = divisor1;
	big divisor10;
	big quotient;
	big tmp;
	big one(1);
	big ten(10);
	int quot_size = 0;
	return quotient;
}


double ln(const big n) {
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

big big::operator%(const big other) const{
	//std::cout << " other |" << other << "|\n";
	//std::cout << " this |" << *this << "|\n";
	big divident = *this;
	big divisor = other;
	big divisor10;
	big tmp(1);
	return divident;
}

big big::operator%(const long long other) const{
	//std::cout << " other |" << other << "|\n";
	//std::cout << " this |" << *this << "|\n";
	big divident = *this;
	big divisor (other);
	big divisor10;
	big tmp(1);
	divident.sign = 0;
	divisor.sign = 0;
	return divident;
}


void big::pow10(int power) {
	for( int i = size - 1; i >= 0; i--) {
		number[i+power] = number[i];
		number[i] = 0;
	}
	size += power;
}

bool special_compare(const big one, const big other) {
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


bool big::operator<(const big other) const{
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

bool big::operator>(const big other) const{
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

bool big::operator==(const big other) const{
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



std::ostream& operator<<(std::ostream& os, const big& obj){
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
big squareRoot(big n)
{
	/*We are using n itself as initial approximation
	 *    This can definitely be improved */
	big x = n;
	big y = 1;
	big two = 2;
	//float e = 0.000001; /* e decides the accuracy level*/
	big e = 1; /* e decides the accuracy level*/
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
		big tmp = x + y;
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


