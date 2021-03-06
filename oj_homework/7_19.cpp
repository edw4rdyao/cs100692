#undef __DEPRECATED
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;

//判断一个字符串是否为11位的正整数
bool isNumber(char* str){
	size_t i = 0;
	for (i = 0; str[i] != 0; i++){
		if (str[i] < '0' || str[i] > '9'){
			return false;
		}
	}
	if (i != 11){
		return false;
	}
	return true;
}

//从文件中查找电话号码
void valid(ifstream& in, const char* strBeg){
	long long number;
	long long numberBeg;
	char buff[200];
	istrstream strsBeg(strBeg, 3);
	strsBeg >> numberBeg;

	cout << "您查找到的电话号码如下:\n";
	while (!in.eof()){
		in >> buff;
		if (isNumber(buff)){
			istrstream strsNum(buff, 11);
			strsNum >> number;
			if (number >= numberBeg * 100000000 && number < (numberBeg + 1) * 100000000){
				cout << number << endl;
			}
		}
	}
}

int main(int argc, char* argv[]){
	if (argc != 3){
		cerr << "请给出文件名和前三位号码" << endl;
		return -1;
	}

	ifstream in(argv[1], ios::in);
	if (!in){
		cerr << "无法打开文件" << endl;
		return -1;
	}

	valid(in, argv[2]);
	in.close();
	return 0;
}