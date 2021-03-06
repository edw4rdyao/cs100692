//查询成绩

#include<iostream>
using namespace std;

struct student{
	int no;
	char name[20];
	float score[3];
	float avrage_sc;
};

float get_score() {
	float score_t;
	cin >> score_t;
	if (cin.fail()||score_t<0||score_t>150) {
		cout << "illegal!";
		exit(0);
	}
	return score_t;
}

int get_no() {
	int no_s;
	cin >> no_s;
	if (cin.fail()||no_s<0) {
		cout << "illegal!";
		exit(0);
	}
	return no_s;
}

void get_info(student students_t[]) {
	cout << "please input the information: " << endl;
	int t=0;

	for (int i = 0; i < 10; i++) {

		students_t[i].no = get_no();
		
		cin>> students_t[i].name;
		for (int j = 0; students_t[i].name[j] != 0; j++) {
			t = int(students_t[i].name[j]);
			if ( (t>0&&t<65)||(t>90&&t<97)||(t>122&&t<256) ) {
				cout << "illegal!";
				exit(0);
			}
		}

		students_t[i].score[0] = get_score();
		students_t[i].score[1] = get_score();
		students_t[i].score[2] = get_score();
		students_t[i].avrage_sc = (students_t[i].score[0] + students_t[i].score[1] + students_t[i].score[2]) / 3;
	}
}

void get_average_sc(student students_t[]) {
	float sum_sc_1 = 0, sum_sc_2 = 0, sum_sc_3 = 0;
	for (int i = 0; i < 10; i++) {
		sum_sc_1 = sum_sc_1 + students_t[i].score[0];
		sum_sc_2 = sum_sc_2 + students_t[i].score[1];
		sum_sc_3 = sum_sc_3 + students_t[i].score[2];
	}
	cout <<"the average score : "<<endl<< sum_sc_1 / 10.0 << " " << sum_sc_2 / 10.0 << " " << sum_sc_3 / 10.0 << endl;
}

void find_top(student students_t[]) {
	cout << "the top student : " << endl;
	float top_sc = 0;
	for (int i = 0; i < 10; i++) {
		if (students_t[i].avrage_sc >= top_sc)
			top_sc = students_t[i].avrage_sc;
	}
	for (int i = 0; i < 10; i++) {
		if (students_t[i].avrage_sc == top_sc)
			cout<<"ID: " << students_t[i].no << " name: "<<students_t[i].name << " score: " << students_t[i].score[0] << " " << students_t[i].score[1] << " " << students_t[i].score[2] << " " << students_t[i].avrage_sc << endl ;
	}
}

int main() {
	student students[10];
	get_info(students);
	get_average_sc(students);
	find_top(students);
	return 0;
}