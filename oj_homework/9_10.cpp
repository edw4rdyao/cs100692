#include<iostream>
using namespace std;

char* MyStrcpy(char* str_d,const char* str_t,size_t size=1024){
    size_t i=0;
    for(;*(str_t+i)!=0&&i<size;i++){
        *(str_d+i)=*(str_t+i);
    }
    *(str_d+i)=0;
    return str_d;
}

class Book_Sale{
private:
    char *isbn;          // 指向书籍编号的指针
                         // 存放书籍编号的空间需动态申请
                         //书籍编号由5段13位数字组成，如978-7-121-15535-2
    int sold;            // 销售量
    double sellingprice; // 原始价格
    double saleprice;    // 实售价格
    double discount;     // 折扣
    double total;        // 销售总额
public:
    Book_Sale(istream &);
    ~Book_Sale();
    void book_set(istream &);
    void book_display();
    char book_last_code(const char*);
};

Book_Sale::Book_Sale(istream& in){
    isbn=new char[18];
    if(isbn==NULL){
        cout<<"isbn is no memory!";
        exit(0);
    }
    MyStrcpy(isbn,"978-7-121-");
    in>>(isbn+10);
    *(isbn+15)='-';
    *(isbn+16)=book_last_code(isbn);
    *(isbn+17)=0;
    book_last_code(isbn);
    in>>sold>>sellingprice>>discount;
    saleprice=sellingprice*discount;
    total=saleprice*sold;
}

Book_Sale::~Book_Sale(){
    delete [] isbn;
    isbn=NULL;
}

char Book_Sale::book_last_code(const char* s){
    int sum=0,r=0;
    for(int i=0,j=1;i<16;i++){
        if(*(s+i)>='0'&&*(s+i)<='9'){
            if(j%2==1) sum+=int(*(s+i)-'0');
            else sum+=3*int(*(s+i)-'0');
            j++;
        }
    }
    r=10-sum%10;
    if(r==10) return '0';
    else return '0'+r;
}

void Book_Sale::book_set(istream & in){
    in>>(isbn+10);
    if(*(isbn+10)=='-') exit(0);
    *(isbn+15)='-';
    *(isbn+16)=book_last_code(isbn);
    *(isbn+17)=0;
    in>>sold>>sellingprice>>discount;
    saleprice=sellingprice*discount;
    total=saleprice*sold;
}

void Book_Sale::book_display(){
    cout.setf(ios::fixed);
    cout.precision(6);
    cout<<"该书的ISBN号为:"<<isbn<<"\n销量为:"<<sold<<"本 原价为:"<<sellingprice<<"元 折扣为:"<<discount<<" 现价为:"<<saleprice<<"元 总销售额为:"<<total<<"元\n";
}

int main(){
    Book_Sale book_a(cin);
    book_a.book_display();
    while(true){
        book_a.book_set(cin);
        book_a.book_display();
    }
    return 0;
}