#define BIG_SIZE 20

class big{
	char number[BIG_SIZE];
	char sign;
	big(){
		for (int i=0; i<BIG_SIZE; i++)
			number[i] = -1;
		sign = 0;
	}
	big(char * str);
	big& operator=(const big other)
	{
		for (int i=0; i<BIG_SIZE; i++)
			number[i] = other.number[i];
		sign = other.sign;
		return *this;
	}
	big& operator+(const big other) const;
}

big::big(char * str) {
	if (*str == '-')
		sign = 1;

	for (int i=0, j = strlen(str); i<BIG_SIZE || j > 0; i++, j--){
		if (*str == '-')
			break;
		number[i] = *(str + j) - '0';
	}
}

big& big::operator+(const big other) const
{
	big tmp;
	big curr = this;
	if( sign == other.sign){
		for (int i=0; i<BIG_SIZE; i++)
			tmp.number[i] = curr.number[i] + other.number[i];
			tmp.sign = curr.sign;
	} else {
		for (int i=0; i<BIG_SIZE; i++){
			if(curr.number[i] == -1 && other.number[i] == -1)
				break;
			else if (curr.number[i] == -1) {
				tmp.number[i] = other.number[i];
				tmp.sign = other.sign;
			} else if (other.number[i] == -1) {
				tmp.number[i] = curr.number[i];
				tmp.sign = curr.sign;
			} else if(curr.number[i] >= other.number[i])
				tmp.number[i] = curr.number[i] - other.number[i];
				tmp.sign = curr.sign;
			else{
				int t1, j, count;
				for(j=i+1, count= 1; j<BIG_SIZE; j++, count++) {
					if (curr.number[j] == 0)
						continue;
					
					if (curr.number[j] == -1){
						less_flag = 1;
						break;
					}
					t1 = curr.number[i] + (curr.number[j] * (10 * count));
					t1 -= other.number[i];
					tmp.number[i] = t1 % (10 * count);
					curr.number[j] = t1 / (10 * count);
					tmp.number[i] = tmp - other.number[i];
					break;
				}
				if (less_flag){
					tmp.number[i] = other.number[i] - curr.number[i];
					tmp.sign = other.sign;
				} else {
					tmp.sing = curr.sign;
				}
			}
		}
	}
	
}
