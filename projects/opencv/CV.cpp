// 大作业来了QAQ....
// 日志：
// 11/30 2:15 打开不喜欢用的VS2019 然后调好了字体颜色（调了一个小时qaq 
// 11/30 2:41 画了个主菜单qaq
// 11/20 14:53 写好了菜单，退出，返回系统qaq  准备把“简单”的加减乘除写好qaq
// 12/01 0:29 因为心急看错题QAQ...开始补救  返回刚刚写好菜单
// 12/01 1:24 居然出现了堆栈问题，咋整再说叭,写完了加法，其他应该简单点叭
// 12/01 1:36 写好了数乘
// 12/01 2:01 写好了转置 然后睡觉QAQ
// 12/01 10:07 突然发现一个优化矩阵读取的东西（符合我一维数组要求...)，我简直不能更高兴哈哈哈
// 12/01 10:26 写好了乘法和H巴拉巴拉乘积,只剩卷积了ee
// 12/01 11:04 决定把优化的代码加进去，因为那样真的更好
// 12/01 11:32 优化完成，准备写卷积
// 12/01 11:48 我感觉我完成了卷积之前的所有事情，开始写卷积QAQ
// 12/02 17:10 完成的卷积的核心代码 也解决了堆栈的问题哈哈
// 12/02 18:06 配置好了opencv，而且完善了代码注释，卷积也写好了，不过感觉可以在多写一点自定义的函数，要不然卷积的应用会比较麻烦QAQ
// 12/02 19:08  我发现了！demo函数简直恶心的一批
// 12/03 23:15 写完了卷积应用哈哈哈哈
// 12/05 1:30 学习了一波opencv QAQ，再想一想猫猫怎么写，然后再写报告叭QAQ
// 12/12 不想更新日志了QAQ


//包含头文件
#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include <cmath>

//命名空间预处理
using namespace cv;
using namespace std;
#define sizeL 256

//定义全局变量
int matrixA[sizeL * sizeL] = { 0 }, matrixB[sizeL * sizeL] = { 0 }, matrixC[sizeL * sizeL] = { 0 }, matrixAPad[(sizeL + 2) * (sizeL + 2)] = { 0 }, convD[sizeL * sizeL];

//声明函数
void tip();
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv_padding(int A[], int APad[], int row, int col);
void conv_ope(int APad[], int B[], int conv[], int row, int col);
int conv_sum(int array[], int row, int col);
void conv();
void wait_for_enter();
void menu();
void demo();
void otsu();
Mat extract_ope(Mat src);
void extract();

 //主函数
int main()
{
	// 定义相关变量
	char choice = 0, ch = 0;

	wait_for_enter();
	while (true)
	{
		system("cls"); //清屏
		menu(); //调用菜单显示函数
		choice = _getch();//选择
		if (choice == '0') //选择退出
		{
			cout << "\n\t\t\t\t你确定要退出吗? (按 \"Y\" 退出)" << endl;
			ch = _getch();
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}

		switch (choice)
		{
		case '1':matriplus(); break;//矩阵加法
		case '2':nummulti(); break;//矩阵数乘
		case '3':matritrans(); break;//矩阵转置
		case '4':matrimulti(); break;//矩阵乘法
		case '5':hadamulti(); break;//Hadamard乘积
		case '6':conv(); break;//矩阵卷积
		case '7':demo(); break;//卷积应用
		case '8':otsu(); break;//二值法
		case '9':extract(); break;//图像目标提取
		default:
			cout << "\n\t\t\t\t   输入错误，请重新输入QAQ..." << endl;
			wait_for_enter();
		}
	}
	return 0;
}

//清屏并等待输入
void wait_for_enter()
{
	cout << endl << "\t\t\t\t\t按回车继续...";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

//菜单函数
void menu() {
	cout << "\t\t************************欢迎来到矩阵操作器************************\n";
	cout << "\t\t******************************************************************\n";
	cout << "\t\t**                           --菜单--                           **\n";
	cout << "\t\t**    1.矩阵加法             2.矩阵数乘         3.矩阵转置      **\n";
	cout << "\t\t**    4.矩阵乘法             5.Hadamard乘积     6.矩阵卷积      **\n";
	cout << "\t\t**    7.卷积应用             8.OTSU算法二值化   9.图像目标提取  **\n";
	cout << "\t\t**    0.如果你想挂科你就按0                                     **\n";
	cout << "\t\t******************************************************************\n";
	cout << "\t\t**************************请选择功能<0~9>*************************\n";
}

//提示函数
void tip() {
	cout << "\n(注:输入矩阵时,请使用英文输入法,每行元素之间以逗号','隔开,以分号';'为分行的标志,末行结尾不需要分号。)\n例：2,3,1;4,3,2;3,6,8\n";
}

//矩阵加法函数
void matriplus() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵加法************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0;
	int i = 0, j = 0;
	char back, c;

	//更新全局变量的值
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}

	//输入两矩阵并判断运算条件，不满足则重新输入
	while (true) {
		for (i = 0; i < rowA * colA; i++) {
			matrixA[i] = 0;
		}
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowA = 0; colA = 0; rowB = 0; colB = 0; i = 0; j = 0;
		cout << "\n请输入矩阵A：" << endl;
		cin >> matrixA[i];
		while ((c = getchar()) != '\n') {
			cin >> matrixA[++i];
			if (c == ';') rowA++;
		}
		rowA++;
		i++;
		colA = i / rowA;
		cout << "\t矩阵A\n";
		for (i = 0; i < rowA * colA; i++) {
			cout << "\t" << matrixA[i];
			if ((i + 1) % colA == 0) cout << endl;
		}
		cout << "请输入矩阵B：" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowA == rowB && colA == colB) break;
		cout << "\t矩阵A与矩阵B不能相加QAQ\n\t请重新输入两个同型矩阵...\n";
	}
	cout << "\t矩阵B\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//计算并输出两矩阵之和
	cout << "\n\t矩阵A矩阵B之和为：\n";
	for (i = 0; i < rowA * colA; i++) {
		matrixA[i] = matrixA[i] + matrixB[i];
	}
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//输出返回菜单提示
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//矩阵数乘函数
void nummulti() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵数乘************\n";
	tip();
	int rowA = 0, colA = 0;
	int i = 0, n = 0;
	char back, c;

	//更新全局变量的值
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	i = 0;

	//输入矩阵
	cout << "\n请输入矩阵A：" << endl;
	cin >> matrixA[i];
	while ((c = getchar()) != '\n') {
		cin >> matrixA[++i];
		if (c == ';') rowA++;
	}
	rowA++;
	i++;
	colA = i / rowA;
	cout << "\t矩阵A\n";
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//输入整数
	cout << "请输入整数B：\n";
	cin >> n;

	//计算结果并输出
	cout << "\t矩阵A与整数B的乘积为：\n";
	for (i = 0; i < rowA * colA; i++) {
		matrixA[i] = matrixA[i] * n;
	}
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//输出返回菜单提示
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//转置函数
void matritrans() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵转置************\n";
	tip();
	int rowA = 0, colA = 0;
	int i = 0, n = 0, j = 0, k = 0;
	char back, c;

	//更新全局变量的值
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	i = 0;

	//输入矩阵
	cout << "\n请输入矩阵A：" << endl;
	cin >> matrixA[i];
	while ((c = getchar()) != '\n') {
		cin >> matrixA[++i];
		if (c == ';') rowA++;
	}
	rowA++;
	i++;
	colA = i / rowA;
	cout << "\t矩阵A\n";
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//输出转置后的结果
	cout << "\n\t矩阵A转置之后的矩阵为：\n";
	for (i = 0, n = 0; j < colA; j++, n++) {
		for (k = 0, i = n; k < rowA; i = i + colA, k++) {
			cout << "\t" << matrixA[i];
		}
		cout << endl;
	}

	//输出返回菜单提示
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//矩阵乘法函数
void matrimulti() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵乘法************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0;
	int i = 0, j = 0;
	char back;
	char c;

	//更新全局变量的值
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixC[i] = 0;
	}

	//输入两矩阵并判断运算条件，不满足则重新输入
	while (true) {
		for (i = 0; i < rowA * colA; i++) {
			matrixA[i] = 0;
		}
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowA = 0; colA = 0; rowB = 0; colB = 0; i = 0; j = 0;
		cout << "\n请输入矩阵A：" << endl;
		cin >> matrixA[i];
		while ((c = getchar()) != '\n') {
			cin >> matrixA[++i];
			if (c == ';') rowA++;
		}
		rowA++;
		i++;
		colA = i / rowA;
		cout << "\t矩阵A\n";
		for (i = 0; i < rowA * colA; i++) {
			cout << "\t" << matrixA[i];
			if ((i + 1) % colA == 0) cout << endl;
		}
		cout << "请输入矩阵B：" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (colA == rowB) break;
		cout << "\t矩阵A与矩阵B不能相乘QAQ\n\t请重新输入两个矩阵,保证矩阵A的列数等于B的行数...\n";
	}
	cout << "\t矩阵B\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//进行乘法运算并输出结果
	cout << "\n\t矩阵A矩阵B相乘为：\n";
	for (i = 0; i < rowA; i++) {
		for (j = 0; j < colB; j++) {
			for (int a = 0; a < colA; a++) {
				matrixC[colB * i + j] += matrixA[i * colA + a] * matrixB[a * colB + j];
			}
		}
	}
	for (i = 0; i < rowA * colB; i++) {
		cout << "\t" << matrixC[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//输出返回菜单提示
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//矩阵Hadamard乘积函数
void hadamulti() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵Hadamard乘积************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0;
	int i = 0, j = 0;
	char back;
	char c;

	//更新全局变量的值
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}

	//输入两矩阵并判断运算条件，不满足则重新输入
	while (true) {
		for (i = 0; i < rowA * colA; i++) {
			matrixA[i] = 0;
		}
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowA = 0; colA = 0; rowB = 0; colB = 0; i = 0; j = 0;
		cout << "\n请输入矩阵A：" << endl;
		cin >> matrixA[i];
		while ((c = getchar()) != '\n') {
			cin >> matrixA[++i];
			if (c == ';') rowA++;
		}
		rowA++;
		i++;
		colA = i / rowA;
		cout << "\t矩阵A\n";
		for (i = 0; i < rowA * colA; i++) {
			cout << "\t" << matrixA[i];
			if ((i + 1) % colA == 0) cout << endl;
		}
		cout << "请输入矩阵B：" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowA == rowB && colA == colB) break;
		cout << "\t矩阵A与矩阵B不能进行Hadamard相乘QAQ\n\t请重新输入两个同型矩阵...\n";
	}
	cout << "\t矩阵B\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//Hadamard乘积运算并输出结果
	cout << "\n\t矩阵A矩阵B的Hadamard乘积为：\n";
	for (i = 0; i < rowA * colA; i++) {
		matrixA[i] = matrixA[i] * matrixB[i];
	}
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//提示返回菜单
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//卷积填充函数
void conv_padding(int A[], int APad[], int row, int col) {
	int colAPad, rowAPad, i;
	colAPad = col + 2;
	rowAPad = row + 2;
	for (i = 0; i < row * col; i++) {
		APad[i + col + 3 + 2 * int(i / col)] = A[i];
	}
}

//卷积操作函数
void conv_ope(int APad[], int B[], int conv[], int row, int col) {
	int i, colAPad, con_i;
	colAPad = col + 2;
	for (i = 0; i < row * col; i++) {
		con_i = i + col + 3 + 2 * int(i / col);
		conv[i] = B[0] * APad[con_i - colAPad - 1] + B[1] * APad[con_i - colAPad] + B[2] * APad[con_i - colAPad + 1]
			+ B[3] * APad[con_i - 1] + B[4] * APad[con_i] + B[5] * APad[con_i + 1]
			+ B[6] * APad[con_i + colAPad - 1] + B[7] * APad[con_i + colAPad] + B[8] * APad[con_i + colAPad + 1];
	}
}

//卷积函数
void conv() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵卷积************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0, colAPad = 0, rowAPad = 0, con_i = 0;
	int const kernelSize = 3;
	int i = 0, j = 0;
	char c, back;

	//更新全局变量的值
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}
	for (i = 0; i < (sizeL + 2) * (sizeL + 2); i++) {
		matrixAPad[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		convD[i] = 0;
	}
	i = 0;

	//输入被卷积矩阵 
	cout << "\n请输入被卷积矩阵A：" << endl;
	cin >> matrixA[i];
	while ((c = getchar()) != '\n') {
		cin >> matrixA[++i];
		if (c == ';') rowA++;
	}
	rowA++;
	i++;
	colA = i / rowA;
	cout << "\t被卷积矩阵\n";

	//输出被卷积矩阵 
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//输入卷积核矩阵 
	while (true) {
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowB = 0; colB = 0; j = 0;
		cout << "请输入卷积核方阵B（3阶）：" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowB == 3 && colB == 3) break; //判断卷积核是否为三阶方阵 
		cout << "\t你输入的不是3阶方阵，请重新输入...\n";
	}

	//输出卷积核 
	cout << "\t卷积核\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//填充操作
	conv_padding(matrixA, matrixAPad, rowA, colA);
	rowAPad = rowA + 2;
	colAPad = colA + 2;

	//卷积操作
	conv_ope(matrixAPad, matrixB, convD, rowA, colA);

	//输出卷积后的矩阵
	cout << "\n\tAB卷积结果为：\n";
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << convD[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//提示返回菜单
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//卷积核元素之和
int conv_sum(int array[],int row,int col) {
	int sum=0,i=0;
	for (; i < row * col;i++) {
		sum = sum + array[i];
	}
	return sum;
}

//卷积的应用——图像处理
void demo() {

	//输出提示并定义相关变量
	cout << "\n\t\t\t\t************矩阵卷积的应用************\n";
	tip();
	cout << "\n你可以利用3阶的自定义卷积核对Lena图像进行操作\n";
	int rowA = 0, colA = 0, rowB = 0, colB = 0, colAPad = 0, rowAPad = 0, con_i = 0,i=0,j=0;
	char c,back;
	Mat image = imread("demolena.jpg",0);//图像的灰度值存放在格式为Mat的变量image中

	
	//更新全局变量
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}
	for (i = 0; i < (sizeL + 2) * (sizeL + 2); i++) {
		matrixAPad[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		convD[i] = 0;
	}

	

	//将Mat类型转化为一维数组
	int* array = new int[sizeL * sizeL];
	for (i = 0; i < sizeL * sizeL; i++) {
		array[i] = 0;
	}
	for (i = 0; i < image.rows * image.cols; i++) {
		array[i] = image.at<uchar>(i / image.cols, i % image.cols);
	}
	rowA = image.rows;
	colA= image.cols;
	
	//输入卷积核矩阵 
	while (true) {
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowB = 0; colB = 0; j = 0;
		cout << "\n请输入卷积核B（3阶）：" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowB == 3 && colB == 3) break; //判断卷积核是否为三阶方阵 
		cout << "\t你输入的不是3阶方阵，请重新输入...\n";
	}

	//输出卷积核 
	cout << "\t卷积核\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//填充操作
	conv_padding(array, matrixAPad, rowA, colA);
	rowAPad = rowA + 2;
	colAPad = colA + 2;

	//卷积操作
	conv_ope(matrixAPad, matrixB, convD, rowA, colA);

	//除以卷积核
	if (conv_sum(matrixB, rowB, colB) != 0) {
		for (i = 0; i < rowA * colA; i++) {
			convD[i] = convD[i] / conv_sum(matrixB, rowB, colB);
		}
	}

	//处理越界像素
	for (i = 0; i < image.rows * image.cols; i++) {
		if (convD[i] < 0) convD[i] = 0;
		if (convD[i] > 255) convD[i] = 255;
	}

	//数组转Mat类型
	Mat result = Mat(image.rows, image.cols, CV_8UC1, Scalar::all(0));
	for (i = 0; i < image.rows * image.cols; i++) {
		result.at<uchar>(i / image.cols, i % image.cols) = convD[i];
	}

	//显示原图
	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", image);

	//显示处理后图像
	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result);
	waitKey(0);
	delete[] array;

	//提示返回菜单
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//OTSU算法二值化
void otsu() {

	//输出提示
	char  begin,back;
	cout << "\n\t\t\t\t************OTSU算法二值化************\n";
	cout << "\n你将用OTSU算法对图像进行二值化\n按任意键显示结果...\n";
	begin = _getch();

	//读入图片
	Mat src = imread("demolena.jpg");

	//判断读入图片是否成功
	if (src.empty()) {
		printf("could not load image...\n");
	}

	//显示原图
	namedWindow("input");
	imshow("input", src);

	//二值法操作(未使用openCV的二值法阈值函数)
	int t = 127;
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Scalar m = mean(src);
	t = int(m[0]);
	binary = Mat::zeros(src.size(), CV_8UC1);
	int height = src.rows;
	int width = src.cols;// 直接读取图像像素
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int pv = gray.at<uchar>(row, col);
			if (pv > t) {
				binary.at<uchar>(row, col) = 255;
			}
			else {
			binary.at<uchar>(row, col) = 0;
			}
		}
	}


	//显示二值法操作后的图片
	imshow("result", binary);
	waitKey(0);


	//提示返回菜单
	cout << "\n\t按任意键返回菜单...";
	back = _getch();

}

//图像分割提取
void extract() {

	//输出提示
	char  begin, back;
	cout << "\n\t\t\t\t************openCV的简单应用************\n";
	cout << "\n你将用openCV对图像进行分割提取处理\n按任意键显示结果...\n";
	begin = _getch();

	//读入图片，建立新Mat变量
	Mat src1 = imread("brain.jpg");
	Mat src2 = imread("ship.jpg");
	Mat src3 = imread("snowball.jpg");
	Mat src4 = imread("polyhedrosis.jpg");
	Mat result1, result2, result3, result4;

	//显示原图
	namedWindow("input1", CV_WINDOW_AUTOSIZE);
	imshow("input1", src1);
	namedWindow("input2", CV_WINDOW_AUTOSIZE);
	imshow("input2", src2);
	namedWindow("input3", CV_WINDOW_AUTOSIZE);
	imshow("input3", src3);
	namedWindow("input4", CV_WINDOW_AUTOSIZE);
	imshow("input4", src4);
	
	//目标提取操作
	result1 = extract_ope(src1);
	result2 = extract_ope(src2);
	result3 = extract_ope(src3);
	result4 = extract_ope(src4);

	//显示结果
	namedWindow("result1", CV_WINDOW_AUTOSIZE);
	imshow("result1", result1);
	namedWindow("result2", CV_WINDOW_AUTOSIZE);
	imshow("result2", result2);
	namedWindow("result3", CV_WINDOW_AUTOSIZE);
	imshow("result3", result3);
	namedWindow("result4", CV_WINDOW_AUTOSIZE);
	imshow("result4", result4);

	waitKey(0);

	//提示返回菜单
	cout << "\n\t按任意键返回菜单...";
	back = _getch();
}

//图像分割提取操作函数
Mat extract_ope(Mat src) {

	/*定义相关变量*/
	Mat src_br;

	/*二值化*/
	cvtColor(src, src_br, COLOR_BGRA2GRAY);
	threshold(src_br, src_br, 0, 255, THRESH_OTSU | THRESH_BINARY);

	/*获取与过滤轮廓*/
	vector<vector<Point>>contours;
	findContours(src_br, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<vector<Point> >::const_iterator it = contours.begin();
	while (it != contours.end())
	{
		if (it->size() < 100)
			it = contours.erase(it);
		else
			++it;
	}
	Mat dst(src.size(), CV_8U, Scalar(0));
	drawContours(dst, contours, -1, Scalar(255), CV_FILLED);
	cvtColor(dst, dst, CV_GRAY2RGB);

	/*遍历保留与抹去*/
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < 3 * src.cols; j++) {
			if (dst.at<uchar>(i, j) == 0) {
				src.at<uchar>(i, j) = 0;
			}
		}
	}

	/*返回结果图像*/
	return src;
}
