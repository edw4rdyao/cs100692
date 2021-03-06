#include <iostream>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
#include<cmath>

class integral{
public:
     virtual double value()=0;
};


class integral_sin:public integral{
public:
     double value(){
          double value=0;
          double dx=(max-min)/10000.0;
          for(int i=0;i<=10000;i++){
               value+=dx*sin(min+i*dx);
          }
          return value;
     }
     friend istream& operator>>(istream& cin,integral_sin& sin);
private:
     double max;
     double min;
};

istream& operator>>(istream& cin,integral_sin& sin){
     cin>>sin.min>>sin.max;
     return cin;
}

class integral_cos:public integral{
public:
     double value(){
          double value=0;
          double dx=(max-min)/10000.0;
          for(int i=0;i<=10000;i++){
               value+=dx*cos(min+i*dx);
          }
          return value;
     }
     friend istream& operator>>(istream& cin,integral_cos& cos);
private:
     double max;
     double min;
};

istream& operator>>(istream& cin,integral_cos& cos){
     cin>>cos.min>>cos.max;
     return cin;
}

class integral_exp:public integral{
public:
     double value(){
          double value=0;
          double dx=(max-min)/10000.0;
          for(int i=0;i<=10000;i++){
               value+=dx*exp(min+i*dx);
          }
          return value;
     }
     friend istream& operator>>(istream& cin,integral_exp& exp);
private:
     double max;
     double min;
};

istream& operator>>(istream& cin,integral_exp& exp){
     cin>>exp.min>>exp.max;
     return cin;
}

/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral *p;

    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "sinxdx的计算结果为：" << (p->value()) << endl;

    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "cosxdx的计算结果为：" << (p->value()) << endl;

    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "expxdx的计算结果为：" << (p->value()) << endl;

     //OJ
    cout<<"\n----------------END---------------\n";
    system("pause");
    //OJ

    return 0;
}
