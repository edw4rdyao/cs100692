#include "hush.h"

/**********************************************************
功能：	HashTable类的构造函数
返回值：	void
描述：	构造哈希表数组head和prev，申请含有2*HUSHSIZE个元素的空间
		将head和prev数组的内存连接起来，并且赋0
***********************************************************/
HushTable::HushTable(USH size) {

	Prev = new USH[(int)size * 2];
	if (Prev == NULL) {
		cout << "Prev is no memory!\n";
	}
	Head = Prev + size;

	//将head和prev数组元素赋0
	memset(Prev, 0, (int)size * 2 * sizeof(USH));

}

/**********************************************************
功能：	HashTable类的析构函数
返回值：	void
描述：	delete数组prev申请的含有2*HUSHSIZE个元素的空间
		将head和prev指针置空
***********************************************************/
HushTable::~HushTable() {
	delete[] Prev;
	Prev = nullptr;
	Head = nullptr;
}

/**********************************************************
功能：	更新哈希表
返回值：	void
描述：	当窗口向前移动32K时（即先前缓冲区大小不足MIN_LOOKAHEAD）
		需要将head数组中存放位置大于32K的元素减去32K，将存放的位
		置小于32K的元素置0
***********************************************************/
void HushTable::UpdateHush() {

	for (USH i = 0; i < HUSHSIZE; i++) {

		//更新head数组
		if (Head[i] >= HWS) {
			Head[i] -= HWS;
		}
		else {
			Head[i] = 0;
		}

		//更新prev数组
		if (Prev[i] >= HWS) {
			Prev[i] -= HWS;
		}
		else {
			Prev[i] = 0;
		}
	}
}

/**********************************************************
功能：	获得字符串的哈希函数
参数：	hashAdr 上一个串的哈希地址 ch 要计算哈希地址的字符串的
		第三个字符
返回值：	void
描述：	通过传入字符串（三字符）的第三个字符来获取本字符串的哈希
		地址，（计算字符串哈希地址需要三个字符，只传入一个字符的
		原因是前两个字符的哈希地址已经被保存在上一个字符串的哈希
		地址中，所以只需要第三个字符就可以将该串的哈希地址计算出
***********************************************************/
void HushTable::HushFunction(USH& hashAddr, USC ch) {
	hashAddr = (((hashAddr) << HUSH_SHIFT()) ^ (ch)) & HUSHMASK;
}

/**********************************************************
功能：	通过字符串的哈希地址将其位置插入到哈希表中
参数：	matchHead 匹配头 ch 要插入的字符串的第三个字符 pos 当前
		串的位置 hashAddr 上一个串的哈希地址
返回值：	void
描述：	每从先行缓冲区读取一个字符时，就计算其与其后两个字符组成
		的字符串的哈希地址（head数组的索引），获得对应head数组
		元素（若为0说明无匹配，即之前没有出现过该串），再将该元素
		赋给prev数组中索引为当前位置的元素，从而形成匹配链
***********************************************************/
void HushTable::HushInsert(USH& matchHead, USC ch, USH pos, USH& hashAddr) {
	//通过哈希函数计算出当前串的哈希地址
	HushFunction(hashAddr, ch);

	//传入匹配链头（用于查找匹配串），再将head[hashAddr]的值（离本串最近的匹配串的位置）赋给匹配链头
	matchHead = Head[hashAddr];

	//将head[hashAddr]的值（离本串最近的匹配串的位置）赋给prev数组中索引为当前位置的元素，从而形成匹配链
	Prev[pos & HUSHMASK] = Head[hashAddr];

	//将当前位置赋给匹配链的头
	Head[hashAddr] = pos;
}

/**********************************************************
功能：	遍历匹配链
参数：	当前匹配头
返回值：	链中下一个串的位置
描述：	传入匹配链的一个节点，通过prev的索引返回下一个匹配串的位
		置以再次进行匹配
***********************************************************/
USH HushTable::GetNextAdress(USH matchHead) {

	//通过prev的索引返回下一个匹配串的位置
	return Prev[matchHead & HUSHMASK];
}

USH HushTable::HUSH_SHIFT() {
	return (HASH_BITS + MIN_MATCHLENGTH - 1) / MIN_MATCHLENGTH;
}
