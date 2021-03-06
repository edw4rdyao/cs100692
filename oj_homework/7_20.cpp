#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
	if (argc != 2) {
        cerr << "请确保输入参数正确" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "无法打开输入文件" << endl;
        return -1;
    }
	/*ifstream in("noise.txt", ios::in );
	if (!in) {
		cerr << "无法打开文件" << endl;
		return -1;
	}*/
	
	ofstream out("noise_red.txt", ios::out );
	if (!out) {
		cerr << "无法打开文件" << endl;
		return -1;
	}

	char ch;
	int i = 0;
	while (1) {
		i++;

		ch = in.get();

		if (ch == EOF) break;

		if (i % 3 == 1) {
			out.put(ch);
		}
	}


	in.close();
	out.close();
	return 0;
}