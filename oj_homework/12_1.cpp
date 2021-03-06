#include <iostream>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdio>
#include <cmath>
#define PI 3.14159265

class Shape{
public:
     virtual char* area()=0;
};

class Circle: public Shape{
public:
     Circle(double r_t){
          r=r_t;
          areastr=new(nothrow) char[80];
          if(areastr==NULL) exit(0);
     }
     char* area(){
          sprintf(areastr,"%s%.4lf","圆的面积为：",PI*r*r);
          return areastr;
     }
     ~Circle(){ delete [] areastr; }
private:
     double r;
     char* areastr;
}; 

class Square: public Shape{
public:
     Square(double side_t){
          side=side_t;
          areastr=new(nothrow) char[80];
          if(areastr==NULL) exit(0);
     }
     char* area(){
          sprintf(areastr,"%s%.4lf","正方形的面积为：",side*side);
          return areastr;
     }
     ~Square(){ delete [] areastr; }
private:
     double side;
     char* areastr;
};

class Rectangle: public Shape{
public:
     Rectangle(double length_t,double width_t){
          length=length_t;
          width=width_t;
          areastr=new(nothrow) char[80];
          if(areastr==NULL) exit(0);
     }
     char* area(){
          sprintf(areastr,"%s%.4lf","长方形的面积为：",length*width);
          return areastr;
     }
     ~Rectangle(){ delete [] areastr; }
private:
     double length;
     double width;
     char* areastr;
};

class Trapezoid:public Shape{
public:
     Trapezoid(double topline_t,double baseline_t,double height_t){
          topline=topline_t;
          baseline=baseline_t;
          height=height_t;
          areastr=new(nothrow) char[80];
          if(areastr==NULL) exit(0);
     }
     char* area(){
          sprintf(areastr,"%s%.4lf","梯形的面积为：",0.5*(topline+baseline)*height);
          return areastr;
     }
     ~Trapezoid(){ delete [] areastr; }
private:
     double topline;
     double baseline;
     double height;
     char* areastr;
};

class Triangle:public Shape{
public:
     Triangle(double a,double b,double c){
          side_a=a;
          side_b=b;
          side_c=c;
          areastr=new(nothrow) char[80];
          if(areastr==NULL) exit(0);
     }
     char* area(){
          double p = (side_a + side_b + side_c)/2.0;
          double s = sqrt(p*(p-side_a)*(p-side_b)*(p-side_c));
          sprintf(areastr,"%s%.4lf","三角形的面积为：",s);
          return areastr;
     }
     ~Triangle(){ delete [] areastr;}
private:
     double side_a;
     double side_b;
     double side_c;
     char* areastr;
};
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
     Circle c1(2);
     Square s1(3);
     Rectangle r1(4, 5);
     Trapezoid t1(6, 7, 8);
     Triangle t2(3, 4, 5);

     Shape *s[5] = { &c1,&s1,&r1,&t1,&t2 };

     for (int i = 0;i < 5;i++)
          cout << s[i]->area() << endl;
     
     //OJ
    cout<<"\n----------------END---------------\n";
    system("pause");
    //OJ
     return 0;
}
