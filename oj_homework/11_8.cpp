
#include<iostream>
using namespace std;

#include<cstring>

char last_code(const char* s){
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

class Book_Sale{
protected:
    char *isbn;          // 指向书籍编号的指针
                         // 存放书籍编号的空间需动态申请
                         //书籍编号由5段13位数字组成，如978-7-121-15535-2
    int sold;            // 销售量
    double sellingprice; // 原始价格
    double saleprice;    // 实售价格
    double discount;     // 折扣
    double total;        // 销售总额
public:
    Book_Sale();
    Book_Sale(int isbn_t, int sold_t,double sellingprice_t,double discount_t);
    Book_Sale(const Book_Sale& b_t);
    ~Book_Sale();
    void set(int isbn_t, int sold_t,double sellingprice_t,double discount_t=1);
    void display();
    friend ostream& operator<<(ostream&,Book_Sale&);
};

class Book_Sale_Limit: private Book_Sale {
protected:
    int limit;
public:
    Book_Sale_Limit();
    Book_Sale_Limit(int isbn_t, int sold_t,double sellingprice_t,double discount_t,int limit_t);
    void set(int isbn_t, int sold_t,double sellingprice_t,double discount_t,int limit_t);
};

Book_Sale_Limit::Book_Sale_Limit(){
    Book_Sale();
    limit=0;
}

Book_Sale_Limit::Book_Sale_Limit(int isbn_t, int sold_t,double sellingprice_t,double discount_t,int limit_t){
    Book_Sale( isbn_t, sold_t,sellingprice_t, discount_t);
    limit=limit_t;
    if(sold>limit) total=sellingprice*discount*limit+sellingprice*(sold-limit);
}

void Book_Sale_Limit::set(int isbn_t, int sold_t,double sellingprice_t,double discount_t,int limit_t){
    Book_Sale::set(isbn_t,sold_t,sellingprice_t,discount_t);
    limit=limit_t;
    if(sold>limit) total=sellingprice*discount*limit+sellingprice*(sold-limit);
}

Book_Sale::Book_Sale(){
    sold=0;
    sellingprice=0;
    discount=0;
    saleprice=0;
    total=0;
    isbn=new(nothrow) char[18];
    if(isbn==NULL){
        cout<<"isbn is no memory!";
        exit(0);
    }
}

Book_Sale::Book_Sale(int isbn_t, int sold_t,double sellingprice_t,double discount_t){
    sold=sold_t;
    sellingprice=sellingprice_t;
    discount=discount_t;
    saleprice=sellingprice*discount;
    total=saleprice*sold;

    isbn=new(nothrow) char[18];
    if(isbn==NULL){
        cout<<"isbn is no memory!";
        exit(0);
    }
    char isbn_str[6];
    sprintf(isbn_str, "%d", isbn_t);

    strcpy(isbn,"978-7-121-");
    strcpy(isbn+10,isbn_str);
    *(isbn+15)='-';
    *(isbn+16)=last_code(isbn);
    *(isbn+17)=0;
}

Book_Sale::~Book_Sale(){
    delete [] isbn;
    isbn=NULL;
}

Book_Sale::Book_Sale(const Book_Sale& b_t){
    sold=b_t.sold;
    sellingprice=b_t.sellingprice;
    discount=b_t.discount;
    saleprice=b_t.saleprice;
    total=b_t.total;
    isbn=new(nothrow) char[18];
    if(isbn==NULL){
        cout<<"isbn is no memory!";
        exit(0);
    }
    strcpy(isbn,b_t.isbn);
}

void Book_Sale::display(){
    cout<<"该书的ISBN号为:"<<isbn<<"，销量为:"<<sold<<"本，原价为:"<<sellingprice<<"元，折扣为:"<<discount<<"，现价为:"<<saleprice<<"元，总销售额为:"<<total<<"元\n";
}

ostream& operator<<(ostream& cout,Book_Sale& book){
    cout<<"该书的ISBN号为:"<<book.isbn<<"，销量为:"<<book.sold<<"本，原价为:"<<book.sellingprice<<"元，折扣为:"<<book.discount<<"，现价为:"<<book.saleprice<<"元，总销售额为:"<<book.total<<"元\n";
    return cout;
}

void Book_Sale::set(int isbn_t, int sold_t,double sellingprice_t,double discount_t){
    if(sold_t!=-1) sold=sold_t;
    if(sellingprice_t!=-1) sellingprice=sellingprice_t;
    if(discount_t!=-1) discount=discount_t;
    saleprice=sellingprice*discount;
    total=saleprice*sold;
    if(isbn_t!=-1){
        delete[] isbn;
        isbn=new(nothrow) char[18];
        if(isbn==NULL){
            cout<<"isbn is no memory!";
            exit(0);
        }

        char isbn_str[6];
        sprintf(isbn_str, "%d", isbn_t);

        strcpy(isbn,"978-7-121-");
        strcpy(isbn+10,isbn_str);
        *(isbn+15)='-';
        *(isbn+16)=last_code(isbn);
        *(isbn+17)=0;
    }
    
}
