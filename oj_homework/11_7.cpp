
#include<iostream>
#include<time.h>
using namespace std;

bool IsLeapYear(int year_t){
    if ((year_t % 4 == 0 && year_t % 100 != 0) || year_t % 400 == 0) return true;
    else return false;
}

int GetYear(int& days_t){
    int Y = days_t / 365;
    int D = days_t % 365;
    int  YY = Y - 1;
    D -= YY / 4;
    D += YY / 100;
    D -= (YY + 300) / 400;
    while (D <= 0){
        Y--;
        D += IsLeapYear(Y + 1900) ? 366 : 365;
    }
    days_t = D;
    return Y + 1900;
}

int GetMonth(int& days_t,bool is_leap){
    int month_tab[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    month_tab[1]=is_leap?29:28;
    int month_t=1;
    for(int i=0;i<12;i++){
        if(days_t-month_tab[i]>0){
            month_t++;
            days_t-=month_tab[i];
        }
        else break;
    }
    return month_t;
}


class Date{
protected:
    int year;
    int month;
    int day;
public:
    Date();
    Date(int year_t,int month_t,int day_t);
    void set(int year_t,int month_t=1,int day_t=1);
    int ComputeDays();
    friend ostream& operator<<(ostream&,Date&);
    Date(int days_t);
    operator int();
};

class Time{
protected:
    int h, m, s;
public:
    Time();
    Time(int ,int ,int );
    Time(int );
    void set(int ,int, int);
    void set(int );
    Time operator+(int );
    Time operator-(int );
    Time& operator+=(int );
    Time& operator-=(int ); 
    Time& operator=(int);
    friend ostream& operator<<(ostream&,Time&);
    friend istream& operator>>(istream&,Time&);
    friend bool operator>(Time&,Time&);
    friend bool operator<(Time&,Time&);
    friend bool operator>=(Time&,Time&);
    friend bool operator<=(Time&,Time&);
    friend bool operator==(Time&,Time&);
    friend bool operator!=(Time&,Time&);
    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);
};

class DateTime:private Date,private Time{
public:
    DateTime();
    DateTime(int ,int ,int);
    DateTime(int ,int ,int,int ,int ,int);
    DateTime(int);
    void set(int ,int ,int,int ,int ,int);
    void set(int ,int ,int);
    void set(long long );
    long long gets_s();
    DateTime operator+(int );
    DateTime operator-(int );
    DateTime& operator+=(int );
    DateTime& operator-=(int );
    DateTime& operator++();
    DateTime operator++(int );
    DateTime& operator--();
    DateTime operator--(int );
    friend ostream& operator<<(ostream&,DateTime&);
    friend istream& operator>>(istream&,DateTime&);
    friend bool operator>(DateTime&,DateTime&);
    friend bool operator<(DateTime&,DateTime&);
    friend bool operator>=(DateTime&,DateTime&);
    friend bool operator<=(DateTime&,DateTime&);
    friend bool operator==(DateTime&,DateTime&);
    friend bool operator!=(DateTime&,DateTime&);
};

//DateTime的功能
DateTime::DateTime(){
    Date();
    Time();
}

DateTime::DateTime(int s_s){
    Date();
    Time(s_s);
}

DateTime::DateTime(int h_t,int m_t,int s_t){
    Date();
    Time(h_t, m_t, s_t);
}

DateTime::DateTime(int year_t, int month_t, int day_t,int h_t,int m_t,int s_t){
    Date(year_t,month_t,day_t);
    Time(h_t, m_t, s_t);
}

void DateTime::set(int year_t, int month_t, int day_t,int h_t,int m_t,int s_t){
    Date::set(year_t,month_t,day_t);
    Time::set(h_t, m_t, s_t);
}

void DateTime::set(int year_t, int month_t, int day_t){
    Date::set(year_t,month_t,day_t);
}

void DateTime::set(long long s_s){
    int days=s_s/3600*24;
    Date(days);
    int s_s_t=s_s-days*3600*24;
    Time(s_s_t);
}

long long DateTime::gets_s(){
    Date date(year,month,day);
    return (int)date*3600*24+3600*h+m*60+s;
}

ostream& operator<<(ostream& cout,DateTime& datetime_t){
    cout<<datetime_t.year<<"年"<<datetime_t.month<<"月"<<datetime_t.day<<"日 ";
    if(datetime_t.h<10) cout<<"0";
    cout<<datetime_t.h<<":";
    if(datetime_t.m<10) cout<<"0";
    cout<<datetime_t.m<<":";
    if(datetime_t.s<10) cout<<"0";
    cout<<datetime_t.s;
    return cout;
}

istream& operator>>(istream& cin,DateTime& datetime_t){
    cin>>datetime_t.year>>datetime_t.month>>datetime_t.day>>datetime_t.h>>datetime_t.m>>datetime_t.s;
    return cin;
}

bool operator>(DateTime& datetime_1,DateTime& datetime_2){
    return datetime_1.gets_s()>datetime_2.gets_s();
}

bool operator<(DateTime& datetime_1,DateTime& datetime_2){
    return datetime_1.gets_s()<datetime_2.gets_s();
}

bool operator>=(DateTime& datetime_1,DateTime& datetime_2){
    return datetime_1.gets_s()>=datetime_2.gets_s();
}

bool operator<=(DateTime& datetime_1,DateTime& datetime_2){
    return datetime_1.gets_s()<=datetime_2.gets_s();
}

bool operator==(DateTime& datetime_1,DateTime& datetime_2){
    return datetime_1.gets_s()==datetime_2.gets_s();
}

bool operator!=(DateTime& datetime_1,DateTime& datetime_2){
    return datetime_1.gets_s()!=datetime_2.gets_s();
}

DateTime DateTime::operator+(int s_t){
    DateTime datetime(gets_s()+s_t);
    return datetime;
}

DateTime DateTime::operator-(int s_t){
    DateTime datetime(gets_s()-s_t);
    return datetime;
}

DateTime& DateTime::operator+=(int s_t){
    set(gets_s()+s_t);
    return *this;
}

DateTime& DateTime::operator-=(int s_t){
    set(gets_s()-s_t);
    return *this;
}

DateTime& DateTime::operator++(){
    set(gets_s()+1);
    return *this;
}

DateTime DateTime::operator++(int ){
    DateTime datetime(gets_s()+1);
    set(gets_s()+1);
    return datetime;
}

DateTime& DateTime::operator--(){
    set(gets_s()-1);
    return *this;
}

DateTime DateTime::operator--(int ){
    DateTime datetime(gets_s()-1);
    set(gets_s()-1);
    return datetime;
}

//Time的功能

Time::Time(){
    h=0;m=0;s=0;
}

Time::Time(int h_t,int m_t,int s_t){
    h=h_t;m=m_t;s=s_t;
}

Time::Time(int s_s){
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
}

void Time::set(int h_t,int m_t,int s_t ){
    if(h_t!=-1) h=h_t;
    if(m_t!=-1) m=m_t;
    if(s_t!=-1) s=s_t;
}

void Time::set(int s_s){
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
}

ostream& operator<<(ostream& cout,Time& time_t){
    if(time_t.h<10) cout<<"0";
    cout<<time_t.h<<":";
    if(time_t.m<10) cout<<"0";
    cout<<time_t.m<<":";
    if(time_t.s<10) cout<<"0";
    cout<<time_t.s;
    return cout;
}

istream& operator>>(istream& cin,Time& time_t){
    cin>>time_t.h>>time_t.m>>time_t.s;
    return cin;
}

Time Time::operator+(int s_t){
    Time time_t;
    int s_s=3600*h+m*60+s;
    s_s+=s_t;
    time_t.h=s_s/3600;
    time_t.m=(s_s-h*3600)/60;
    time_t.s=s_s-h*3600-m*60;
    return time_t;
}

Time Time::operator-(int s_t){
    Time time_t;
    int s_s=3600*h+m*60+s;
    s_s-=s_t;
    time_t.h=s_s/3600;
    time_t.m=(s_s-h*3600)/60;
    time_t.s=s_s-h*3600-m*60;
    return time_t;
}

Time& Time::operator+=(int s_t){
    int s_s=3600*h+m*60+s;
    s_s+=s_t;
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return *this;
}

Time& Time::operator-=(int s_t){
    int s_s=3600*h+m*60+s;
    s_s-=s_t;
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return *this;
}

Time& Time::operator=(int s_s){
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return *this;
}

bool operator>(Time& t_1,Time& t_2){
    return (t_1.h*3600+t_1.m*60+t_1.s)>(t_2.h*3600+t_2.m*60+t_2.s);
}

bool operator<(Time& t_1,Time& t_2){
    return (t_1.h*3600+t_1.m*60+t_1.s)<(t_2.h*3600+t_2.m*60+t_2.s);
}

bool operator>=(Time& t_1,Time& t_2){
    return (t_1.h*3600+t_1.m*60+t_1.s)>=(t_2.h*3600+t_2.m*60+t_2.s);
}

bool operator<=(Time& t_1,Time& t_2){
    return (t_1.h*3600+t_1.m*60+t_1.s)<=(t_2.h*3600+t_2.m*60+t_2.s);
}

bool operator==(Time& t_1,Time& t_2){
    return (t_1.h*3600+t_1.m*60+t_1.s)==(t_2.h*3600+t_2.m*60+t_2.s);
}

bool operator!=(Time& t_1,Time& t_2){
    return (t_1.h*3600+t_1.m*60+t_1.s)!=(t_2.h*3600+t_2.m*60+t_2.s);
}

Time& Time::operator++(){
    int s_s=3600*h+m*60+s;
    s_s+=1;
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return *this;
}

Time Time::operator++(int){
    int s_s=3600*h+m*60+s;
    Time time_t(s_s);
    s_s+=1;
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return time_t;
}

Time& Time::operator--(){
    int s_s=3600*h+m*60+s;
    s_s-=1;
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return *this;
}

Time Time::operator--(int){
    int s_s=3600*h+m*60+s;
    Time time_t(s_s);
    s_s-=1;
    h=s_s/3600;
    m=(s_s-h*3600)/60;
    s=s_s-h*3600-m*60;
    return time_t;
}


//Date的功能

Date::Date(){
    time_t now_time=time(NULL);
    tm* now=localtime(&now_time);
    year=now->tm_year+1900;
    month=now->tm_mon+1;
    day=now->tm_mday;
}

Date::Date(int year_t,int month_t,int day_t){
    year=year_t;
    month=month_t;
    day=day_t;
}

void Date::set(int year_t,int month_t,int day_t){
    if(year_t!=0)  year=year_t;
    if(month_t!=0) month=month_t;
    if(day_t!=0) day=day_t;
}

int Date::ComputeDays(){
    int tab[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (IsLeapYear(year)) {
        tab[1] = 29;
    }
    int sum = 0;
    for (int i = 0; i < month -1; i++) {
        sum += tab[i];
    }
    sum = sum + day;
    return sum;
}   

ostream& operator<<(ostream& cout,Date& date_t){
    cout<<date_t.year<<"年"<<date_t.month<<"月"<<date_t.day<<"日";
    return cout;
}

Date::Date(int days_t){
    year=GetYear(days_t);
    month=GetMonth(days_t,IsLeapYear(year));
    day=days_t;
}

Date::operator int(){
    int days_t=0;
    for(int i=year-1900;i>0;i--){
        days_t+=(IsLeapYear(1900+i-1)?366:365);
    }
    days_t+=ComputeDays();
    return days_t;
}
