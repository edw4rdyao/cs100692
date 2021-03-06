/***************************************************************
hush.h
本文件为哈希表（桶）hush的头文件
构建了一个哈希表类（LZ77所用）和一个哈希桶类（huffman所用）
哈希方式大大提高了查找的效率,为压缩文件节省了大量的时间
****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>

using namespace std;

typedef unsigned char USC;
typedef unsigned short USH;
typedef unsigned long long USL;

const USH HWS = USH(32 * 1024); 					//hushtable head and windows' size哈希表head数组的大小和窗口大小的一半 32*1024=32K
const USH MIN_MATCHLENGTH = 3;						//最短的匹配长度为3
const USH MAX_MATCHLENGTH = 258;					//最长的匹配长度255+3=258
const USH MIN_LOOKAHEAD = MAX_MATCHLENGTH + 1;		//先行缓冲区的最小长度，当小于此长度时，就使窗口滑动32K
const USH HASH_BITS = 15;

const USH HUSHSIZE = USH(32 * 1024);			//哈希表数组的大小
const USH HUSHMASK = USH(HUSHSIZE - 1);			//防止哈希表数组溢出

//哈希表
class HushTable {
public:
	HushTable(USH size);
	~HushTable();
	void UpdateHush();
	void HushFunction(USH& hashAddr, USC ch);
	void HushInsert(USH& matchHead, USC ch, USH pos, USH& hashAddr);
	USH GetNextAdress(USH matchHead);
	USH HUSH_SHIFT();

private:
	USH* Head;		//哈希表的head数组，用以存放某（三字符）字符串的匹配头，索引为（三字符）字符串对应的哈希地址（通过哈希函数获取）
	USH* Prev;		/*哈希表的prev数组，用以存放上一个字符串的位置，用于解决哈希冲突（即字符串对应的哈希地址将原匹配头覆盖可能会使后续的匹配中得不到最优匹配）
					将字符连成匹配链*/
};
