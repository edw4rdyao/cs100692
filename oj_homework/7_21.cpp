#include <iostream>
using namespace std;

void itobs(int num, char* buffer) {
	size_t n = 0;
	for (size_t i = 0; i < 35; i++) {
		if ( (n > 0) && (n % 8 == 0)) {
			buffer[i] = ' ';
			n = 0;
		}
		else {
			if (num & 0x80000000) {
				buffer[i] = '1';
				num = num << 1;
				n++;
			}
			else {
				buffer[i] = '0';
				num = num << 1;
				n++;
			}
		}
	}
}

int main(){

	int num = 0;
	char buffer[36] = {0};

	cout << "请输入一些整数：\n";

	while (true) {
		cin >> num;
		if (cin.fail()) break;
		itobs(num,buffer);
		cout << num << "的二进制为：" << buffer << endl;
	}

	return 0;
}