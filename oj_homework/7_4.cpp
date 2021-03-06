#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<cstdlib>
using namespace std;

struct student {
	int no;                
	char name[20];        
	int score;           
	struct student* next;  
};

void print_stu(student* head,int N)
{
	struct student* p = head;
	cout << "所有学生的信息如下：" << endl;
	for (int i = 0; i < N; i++) {
		cout<<"学号:" << p->no << " " <<"姓名:"<< p->name << " " << "分数:" << p->score << endl;
		p = p->next;
	}
}

int main() {

	struct student* head = (student*)malloc(sizeof(student));
	//检测是否申请成功
	if (head == NULL) {
		cout << "No Memory" << endl;
		return 0;
	}
	student* p = head;
	int N = 0;
	FILE* fp;

	//读取文件
	fp = fopen("d:\\student.txt", "r");
	if (fp == NULL) {
		printf("Open filefailure!");
		exit(1);
	}
	else {
		(void)fscanf(fp, "%d \n", &N);
		for (int i = 0; i < N; i++) {
			(void)fscanf(fp, "%d %s %d \n", &p->no, p->name, &p->score);
			if (i != N - 1) {
				p->next = (student*)malloc(sizeof(student));
				if (p->next == NULL) {
					cout << "No Memory" << endl;
					return 0;
				}
				p = p->next;
			}
			else {
				p->next = NULL;
			}
		}
	}
	//关闭文件
	fclose(fp);

	//输出学生数据
	print_stu(head, N);

	//释放申请的内存
	p = head;
	struct student* q = head->next;
	while (p != NULL) {
		free(p);
		if (q != NULL) {
			p = q->next;
			free(q);
			if (p != NULL) {
				q = p->next;
			}
		}
		else {
			break;
		}
	}
	head = NULL;
	return 0;
}