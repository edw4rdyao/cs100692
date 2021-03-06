#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#include<cstring>

class Teacher{
private:
    int id;
    int age;
    int gender;
    char name[16];
public:
    void set_info(int ,int , int , char* );
    void show_info();
};

class Student{
private:
    int id;
    int age;
    int gender;
    char name[16];
public:
    Student(int ,int , int, char* );
    void show_info();
    operator Teacher();
};

Student::operator Teacher(){
    Teacher teacher_t;
    teacher_t.set_info(id,age,gender,name);
    return teacher_t;
}

Student::Student(int id_t,int age_t, int gender_t, char* name_t){
    id=id_t;
    age=age_t;
    gender=gender_t;
    strcpy(name,name_t);
}

void Teacher::set_info(int id_t,int age_t, int gender_t, char* name_t){
    id=id_t;
    age=age_t;
    gender=gender_t;
    strcpy(name,name_t);
}

void Teacher::show_info(){
    cout<<"教师号:"<<id<<" 教师年龄:"<<age<<"岁 教师性别:";
    if(gender==1) cout<<"男 教师姓名:";
    else cout<<"女 教师姓名:";
    cout<<name;
}

void Student::show_info(){
    cout<<"学生学号:"<<id<<" 学生年龄:"<<age<<"岁 学生性别:";
    if(gender==1) cout<<"男 学生姓名:";
    else cout<<"女 学生姓名:";
    cout<<name<<endl;
}


int main() {
    int id, age, gender;
    char name[16];

    cin >> id >> age >> gender >> name;
    Student stu(id, age, gender, name);
    stu.show_info();

    Teacher teac;
    teac = (Teacher)stu;
    teac.show_info();
    return 0;
}