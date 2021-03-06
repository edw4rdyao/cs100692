#include<iostream>
#include "LZ77.h"
#include<Windows.h>

int main(int argc, char* argv[]) {

	//若参数不为4，则提示错误
	if (argc != 4) {
		cerr << "Please make sure the number of parameters is correct." << endl;
		return -1;
	}

	//如果第3个参数为zip则执行压缩程序
	if (!strcmp(argv[3], "zip")) {

		//计算压缩时间
		USL t = GetTickCount64();

		//执行压缩
		LZ77 lz;
		lz.CompressFile(argv[1], argv[2]);

		cout <<"Compress File Time: "<< (GetTickCount64() - t) / 1000.0 << "s";
		return 0;
	}
	//如果第3个参数为unzip则执行解压缩程序
	if(!strcmp(argv[3], "unzip")){

		//计算解压时间
		USL t = GetTickCount64();

		//执行解压
		LZ77 lz;
		lz.UnCompressFile(argv[1], argv[2]);

		cout << "Uncompress File Time: " << (GetTickCount64() - t) / 1000.0 << "s";
		return 0;
	}
	else {

		//命令错误
		cerr << "Unknown parameter!\nCommand list: zip unzip" << endl;
		return -1;
	}
}