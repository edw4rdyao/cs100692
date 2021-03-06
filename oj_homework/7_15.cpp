#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

struct node {
	double data;
	node* next;
};

//功能：求最大宽度
int wide(double t) {
	int wide = 1;
	int n = int(floor(t));
	if (t < 0) wide++;
	while (n/10) {
		wide++;
		n = n / 10;
	}
	return wide+4;
}

int main() {
	int width_m = 0;
	double t;
	node* head = new(nothrow) node;
	//检验是否申请成功
	if (head == NULL) {
		cout << "No Memory" << endl;
		exit(0);
	}
	node* p = head;
	cout << "请输入一些浮点数，以q结束:\n";
	cin >> t;
	while (1) {
		p->data=t;
		if (width_m < wide(p->data))
			width_m = wide(p->data);
		cin >> t;
		if (!cin.fail()) {
			p->next = new(nothrow) node;
			if (p->next == NULL) {
				cout << "No Memory" << endl;
				exit(0);
			}
			p = p->next;
		}
		else {
			p->next = NULL;
			break;
		}
	}
	p = head;
	while (p!=NULL) {
		if (p->data > 0) {
			p->data = floor(p->data * 1000) / 1000;
		}
		else {
			p->data = ceil(p->data * 1000) / 1000;
		}
		cout.width(width_m);
		cout.setf(ios::right);
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << p->data << endl;
		p = p->next;
	}
	p = head;
	node* q;
	//释放申请的内存
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	return 0;
}