#include<iostream> 
#include<fstream>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};


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

	struct student* head = new student;
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
	return head;
}

//统计函数
void sta_stu(student* head) {
	struct student* p = head;
	int sta[5] = {0};
	while (p != NULL) {
		switch (p->score/10)
		{
		case(10):
		case(9):
			sta[0]++;
			break;
		case(8):
			sta[1]++;
			break;
		case(7):
			sta[2]++;
			break;
		case(6):
			sta[3]++;
			break;
		default:
			sta[4]++;
			break;
		}
		p = p->next;
	}
	cout << "统计信息如下:" << endl;
	cout << "优:" << sta[0] << "人  " << "良:" << sta[1] << "人  " << "中:" << sta[2] << "人  " << "及格:" << sta[3] << "人  " << "不及格:" << sta[4] << "人" << endl ;
}

int main() {
	struct student* head = read_stu();
	sta_stu(head);
	delete_stu(head);
	return 0;
}