#include "big.h"

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
	size = str.size();
	std::cout << "contructor big: size" <<(int) size << "\n";
	//std::cout << "condtructor big: strlen" <<(int) str.size() << "\n";
	if (size >= BIG_SIZE) {
		cout << " to big number " << str << "\n";
		throw "throw something";
	}
	for (int i=0, j = size - 1; i<BIG_SIZE; i++, j--){
		if (j >= 0)
			number[i] = str[j] - '0';
		else
			number[i] = 0;
	}
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
			tmp.number[i] = number[i] + other.number[i];
			
				//std::cout << "operator_+ i " << i << "\n";
				//std::cout << "number+ i " << (int) tmp.number[i] << "\n";
				//std::cout << "number+ i " << (int) other.number[i] << "\n";
				//std::cout << "number+ i " << (int) number[i] << "\n";
			if(tmp.number[i] > 9){
				tmp.number[i] -= 10;
				tmp.number[i+1] += 1;
				//std::cout << "operator+ i " << i << "\n";
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
				tmp.number[i] += 10;
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
				tmp.number[i] += 10;
				//curr.number[i+1] -= 1;
				tmp.number[i+1] -= 1;
				//std::cout << "tmp operator+ i " << i+1 << "=" << (int) tmp.number[i+1] << "\n";
			}
			//std::cout << "operator+ i " << (int)i << "\n";
			//std::cout << "operator+ size " << (int)tmp.size<< "\n";
			if( i+1 == tmp.size && tmp.number[i] == 0) {
				tmp.size--;
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
	tmp.size = size + other.size - 1;
	int tmp_size = tmp.size;
	if( sign == other.sign)
		tmp.sign = 0; 
	else  
		tmp.sign = 1; 
	
	//std::cout << "operator * tmp_size "<< (int) tmp_size << "\n";
	int offset = 0;
	for (int i = 0; i < other.size; i++, offset++) {
		if( other.number[i] == 0)
			continue;

		for (int j = 0; j < size; j++) {
			tmp.number[j + offset] += number[j] * other.number[i];
			//std::cout << "operator * tmp number "<< (int) tmp.number[j + offset] << "\n";
			if (tmp.number[j + offset] > 9){
				int tmp_number = tmp.number[j + offset];
				tmp.number[j + offset] =  tmp_number % 10;
				tmp.number[j + offset + 1] = tmp_number / 10;
				//std::cout << "operator * tmp number++ "<< (int) tmp.number[j + offset +1] << "\n";
				if( j + offset + 1 == tmp.size) {
					tmp.size++;
				}
			}
		}
	}
	return tmp;
}
std::ostream& operator<<(std::ostream& os, const big& obj){
	if (obj.sign == 1)
		os << "-";
	for (int i = obj.size - 1; i>=0; i--){
		//if (obj.number[i] == -1)
		//	continue;
		//os <<"|" <<static_cast<unsigned int>(obj.number[i]);
		os <<static_cast<unsigned int>(obj.number[i]);
	}
	//os << "\n";  
	//os << "size " <<(int) obj.size <<"\n";  
	//os << "sign " <<(int) obj.sign <<"\n";  
	return os;  
}
