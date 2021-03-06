#include<iostream> 
#include<fstream>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};

void print_stu(student* head, int N)
{
	struct student* p = head;
	cout << "所有学生的信息如下：" << endl;
	for (int i = 0; i < N; i++) {
		cout<<"学号:" << p->no << " " <<"姓名:"<< p->name << " " << "分数:" << p->score << endl;
		p = p->next;
	}
}

int main() {

	struct student* head = new(nothrow) student;

	//检测是否申请成功
	if (head == NULL) {
		cout << "No Memory" << endl;
		return 0;
	}
	student* p = head;
	int N = 0;

	//读取文件
	ifstream fp("d:\\student.txt",ios::in);
	if (!fp.is_open()) {
		cout << "Open filefailure!";
		exit(1);
	}
	else {
		fp >> N;
		for (int i = 0; i < N && (!fp.eof()); i++) {
			fp >> p->no >> p->name >> p->score;
			if (i != N - 1) {
				p->next = new student;
				//检测是否申请成功
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
	fp.close();

	//输出学生数据
	print_stu(head, N);

	//释放申请的内存
	p = head;
	struct student* q = head->next;
	while (p != NULL) {
		delete p;
		if (q != NULL) {
			p = q->next;
			delete q;
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