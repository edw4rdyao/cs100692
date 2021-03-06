/****************************************************************************
本头文件为LZ77（GZIP中的LZ77压缩方式）头文件，创建了一个LZ77类
附：（LZ77简要步骤，详细步骤会在实验报告中写明）
1.创建一个窗口（查找缓冲区和先行缓冲区）（64K=32K+32K）
2.随着查找缓冲区的前进和窗口的前进 ，不断构建字典
3.构建字典的同时，将先行缓冲区头三个字符组成的字符串与先前的字符串进行匹配（通过字典）
  为提高匹配效率，采用哈希表的方式进行匹配
4.若匹配成功，则通过哈希表构建的匹配链匹配出最长的匹配串，将当前串用<距离，长度>进行
  替换后输出到压缩文件；若匹配不成功则原样输出到压缩文件
5.最后将压缩文件和标记文件（标记字符是被替换的‘对’还是原字符）合并组成最终的压缩文件
*****************************************************************************/

#include "hush.h"
#include <fstream>
#include <cstdio>

using namespace std;

class LZ77 {
public:
	LZ77();
	~LZ77();
	void CompressFile(string fileName, string newFileName);
	void UnCompressFile(string fileName,string newFileName);
	void MoveWindow(ifstream& inFile, size_t& lookAhead, USH& strStart);
	USC GetMaxMatchLength(USH matchHead, USH& curMatchDistance, USH strStart);
	void WriteFlag(ofstream& flagFile, USC& chFlag, USC& bitCount, bool hasEncode);
	void MergeFile(ofstream& fOut, USL fileSize);
private:
	USC* Window;		//滑动窗口，大小为64K，用于存放缓冲区的数据
	HushTable LZhush;	//窗口对应的哈希表，随着窗口的滑动不断更新
};
