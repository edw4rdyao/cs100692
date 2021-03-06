#include<iostream> 
using namespace std;


istream& f(istream& in) {
	int tmp;
	while (!in.eof()) {
		in >> tmp;
		if (in.fail()){
			cerr << "illegal，你的输入不合法，请重新输入" << endl;
			in.clear(istream::goodbit);
			in.ignore(100,' ');
		}
		else if(tmp==-1) {
			in.clear();
			return in;
		}
		else {
			cout << "你说了：" << tmp << endl;
		}
	}
	in.clear();
	return in;
}

int main() {
	f(cin);
	return 0;
}
