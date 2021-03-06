#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<cstdlib>
using namespace std;

struct node {
	int data;
	node* next;
};

//功能：从文件读取数据
void readFromFile(node* head) {
	FILE* fp;
	fp = fopen("d:\\1.txt", "r");
	if (fp == NULL) {
		printf("Open filefailure!");
		exit(1);
	}
	node* p = head;
	while (!feof(fp)) {
		(void)fscanf(fp, "%d ", &p->data);
		if (feof(fp)) {
			p->next = NULL;
		}
		else {
			p->next = new(nothrow) node;
			if (p->next == NULL) {
				cout << "no memory!\n";
				exit(0);
			}
			p = p->next;
		}
	}
	fclose(fp);
}

//功能：通过cin读取数据
void readFromStdin(node* head) {
	node* p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	cout << "请输入10个整数：\n";
	for (int i = 0; i < 11; i++) {
		if (i != 10) {
			p->next = new(nothrow) node;
			if (p->next == NULL) {
				cout << "no memory!\n";
				exit(0);
			}
			p = p->next;
			cin>>p->data;
		}
		else {
			p->next = NULL;
		}
	}
}

//功能：将数据从小到大排序
void sortFileData(node* head) {
	node* p = head;
	node* q = NULL;
	int t;
	while (p != NULL) {
		q = p->next;
		while (q != NULL) {
			if (q->data < p->data) {
				t = p->data;
				p->data = q->data;
				q->data = t;
			}
			q = q->next;
		}
		p = p->next;
	}
}

//功能：将排序后的数据写入out文件中
void outToFile(node* head) {
	node* p = head;
	FILE* fp;
	fp = fopen("1.out", "r+");
	while (p != NULL) {
		fprintf(fp, "%d ", p->data);
		p = p->next;
	}
	fclose(fp);
}

int main() {
	node* head=new(nothrow) node;
	if (head == NULL) {
		cout << "no memory!\n";
		return 0;
	}

	readFromFile(head);
	readFromStdin(head);
	sortFileData(head);
	outToFile(head);

	//释放申请的内存
	node* p = head;
	node* q;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	return 0;
}