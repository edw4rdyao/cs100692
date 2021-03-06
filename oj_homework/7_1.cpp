//7_1 日期计算器

#include <iostream>
using namespace std;

struct Date{
	int year;
	int month;
	int day;
};

int days1(Date date_t) {
	int days_feb, days=0;
	if ((date_t.year % 4 == 0 && date_t.year % 100 != 0) || (date_t.year % 400 == 0)) {
		days_feb = 29;
	}
	else {
		days_feb = 28;
	}
	switch (date_t.month) {
	case 1:
		days = date_t.day;
		break;
	case 2:
		days = date_t.day + 31;
		break;
	case 3:
		days = date_t.day + 31 + days_feb;
		break;
	case 4:
		days = date_t.day + 31 + days_feb + 31;
		break;
	case 5:
		days = date_t.day + 31 + days_feb + 31 + 30;
		break;
	case 6:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31;
		break;
	case 7:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30;
		break;
	case 8:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31;
		break;
	case 9:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31;
		break;
	case 10:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		break;
	case 11:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		break;
	case 12:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
	}
	return days;
}

int days2(Date* date_t) {
	int days_feb, days=0;
	if ((date_t->year % 4 == 0 && date_t->year % 100 != 0) || (date_t->year % 400 == 0)) {
		days_feb = 29;
	}
	else {
		days_feb = 28;
	}
	switch (date_t->month) {
	case 1:
		days = date_t->day;
		break;
	case 2:
		days = date_t->day + 31;
		break;
	case 3:
		days = date_t->day + 31 + days_feb;
		break;
	case 4:
		days = date_t->day + 31 + days_feb + 31;
		break;
	case 5:
		days = date_t->day + 31 + days_feb + 31 + 30;
		break;
	case 6:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31;
		break;
	case 7:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31 + 30;
		break;
	case 8:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31 + 30 + 31;
		break;
	case 9:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31;
		break;
	case 10:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		break;
	case 11:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		break;
	case 12:
		days = date_t->day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
	}
	return days;
}

int days3(Date & date_t) {
	int days_feb, days=0;
	if ((date_t.year % 4 == 0 && date_t.year % 100 != 0) || (date_t.year % 400 == 0)) {
		days_feb = 29;
	}
	else {
		days_feb = 28;
	}
	switch (date_t.month) {
	case 1:
		days = date_t.day;
		break;
	case 2:
		days = date_t.day + 31;
		break;
	case 3:
		days = date_t.day + 31 + days_feb;
		break;
	case 4:
		days = date_t.day + 31 + days_feb + 31;
		break;
	case 5:
		days = date_t.day + 31 + days_feb + 31 + 30;
		break;
	case 6:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31;
		break;
	case 7:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30;
		break;
	case 8:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31;
		break;
	case 9:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31;
		break;
	case 10:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30;
		break;
	case 11:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
		break;
	case 12:
		days = date_t.day + 31 + days_feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
	}
	return days;
}

int main(){
	Date date_s;
	Date* date_p = &date_s;
	Date& date_c = date_s;
	char key;
	int days=0;
	cout << "please input a date :";
	cin >> date_s.year >> date_s.month >> date_s.day;
	if (cin.fail()||date_s.month<1||date_s.month>12||date_s.day<1||date_s.day>31) {
		cout << "Illegal" << endl;
		exit(0);
	}
	if ((date_s.month == 4 || date_s.month == 6 || date_s.month == 9 || date_s.month == 11) && (date_s.day == 31)) {
		cout << "Illegal" << endl;
		exit(0);
	}
	if (!((date_s.year % 4 == 0 && date_s.year % 100 != 0) || (date_s.year % 400 == 0)) && date_s.month == 2 && date_s.day == 29) {
		cout << "Illegal" << endl;
		exit(0);
	}
	if (date_s.month == 2 && date_s.day == 30) {
		cout << "Illegal" << endl;
		exit(0);
	}
	cout << "please input a keyword:";
	cin >> key;
	switch (key)
	{
	case 'a':
		days=days1(date_s);
		break;
	case 'b':
		days = days2(date_p);
		break;
	case 'c':
		days = days3(date_c);
		break;
	default:
		break;
	}
	cout << endl <<date_s.year << "-" << date_s.month << "-" << date_s.day << " is the " << days << " th day in " << date_s.year;
	return 0;
}