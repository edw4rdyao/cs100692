#include <iostream>
using namespace std;

class Array{
public:
    void display();
    void readFromKeyboard();
    friend Array operator+(const Array&,const Array&);
private:
    int _array[2][3];
};

Array operator+(const Array& array_a,const Array& array_b){
    Array array_c;
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            array_c._array[i][j]=array_a._array[i][j]+array_b._array[i][j];
        }
    }
    return array_c;
}

void Array::readFromKeyboard(){
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            cin>>_array[i][j];
        }
    }
}

void Array::display(){
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            cout<<_array[i][j]<<"   ";
        }
        cout<<endl;
    }
}


int main(){

    Array a, b, c;         // 固定2行3列
    a.readFromKeyboard();  // 从键盘读取矩阵a的数据
    b.readFromKeyboard();  // 从键盘读取矩阵b的数据
    c = a + b;
    c.display();
    return 0;
}