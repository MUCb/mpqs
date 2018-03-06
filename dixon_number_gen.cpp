#include <stdio.h>
#include <iostream>
#include <vector>

int main () {
	std::vector<long long> number;
	number.push_back(2);
	number.push_back(3);
	int count = 1;

	for(int i = 4; i < 9999; i++) {
		int res = 0;
		int flag = 0;
		for (int j = 0; j < number.size(); ++j) {
			res = i % number[j];
			if (res == 0) {
				res = i / number[j];
				res = res % number[j];
				if (res == 0) {
					flag = 1;
					break;
				}
			}
		}
		if (!flag) {
			number.push_back(i);
			std::cout << i << ",\t";
			count++;
		}
		if (!(count % 11)){
			std::cout << std::endl;
			count = 1;
		}

	}
}