#include "LZ77.h"

/**********************************************************
功能：	LZ77类的构造函数
返回值：	void
描述：	构造一个LZ77类，申请一个窗口大小（64K）的空间和一个哈希
		表
***********************************************************/
LZ77::LZ77()
	:Window(new USC[2 * HWS]),
	LZhush(HWS) { }


/**********************************************************
功能：	LZ77类的析构函数
返回值：	void
描述：	delete申请的一个窗口大小（64K）的空间
***********************************************************/
LZ77::~LZ77() {
	delete[] Window;
	Window = NULL;
}


/**********************************************************
功能：	核心压缩函数，将文件通过LZ77算法压缩
参数：	fileName 文件名  压缩后的文件名
返回值：	void
描述：	通过滑动窗口中的先行缓冲区读取的字符（和其后两个字符构成
		的字符串）建立哈希表，同时建立匹配链，再用当前串通过哈希
		表的匹配链查找最长匹配，将<长度，距离>对替换该串（当找不
		到匹配就不做替换，继续读入下一字符）；再将每个位置对应的
		标记信息（是否被‘<长度，距离>对’替换了）写入到标记文件
***********************************************************/
void LZ77::CompressFile(string fileName, string newFileName) {

	//打开要压缩的数据文件
	ifstream fIn(fileName, ios::in | ios::binary);
	if (!fIn.is_open()) {
		cout << "open file error!";
		exit(0);
	}

	//打开压缩后的数据文件
	ofstream fOut(newFileName, ios::out | ios::binary);
	if (!fOut.is_open()) {
		cout << "open file error!";
		exit(0);
	}

	//打开临时的标记信息文件
	ofstream fFlag("flag.txt", ios::out | ios::binary);
	if (!fFlag.is_open()) {
		cout << "open file error!";
		exit(0);
	}

	//获取文件大小
	fIn.seekg(0, ios::end);
	USL fileSize = fIn.tellg();
	fIn.clear();
	fIn.seekg(0, ios::beg);

	//先从文件中读取64K（32K+32K）个字节，并且获得当前读取的字节数作为先前缓冲区
	fIn.read((char*)Window, HWS * 2);
	size_t lookAhead = size_t(fIn.gcount());

	//首先利用前两个字符设置最初的哈希地址
	USH hashAdress = 0;
	LZhush.HushFunction(hashAdress, Window[0]);
	LZhush.HushFunction(hashAdress, Window[1]);

	//与查找匹配相关的变量
	USH strStart = 0;			//当前匹配查找的位置（即先前缓冲区的第一个字符在窗口中的相对位置）
	USH matchHead = 0;			//当前字符串匹配查找的头位置，若为0则没有找到匹配串（即离当前串距离最近的匹配串的位置）
	USC curMatchLength = 0;		//当前串的匹配长度
	USH curMatchDistance = 0;	//当前匹配的距离（当前串与匹配串之间的距离）

	//与写入标记信息相关的变量
	USC chFlag = 0;		//8bit标记信息
	USC bitCount = 0;	//标记信息bit位


	//开始查找匹配
	while (lookAhead) {

		//插入三字符字符串中的最后一个字符以计算哈希地址，获取匹配头，完善匹配链
		LZhush.HushInsert(matchHead, Window[strStart + 2], strStart, hashAdress);

		//更新与当前匹配相关的变量
		curMatchLength = 0;		//当前的匹配长度
		curMatchDistance = 0;	//当前匹配的距离（当前串与匹配串之间的距离）

		//当获取的匹配头不为0，则通过GetLonggestMatchLength函数得到匹配链中的最长匹配长度
		if (matchHead) {
			curMatchLength = GetMaxMatchLength(matchHead, curMatchDistance, strStart);
		}

		//验证是否真的在匹配链中找到了不小于MIN_MACHLENGTH（最短的匹配长度）的匹配串
		if (curMatchLength >= MIN_MATCHLENGTH) {

			//说明找到了有效匹配串，将<长度，距离>对写入压缩数据文件中
			USC length = curMatchLength - 3;				//<长度>
			USH distance = curMatchDistance;				//<距离>
			fOut.put(length);								//写入长度
			fOut.write((char*)&distance, sizeof(distance));	//写入距离

			//写入标记文件
			WriteFlag(fFlag, chFlag, bitCount, true);


			//替换后将被替换的串中所有三字符字符串插入到哈希表中
			for (USC i = 0; i < curMatchLength - 1; i++) {
				strStart++;		//后移一个字符
				LZhush.HushInsert(matchHead, Window[strStart + 2], strStart, hashAdress);	//插入三字符字符串
			}
			strStart++;			//循环过程中少移了一次

			//更新先行缓冲区中剩余字符的个数
			lookAhead = lookAhead - curMatchLength;
		}
		else {

			//说明没有找到有效匹配串，将字符原样输出到压缩数据文件中
			fOut.put(Window[strStart]);	//写入字符
			strStart++;					//后移一个字符
			lookAhead--;				//先前缓冲区减1

			//写入标记文件
			WriteFlag(fFlag, chFlag, bitCount, false);

		}

		//当先行缓冲区的长度小于最小长度时，窗口滑动
		if (lookAhead <= MIN_LOOKAHEAD) {
			MoveWindow(fIn, lookAhead, strStart);
		}
	}

	//当最后的标记位数不够8bit
	if (bitCount > 0 && bitCount < 8) {

		//直接写入标记文件
		chFlag <<= (8 - bitCount);
		fFlag.put(chFlag);
	}

	//关闭标记文件
	fFlag.close();

	//合并压缩数据文件与标记文件形成最终压缩文件
	MergeFile(fOut, fileSize);

	//关闭各文件
	fIn.close();
	fOut.close();

	// 将用来保存标记信息的临时文件删除掉
	remove("flag.txt");

}


/**********************************************************
功能：	解压函数，将文件解压
参数：	fileName 文件名  newFileName 解压后的文件名
返回值：	void
描述：从标记文件中读取标记,如果当前标记是0，表示源字符，从压缩数
	 据文件中读取一个字节，直接写到解压缩之后的文件中;如果当前标
	 记是1，表示遇到<长度,距离>，从压缩数据文件中先读取一个字节
	 作为压缩的长度，再继续读取两个字节作为距离，然后从解压缩过
	 的结果中找出匹配长度
***********************************************************/
void  LZ77::UnCompressFile(const string fileName,const string newFileName)
{
	// 操作压缩文件 "原始数据" 的指针
	FILE* fIN = fopen(fileName.c_str(), "rb");
	if (nullptr == fIN){
		cout << "压缩文件打开失败" << std::endl;
		return;
	}

	// 操作压缩文件 "标记数据" 的指针
	FILE* fInFlag = fopen(fileName.c_str(), "rb");
	if (nullptr == fInFlag){
		cout << "压缩文件打开失败" << std::endl;
		return;
	}

	// 获取原始文件的大小
	USL fileSize = 0;
	fseek(fInFlag, 0 - int(sizeof(fileSize)), SEEK_END);
	fread(&fileSize, sizeof(fileSize), 1, fInFlag);

	// 获取标记信息的大小
	USL flagSize = 0;
	fseek(fInFlag, 0 - int(sizeof(fileSize)) - int(sizeof(size_t)), SEEK_END);
	fread(&flagSize, sizeof(fileSize), 1, fInFlag);

	// 将标记信息文件的文件指针移动到保存标记数据的起始位置
	fseek(fInFlag, 0 - int(sizeof(fileSize)) - int(sizeof(size_t)) - long(flagSize), SEEK_END);


	//打开解压文件
	FILE* fOUT = fopen(newFileName.c_str(), "wb");
	
	//用于从已经解压好的数据中向前读取重复的字节
	FILE* fOutIn = fopen(newFileName.c_str(), "rb");

	USC bitCount = 0;
	USC chFlag = 0;
	USL encodeCount = 0;	//已经解码的长度


	while (encodeCount < fileSize){

		//处理完完8bit时，再读取8bit
		if (0 == bitCount)
		{
			chFlag = fgetc(fInFlag);
			bitCount = 8;
		}

		if (chFlag & 0x80)
		{
			// 距离长度对
			USH matchLength = fgetc(fIN) + 3;
			USH matchDistance = 0;
			fread(&matchDistance, sizeof(matchDistance), 1, fIN);

			// 清空缓冲区：系统会将缓冲区中的数据写入到文件中
			fflush(fOUT);

			// 更新已经解码字节数大小
			encodeCount += matchLength;

			//移动文件指针至匹配字符处
			fseek(fOutIn, 0 - matchDistance, SEEK_END);

			//写入匹配的字符
			for (size_t i = 0; i < matchLength; i++) {
				fputc((fflush(fOUT), fgetc(fOutIn)), fOUT);
			}
		}
		else
		{
			//写入原字符
			int ch = fgetc(fIN);
			fputc(ch, fOUT);
			encodeCount++;
		}

		//再读取一个bit位
		chFlag <<= 1;
		bitCount--;
	}

	//关闭相关文件
	fclose(fIN);
	fclose(fInFlag);
	fclose(fOUT);
	fclose(fOutIn);
}


/**********************************************************
功能：	获得最长的匹配串
参数：	matchHead 匹配头 strStart 当前字符串的位置 curcurMat-
		chDistance 当前串与匹配串的距离
返回值：	最长的匹配长度
描述：	通过匹配链不断查找得到最长匹配长度的匹配串，但是要通过限
		制匹配次数（次数可自定义，这影响了压缩的程度和时间）以防
		止陷入死循环
***********************************************************/
USC LZ77::GetMaxMatchLength(USH matchHead, USH& curMatchDistance, USH strStart) {

	//相关的变量
	USC nowMatchLength = 0;	//每次匹配的长度
	USH curMatchStart = 0;  // 当前匹配在查找缓冲区中的起始位置
	USC maxMatchTimes = 255;	//最大的匹配次数
	USC maxMatchLenght = 0;	//最长的匹配长度

	do {
		//更新 从当前串开始的匹配范围（先行缓冲区中）
		USC* pStart = Window + strStart;	//开始
		USC* pEnd = pStart + MAX_MATCHLENGTH;//结束

		//更新 查找缓冲区的起始
		USC* pMatchStart = Window + matchHead;

		//更新 每次匹配的长度
		nowMatchLength = 0;

		//逐字符进行匹配
		while (pStart < pEnd && *pStart == *pMatchStart) {

			//使两串再后移一位进行匹配，再使匹配长度加1
			pStart++;
			pMatchStart++;
			nowMatchLength++;
		}

		//一次匹配结束了，判断并记录最长匹配
		if (nowMatchLength > maxMatchLenght) {
			maxMatchLenght = nowMatchLength;			//更新 长度
			curMatchStart = matchHead;					//更新 距离
		}

		//当匹配头为空（即为0）时或者达到了最大的匹配次数时，停止匹配
	} while ((matchHead = LZhush.GetNextAdress(matchHead)) > 0 && maxMatchTimes--);

	//获得最终最长匹配对应的距离
	curMatchDistance = strStart - curMatchStart;

	//返回最长匹配长度
	return maxMatchLenght;
}


/**********************************************************
功能：	滑动窗口
参数：	fIn 要压缩文件 lookAhead 先前缓冲区剩余字节数 strStrat
		当前串所在位置（即先前缓冲区的第一个字符位置）
返回值：	void
描述：	将滑动窗口向后移动32K
***********************************************************/
void LZ77::MoveWindow(ifstream& fIn, size_t& lookAhead, USH& strStart) {

	//先判断是否到达了文件末端
	if (strStart >= HWS) {

		//将右窗中的数据移至左窗
		memcpy(Window, Window + HWS, HWS);

		//将右窗置0
		memset(Window + HWS, 0, HWS);
		strStart -= HWS;

		//更新哈希表
		LZhush.UpdateHush();

		//向右窗（先前缓冲区）补充数据
		if (!fIn.eof()) {
			fIn.read((char*)Window + HWS, HWS);
			lookAhead = lookAhead + size_t(fIn.gcount());
		}
	}
}


/**********************************************************
功能：	写入标记信息
参数：	fFlag 标记文件 chFlag 8bit标记信息 bitcount bit位数
		hasEncode 判断是否已被替换
返回值：	void
描述：	通过判断字符是否被<长度，距离>对替换，来向标记文件写入标
		记信息，用0（一个bit）表示未被替换，用1（一个bit）表示已
		被替换当满8bit时，将chFlag写入标记文件中
***********************************************************/
void LZ77::WriteFlag(ofstream& fFlag, USC& chFlag, USC& bitCount, bool hasEncode) {

	//左移一位
	chFlag <<= 1;

	//若被替换，则记录1
	if (hasEncode) {
		chFlag |= 1;
	}
	bitCount++;

	//当标记满8bit时，将chFlag写入标记文件
	if (bitCount == 8) {
		fFlag.put(chFlag);

		//更新chFlag
		chFlag = 0;

		//更新bit位数
		bitCount = 0;
	}
}


/**********************************************************
功能：	合并标记信息与压缩文件信息
参数：	fOut 压缩数据文件 fileSize
返回值：	void
描述：	将标记信息与压缩文件信息合并成最后的压缩文件
***********************************************************/
void LZ77::MergeFile(ofstream& fOut, USL fileSize) {

	//打开标记文件
	ifstream fFlag("flag.txt", ios::in | ios::binary);
	if (!fFlag.is_open()) {
		cout << "open file error!";
		exit(0);
	}

	size_t flagSize = 0;				//标记文件的大小
	char* pReadBuff = new char[1024];	//读取缓冲区，每次读1024个字节
	if (pReadBuff == NULL) {
		cout << "pReadBuff is no memory!\n";
		return;
	}

	//读取标记文件内容
	while (true) {

		//读取缓冲区
		fFlag.read(pReadBuff, 1024);
		size_t readSize = size_t(fFlag.gcount());

		//若读取完毕，则退出循环
		if (readSize == 0) break;

		//将缓冲区的标记信息写入压缩文件
		fOut.write(pReadBuff, readSize);

		//记录标记文件大小
		flagSize = flagSize + readSize;
	}

	//写入标记文件大小
	fOut.write((char*)&flagSize, sizeof(flagSize));

	// 写原始文件大小
	fOut.write((char*)&fileSize, sizeof(fileSize));

	//关闭文件并delete缓冲区
	fFlag.close();
	delete[] pReadBuff;
}