#include<iostream> 
#include<fstream>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};

//字符数组复制函数
void tj_strcpy(char* s1, const char* s2){
	int i = 0;
	for (; *(s2 + i) != 0; i++) {
		*(s1 + i) = *(s2 + i);
	}
	*(s1 + i) = 0;
}

//显示函数
void print_stu(student* head)
{
	struct student* p = head;
	cout << "所有学生的信息如下：" << endl;
	while(p!=NULL) {
		cout<<"学号:" << p->no << " " <<"姓名:"<< p->name << " " << "分数:" << p->score << endl;
		p = p->next;
	}
}

//释放内存函数
void delete_stu(student* head) {
	struct student* p = head;
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
}

//读取函数
student* read_stu() {

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
		cout << "Error opening file";
		exit(1);
	}
	else {
		fp >> N;
		for (int i = 0; i < N && (!fp.eof()); i++) {
			fp >> p->no >> p->name >> p->score;
			if (i != N - 1) {
				p->next = new(nothrow) student;
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
	return head;
}

//交换函数
void swap_stu(student* p,student* q) {
	student temp = {0};

	temp.no = p->no;
	p->no = q->no;
	q->no = temp.no;

	tj_strcpy(temp.name ,p->name);
	tj_strcpy(p->name , q->name);
	tj_strcpy(q->name , temp.name);

	temp.score = p->score;
	p->score = q->score;
	q->score = temp.score;
}

//排序函数
void sort_stu(student* head) {
	student* p = head;
	student* q =NULL;
	while(p != NULL) {
		q = p->next;
		while (q != NULL) {
			if (q->score > p->score) {
				swap_stu(p, q);
			}
			else if ((q->score == p->score) && (q->no < p->no)) {
				swap_stu(p, q);
			}
			q = q->next;
		}
		p = p->next;
	}
}

int main() {
	struct student* head = read_stu();
	sort_stu(head);
	print_stu(head);
	delete_stu(head);
	return 0;
}