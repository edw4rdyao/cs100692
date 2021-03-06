#include <iostream>
using namespace std;

class Array{
public:
    Array operator+(const Array&);
    friend istream& operator>>(istream&,Array&);
    friend ostream& operator<<(ostream&,Array&);
private:
    int _array[2][3];
};

istream& operator>>(istream& cin,Array& array_t){
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            cin>>array_t._array[i][j];
        }
    }
    return cin;
}

ostream& operator<<(ostream& cout,Array& array_t){
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            cout<<array_t._array[i][j]<<"   ";
        }
        cout<<endl;
    }
    return cout;
}
Array Array::operator+(const Array& array_a){
    Array array_c;
   for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            array_c._array[i][j]=array_a._array[i][j]+_array[i][j];
        }
    }
    return array_c;
}

int main(){

    Array a, b, c;         // 固定2行3列
    cin>>a>>b;  // 从键盘读取矩阵a ,b的数据
    c = a + b;
    cout<<c;
    return 0;
}