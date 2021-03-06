/****************************************
GameEngine.cpp
Author: Root
Date: 2019/12/09
Description:
定义了程序游戏模块，用GameEngine命名空间防止同名污染，是你主要需要修改的文件
*****************************************/
#include "GameEngine.h"

namespace GameEngine {

	// 引入两个命名空间
	using namespace Graphic;
	using namespace Controller;

	//预置变量
	size_t mapWidth = 0, mapHeight = 0;				 // 地图宽度和高度
	UCHAR* mapCanvas = nullptr;						 // 地图数组指针，若做基础项请不要直接尝试操作这个指针
	COORD pos = { 0 }, posOld = { 0 };				 // 鼠标的位置
	COORD posChoice = { 0 }, posChoiceOld = { 0 };	 // 选中地图坐标的位置
	char key = '\0';								 // 键盘的按键
	bool gameFlag = false;							 // 游戏运行状态
	size_t frame = 0;								 // 已渲染帧数
	clock_t tic = clock();							 // 游戏开始时刻
	int operation = 0;								 // 执行的操作
	bool isFirst = true;							 // 是否为第一步
	UCHAR **mapArray=nullptr;						 // 地图数组
	// 新加变量
	UCHAR **mapArrayPadding=nullptr;				 //为处理边界而拓展的地图数组
	short flagNum = 0;                               //已标记数
	UCHAR stepNum = 0;                               //已走步数
	bool isWin=true;                                 //游戏输赢
	bool isLose = false;                             //游戏输赢
	clock_t timeStart;                               //开始计时
	clock_t timeEnd;                                 //停止计时
	short mineNum = 0;								 //地雷个数

	/****************************************
	Function:  renderMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	绘制当前地图
	*****************************************/
	void renderMap() {

		// 从行开始遍历
		for (size_t i = 0; i < mapHeight + 1; i++) {
			// 移动坐标至行首 并绘制行首的字符
			MovePos(0, (SHORT)i * 2 + 3);
			if (i == 0) {
				PutString("╔");
			}
			else if (i == mapHeight) {
				PutString("╚");
			}
			else {
				PutString("╠");
			}

			// 遍历列，绘制边界
			for (size_t j = 0; j < mapWidth; j++) {
				// 移动至确切的坐标，绘制方格的边界
				MovePos(2 + (SHORT)j * 8, (SHORT)i * 2 + 3);
				if (i == 0) {
					if (j < mapWidth - 1) {
						PutString("═══╦");
					}
					else {
						PutString("═══╗");
					}
				}
				else if (i == mapHeight) {
					if (j < mapWidth - 1) {
						PutString("═══╩");
					}
					else {
						PutString("═══╝");
					}
				}
				else {
					if (j < mapWidth - 1) {
						PutString("═══╬");
					}
					else {
						PutString("═══╣");
					}
				}
			}

			// 绘制地图
			if (i > 0 && i < mapHeight + 1) {
				// 移动至行首，绘制边界字符
				MovePos(0, (SHORT)i * 2 + 2);
				PutString("║");
				// 遍历列 绘制地雷
				for (size_t j = 0; j < mapWidth; j++) {
					MovePos(2 + (SHORT)j * 5, (SHORT)i * 2 + 2);    // 移动至确切坐标
					const size_t mapIndex = (i - 1) * mapWidth + j; // 确定地图数组的下标
					char numMap[8] = "   ";							// 确定数字字符串
					numMap[1] = '0' + mapCanvas[mapIndex];			// 当mapCanvas[mapIndex]为1到8时，将其转换成字符串
					switch (mapCanvas[mapIndex]) {
					case 0:
						// 0的时候放置空白
						PutString("   ");
						break;
					case 1:
						// 从1开始绘制数字
						PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
						break;
					case 2:
						PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
						break;
					case 3:
						PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
						break;
					case 4:
						PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
						break;
					case 5:
						PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
						break;
					case 6:
						PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
						break;
					case 7:
						PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
						break;
					case 8:
						PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
						break;
					case 9:
						// 9为地雷
						PutStringWithColor(" ※", 255, 215, 0, 0, 0, 0);
						break;
						//大于20为标记
					case 20:
					case 21:
					case 22:
					case 23:
					case 24:
					case 25:
					case 26:
					case 27:
					case 28:
					case 29:
						PutStringWithColor(" ★", 178, 34, 34, 0, 0, 0);
						//其余为未翻开
					default:
						PutString(" ▇");
					}

					MovePos(5 + (SHORT)j * 5, (SHORT)i * 2 + 2);
					PutString("║");
				}
			}
		}

		// 将地图更新到屏幕
		Update();
	}

	/****************************************
	Function:  updateMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	将二维数组的数据复制到一维数组中
	*****************************************/
	void updateMap() {
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapCanvas[j + i * mapWidth] = mapArray[i][j];
			}
		}
	}

	/****************************************
	Function:  patternCust()
	Parameter: None(void)
	Return:    None(void)
	Description:
	得到用户自定义地图的大小与雷的个数
	*****************************************/
	void patternCust() {
		//相关变量
		char ch='0';
		size_t n=0;
		size_t i = 0;

		//绘制说明
		ClearScreen();							//清屏
		MovePos(55, 2);
		PutStringWithColor("自定义模式", 30, 144, 255, 0, 0, 0);
		MovePos(30, 4);
		PutString("你可以依次自己输入地图大小和雷的个数，但是要在一定范围内，地图宽在");
		MovePos(30, 6);
		PutString("8-30之间，地图高在8-16之间，地雷的个数根据地图的大小适中选择。");
		MovePos(30, 8);
		PutStringWithColor("注意:请保证输入的正确性，并且不能删除，输入后按‘回车’确认", 178, 34, 34, 0, 0, 0);
		Update();


		//获得地图宽度
		MovePos(46, 10);
		PutString("请输入地图宽度（8-30）：");
		Update();
		MovePos(46, 11);
		while (ch != 13) {
			n = n * 10 + ch - '0';
			while (true) {
				ch = _getch(); if (ch >= '0' && ch <= '9' || ch == 13) break;
			}
			PutChar(ch);
			Update();
			i++;
			MovePos(46+i, 11);
		}
		mapWidth = n;
		ch = '0'; n = 0; i = 0;

		//获得地图高度
		MovePos(46, 12);
		PutString("请输入地图高度（8-16）：");
		Update();
		MovePos(46, 13);
		while (ch != 13) {
			n = n * 10 + ch - '0';
			while (true) {
				ch = _getch(); if (ch >= '0' && ch <= '9' || ch == 13) break;
			}
			PutChar(ch);
			Update();
			i++;
			MovePos(46 + i, 13);
		}
		mapHeight = n;
		ch = '0'; n = 0; i = 0;

		//获得地雷个数
		MovePos(46, 14);
		PutString("请输入地雷个数（不超过地图大小）：");
		Update();
		MovePos(46, 15);
		while (ch != 13) {
			n = n * 10 + ch - '0';
			while (true) {
				ch = _getch(); if (ch >= '0' && ch <= '9' || ch == 13) break;
			}
			PutChar(ch);
			Update();
			i++;
			MovePos(46 + i, 15);
		}
		mineNum = n;
		
	}


	/****************************************
	Function:  patternChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	显示模式选择，根据选择的困难程度确定地图的大小与雷的个数
	*****************************************/
	void patternChoice() {

		//绘制说明
		ClearScreen();//清屏
		MovePos(62, 2);
		PutStringWithColor("困难程度", 30, 144, 255, 0, 0, 0);
		MovePos(38, 4);
		PutString("|简单模式|    地图大小：10x10 雷：10       (按‘1’)");
		MovePos(38, 6);
		PutString("|一般模式|    地图大小：16x16 雷：30       (按‘2’)");
		MovePos(38, 8);
		PutString("|困难模式|    地图大小：16x30 雷：99       (按‘3’)");
		MovePos(38, 10);
		PutString("|自定义模式|  地图宽：8-30 地图高：8-16    (按‘4’)");
		Update();

		//检查输入
		char choice;
		while (true) {
			choice = _getch();
			if (choice == '1' || choice == '2' || choice == '3'||choice=='4') break;
		}

		//根据输入确定困难程度
		switch (choice) {
		case '1': 
			//简单模式
			mapWidth = 10;
			mapHeight = 10;
			mineNum = 10;
			break;
		case '2':
			//一般模式
			mapWidth = 16;
			mapHeight = 16;
			mineNum = 30;
			break;
		case '3':
			//困难模式
			mapWidth = 30;
			mapHeight = 16;
			mineNum = 99;
			break;
		case '4':
			//自定义难度
			patternCust();
		}
		ClearScreen();//清屏
	}

	/****************************************
	Function:  InitGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	初始化游戏
	*****************************************/
	void InitGame() {

		// 清屏
		ClearScreen();	

		// 确定困难程度
		patternChoice();

		// 分配地图数组空间
		mapArray = new UCHAR * [mapHeight];
		mapArray[0] = new UCHAR[mapWidth * mapHeight];
		for (size_t i = 1; i < mapHeight; i++) mapArray[i] = mapArray[i - 1] + mapWidth;
		mapArrayPadding = new UCHAR * [mapHeight+2];
		mapArrayPadding[0] = new UCHAR[(mapWidth+2) * (mapHeight+2)];
		for (size_t i = 1; i < mapHeight+2; i++) mapArrayPadding[i] = mapArrayPadding[i - 1] + mapWidth+2;
		mapCanvas = new UCHAR[mapWidth * mapHeight];

		// 初始化地图数组
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArray[i][j] = 10;
			}
		}

		// 更新并绘制地图
		updateMap();	
		renderMap();	
	}

	/****************************************
	Function:  renderChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	绘制选中的地块的背景
	*****************************************/
	void renderChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);        // 定义背景白色当前的颜色值，通过已渲染的帧数进行运算（此处也可以改成使用时间）
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x; // 确定地图下标

		MovePos(2 + x * 4, y * 2 + 3);

		// 以下内容同renderMap中绘制数组元素对应图案部分相同
		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, alpha, alpha, alpha);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, alpha, alpha, alpha);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, alpha, alpha, alpha);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, alpha, alpha, alpha);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, alpha, alpha, alpha);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, alpha, alpha, alpha);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, alpha, alpha, alpha);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, alpha, alpha, alpha);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, alpha, alpha, alpha);
			break;
		case 9:
			PutStringWithColor("※", 255, 215, 0, alpha, alpha, alpha);
			break;
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
			PutStringWithColor("★", 178, 34, 34, alpha, alpha, alpha);
			break;
		default:
			PutStringWithColor("▇", 255, 255, 255, alpha, alpha, alpha);
		}
	}

	/****************************************
	Function:  clearChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	清除choice中指示位置的背景，功能同上
	*****************************************/
	void clearChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x;

		MovePos(2 + x * 4, y * 2 + 3);

		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, 0, 0, 0);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
			break;
		case 9:
			PutStringWithColor("※", 255, 215, 0, 0, 0, 0);
			break;
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
			PutStringWithColor("★", 178, 34, 34, 0, 0, 0);
			break;
		default:
			PutStringWithColor("▇", 255, 255, 255, 0, 0, 0);
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	检查输入和操作，并设置相关变量
	*****************************************/
	void checkChoice() {
		FlushInput();							// 刷新输入缓冲区
		pos = GetCursorPos();					// 获取鼠标坐标
		COORD hitLeftPos = GetCursorHitPos();	// 获取左键单击坐标
		COORD hitRightPos = GetCursorHitPos(2);	// 获取右键单击坐标
		key = GetKeyHit();						// 获取键盘输入
		operation = 0;							// 当前操作 (0无操作，1为挖开地块，2为标值旗帜，或者自己指定)

		// 检查键盘输入
		switch (key) {
		case VK_ESCAPE:
			// ESC键，将游戏运行状态置否以退出游戏
			gameFlag = false;
			break;

		// 上下左右键移动选中的坐标
		case VK_UP:
			if (posChoice.Y > 0)posChoice.Y--;
			break;
		case VK_RIGHT:
			if (posChoice.X < (SHORT)mapWidth - 1)posChoice.X++;
			break;
		case VK_DOWN:
			if (posChoice.Y < (SHORT)mapHeight - 1)posChoice.Y++;
			break;
		case VK_LEFT:
			if (posChoice.X > 0)posChoice.X--;
			break;

		// 回车和空格分别对应操作1和2
		case VK_RETURN:
			operation = 1;
			break;
		case VK_SPACE:
			operation = 2;
			break;
		}

		// 将鼠标控制台的坐标放缩至地图坐标
		const size_t mouseY = (size_t)(pos.Y + 1) / 2 - 2;
		const size_t mouseX = (size_t)(pos.X - 1) / 4;
		if (mouseY < mapHeight && mouseX < mapWidth) {
			// 若没有超边界，更新选择的坐标
			posChoice.X = (SHORT)mouseX;
			posChoice.Y = (SHORT)mouseY;
		}

		// 左键和右键分别对应操作1和2
		if (hitLeftPos.X == pos.X && hitLeftPos.Y == pos.Y) {
			operation = 1;
		}
		else if (hitRightPos.X == pos.X && hitRightPos.Y == pos.Y) {
			operation = 2;
		}
	}

	/****************************************
	Fuction: loadingMap()
	Parameter:
	Return:	  
	Description:
	翻开地块并且利用递归做延伸拓展
	*****************************************/
	void loadingMap(size_t x,size_t y) {

		//首先翻开空白
		mapArray[x][y] = mapArray[x][y] - 10;

		//遍历赋值
		for (size_t i = 0; i < mapHeight+2; i++) {
			for (size_t j = 0; j < mapWidth+2; j++) {
				mapArrayPadding[i][j] = 100;
			}
		}
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArrayPadding[i + 1][j + 1] = mapArray[i][j];
			}
		}

		//拓展空白
		for (size_t i = x; i <= x + 2; i++) {
			for (size_t j = y; j <= y + 2; j++) {
				if (mapArrayPadding[i][j] >= 11 && mapArrayPadding[i][j] <= 18) {
					mapArrayPadding[i][j] = mapArrayPadding[i][j] - 10;
					for (size_t i = 0; i < mapHeight; i++) {
						for (size_t j = 0; j < mapWidth; j++) {
							mapArray[i][j] = mapArrayPadding[i + 1][j + 1];
						}
					}
				}
				else if (mapArrayPadding[i][j] == 10) {
					loadingMap(i - 1, j - 1);
				}
			}
		}

	}

	/****************************************
	Function:  renderFailTip
	Parameter: None(void)
	Return:    None(void)
	Description:
	显示失败提示
	*****************************************/
	void renderLoseTip() {
		
		//显示雷
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (mapArray[i][j] == 19|| mapArray[i][j] == 29) mapArray[i][j] = 9;
			}
		}

		// 更新并绘制地图
		updateMap();	
		renderMap();

		//显示失败提示
		MovePos(2,2*mapHeight+3);
		PutStringWithColor("!!!BOOM YOU LOST!!!", 178, 34, 34, 0, 0, 0);
		MovePos(2, 2 * mapHeight + 4);
		PutString("|你输了，点击屏幕或按下回车以继续|");
		Update();
	}

	/****************************************
	Function:  renderWinTip
	Parameter: None(void)
	Return:    None(void)
	Description:
	显示成功提示
	*****************************************/
	void renderWinTip() {

		//显示步数和所用时间
		MovePos(12, 1);
		char strStep[32] = "";
		sprintf_s(strStep, "Step:%u   ", stepNum);
		PutString(strStep);
		char strTime[32] = "";
		sprintf_s(strTime, "Time:%ds  ", (int)(timeEnd - timeStart) / CLOCKS_PER_SEC);
		PutStringWithColor(strTime, 30, 144, 255, 0, 0, 0);
		
		//显示成功提示
		MovePos(2, 2 * mapHeight + 3);
		PutStringWithColor("!!!! YOU  WIN !!!!", 30, 144, 255, 0, 0, 0);
		MovePos(2, 2 * mapHeight + 4);
		PutString("|你赢了，点击屏幕或按下回车继续|");
		Update();
	}

	/****************************************
	Function:  initMap(COORD pos)
	Parameter: COORD pos
	Return:    None(void)
	Description:
	埋雷操作，初始化地图
	*****************************************/
	void initMap(COORD pos) {

		// 随机埋雷
		srand((unsigned)time(NULL));
		int mineX, mineY;
		for (size_t i = 0; i < mineNum;) {
			mineX = rand() % mapHeight;
			mineY = rand() % mapWidth;
			if (mineX != pos.Y && mineY != pos.X && mapArray[mineX][mineY] != 19) {
				mapArray[mineX][mineY] = 19;
				i++;
			}
		}

		//遍历赋值
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArrayPadding[i + 1][j + 1] = mapArray[i][j];
			}
		}

		// 确定数字
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (mapArray[i][j] >= 19) {
					mapArrayPadding[i ][j ]++;
					mapArrayPadding[i ][j+1]++;
					mapArrayPadding[i ][j + 2]++;
					mapArrayPadding[i+1][j ]++;
					mapArrayPadding[i+1][j + 2]++;
					mapArrayPadding[i + 2][j  ]++;
					mapArrayPadding[i + 2][j+1]++;
					mapArrayPadding[i + 2][j + 2]++;
				}
			}
		}

		// 更新雷的值
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArray[i][j] = mapArrayPadding[i + 1][j + 1];
				if (mapArray[i][j] > 19) mapArray[i][j] = 19;
			}
		}

		// 更新并绘制地图
		updateMap();	
		renderMap();	
	}

	/****************************************
	Function:  digBlock()
	Parameter: COORD(pos)
	Return:    None(void)
	Description:
	翻开地块，并判断是否为雷
	*****************************************/
	void digBlock(COORD pos) {

		if (isFirst) {
			// 如果是第一步走，则先初始化地图
			initMap(pos);
			isFirst = false; // 将第一步设置为否
		}

		// 获取翻开的地块坐标
		size_t x = pos.Y;
		size_t y = pos.X;

		// 如果翻开的是雷，则失败
		if (mapArray[x][y] == 19) {
			isLose = true;
		}

		// 如果是数字，直接翻开
		else if (mapArray[x][y] >= 11 && mapArray[x][y] <= 18) {
			mapArray[x][y] = mapArray[x][y] - 10;
			stepNum++;
			// 更新并绘制地图
			updateMap();
			renderMap();
		}

		// 如果是空白，则扩散
		else if (mapArray[x][y] == 10) {
			loadingMap(x, y);
			stepNum++;
			// 更新并绘制地图
			updateMap();
			renderMap();
		}
	}

	/****************************************
	Function:  flagBlock(COORD pos)
	Parameter: COORD pos
	Return:    None(void)
	Description:
	标记或清除标记
	*****************************************/
	void flagBlock(COORD pos) {

		// 标记
		if (mapArray[pos.Y][pos.X] >= 10 && mapArray[pos.Y][pos.X] <= 19) {
			mapArray[pos.Y][pos.X] = mapArray[pos.Y][pos.X] + 10;
			flagNum++;
		}

		// 清除标记
		else if(mapArray[pos.Y][pos.X] >= 20 && mapArray[pos.Y][pos.X] <= 29) {
			mapArray[pos.Y][pos.X] = mapArray[pos.Y][pos.X] - 10;
			flagNum--;
		}

		// 更新并绘制地图
		updateMap();
		renderMap();
	}

	/****************************************
	Function:  judgeWin()
	Parameter: None(void)
	Return:    None(void)
	Description:
	判断是否成功
	*****************************************/
	void judgeWin() {
		//判断是否胜利
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (mapArray[i][j] >= 9 && mapArray[i][j] <= 28) {
					isWin = false;
				}
			}
		}
	}

	/****************************************
	Function:  renderIntro()
	Parameter: None(void)
	Return:    None(void)
	Description:
	绘制游戏说明
	*****************************************/
	void RenderIntro() {
		//清屏
		ClearScreen();

		//绘制游戏说明
		MovePos(57, 3);
		PutStringWithColor("游戏说明", 178, 34, 34, 0, 0, 0);
		MovePos(41, 5);
		PutString("本游戏为扫雷游戏，你需要根据你翻开地块的");
		MovePos(41, 6);
		PutString("数字提示，找到地图中所有的雷并做好标记。");
		MovePos(41, 7);
		PutString("操作规则如下：");
		MovePos(41, 9);
		PutString("1.点击鼠标左键(或按下回车键)翻开地块，如");
		MovePos(41, 10);
		PutString("果翻开的是地雷(雷的图案为'※')则游戏失败");
		MovePos(41, 11);
		PutString("，翻开的地块上显示的数字是该地块八邻域内");
		MovePos(41, 12);
		PutString("存在的雷的个数。");
		MovePos(41, 14);
		PutString("2.点击鼠标右键(或按下空格键)对地块进行标"); 
		MovePos(41, 15);
		PutString("记或解除标记(标记的图案为'★')");
		MovePos(41, 17);
		PutString("3.当你把所有非雷地块翻开，并把所有雷成功");
		MovePos(41, 18);
		PutString("标记，则游戏胜利。");
		MovePos(46, 21);
		PutString("(点击屏幕或者按下回车返回菜单)");
		Update();
		
		//等待输入
		while (true) {
			checkChoice();
			if (operation == 1 || operation == 2) break;
		}
	}

	/****************************************
	Function:  Play()
	Parameter: None(void)
	Return:    None(void)
	Description:
	开始游戏
	*****************************************/
	void Play() {
		timeStart = clock();							//开始计时
		flagNum = 0;									//初始化标记数
		stepNum = 0;									//初始化步数
		isFirst = true;									
		isLose = false;
		gameFlag = true;
		
		//进入循环
		while (gameFlag) {
			timeEnd = clock();
			isWin = true;
			checkChoice(); // 检查输入

			// 查看当前坐标是否需要更新背景
			if (posChoice.X != posChoiceOld.X || posChoice.Y != posChoiceOld.Y) {
				clearChoiceBackground(posChoiceOld);
				posChoiceOld = posChoice;
			}
			renderChoiceBackground(posChoice);

			// 放置当前选择位置的字符串：‘选择位置’，‘步数’，‘剩余地雷数’,‘时间’
			MovePos(2, 0);
			char strChoice[32] = "";
			sprintf_s(strChoice, "Choice(%u, %u)  ", posChoice.X+1, posChoice.Y+1);
			PutString(strChoice);
			char strFlag[32] = "";
			sprintf_s(strFlag, "Mine:%d  ", mineNum-flagNum);
			PutString(strFlag);
			char strStep[32] = "";
			sprintf_s(strStep, "Step:%u  ", stepNum);
			PutString(strStep);
			char strTime[32] = "";
			sprintf_s(strTime, "Time:%ds  ", (int)(timeEnd-timeStart)/CLOCKS_PER_SEC);
			PutString(strTime);
			Update();

			// 根据鼠标或键盘行为执行相应操作
			switch (operation) {
			case 1:
				// 翻块
				digBlock(posChoice);
				break;
			case 2:
				// 标记
				flagBlock(posChoice);
				break;
			}

			//判断是否失败
			if (isLose) {
				renderLoseTip();//绘制失败提示
				// 等待输入
				while (true) {
					checkChoice(); 
					if (operation == 1 || operation == 2) break;
				}
				//游戏结束
				gameFlag = false;
			}

			//判断是否胜利
			if (operation ==1|| operation==2) {
				judgeWin();
				if (isWin) {
					renderWinTip();//绘制成功提示
					// 等待输入
					while (true) {
						checkChoice(); 
						if (operation == 1 || operation == 2) break;
					}
					//游戏结束
					gameFlag = false;
				}
			}

			//处理每帧的事务
			updateMap(); // 更新地图画板
			Update();    // 更新操作到屏幕

			frame++;  // 渲染帧数自增
			clock_t elapsed = 25 - (clock() - tic); // 检查上一帧渲染时间，并计算与25的差值
			Sleep(elapsed > 0 ? elapsed : 0);	    // 若差值大于零，则休眠该差值的毫秒数，以确保每帧渲染不超过50帧
			tic = clock();						    // 更新上一次记录的时间
		}
	}

	/****************************************
	Function:  DestroytGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	结束游戏，回收动态申请的变量
	*****************************************/
	void DestroyGame() {
		delete[] mapCanvas;
		delete[] mapArray[0];
		delete[] mapArray;
		delete[] mapArrayPadding[0];
		delete[] mapArrayPadding;
	}
}