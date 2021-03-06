#include<iostream> 
#include<fstream>
using namespace std;

struct student {
	int no;
	char name[20];
	int score;
	struct student* next;
};

//显示函数
void print_stu(student* head)
{
	struct student* p = head;
	cout << "学生的信息如下：" << endl;
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

//判断是否继续操作函数
bool isContinue() {
	cout << "是否继续?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')return true;
	return false;
}

//删除函数
struct student* cut_stu(student* head) {
	int cut_no = 0;
	student* p = NULL;
	student* q = NULL;
	bool is_cut = 0;
	while (1) {
		cin >> cut_no;
		p = head;
		is_cut = 0;
		while (p != NULL) {
			if (p->no == cut_no) {
				if (p == head) {
					head = p->next;
					delete p;
				}
				else {
					q->next = p->next;
					delete p;
				}
				is_cut = 1;
				break;
			}
			q = p;
			p = p->next;
		}
		if (!is_cut) cout << "不存在" << endl;
		if (!isContinue()) break;
	}
	return head;
}

int main() {
	struct student* head = read_stu();
	head=cut_stu(head);
	print_stu(head);
	delete_stu(head);
	return 0;
}