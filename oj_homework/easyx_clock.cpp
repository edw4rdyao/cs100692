#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define PI 3.1415926

/*绘制钟表框架*/
void drawClock() {
	int x, y, x1, y1; 
	double ang;

	//绘制表框
	setcolor(RGB(162, 94, 94));
	setbkcolor(WHITE);
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 10);
	fillcircle(225, 240, 7);
	circle(225, 240, 152);
	setfillcolor(WHITE);
	fillcircle(225, 240, 148);
	setfillcolor(BLACK);

	//绘制刻度
	for (int i = 0; i < 60; i++) {
		ang = i * PI / 30;
		if (i % 15 == 0) {
			x = int(225 + 141 * sin(ang));
			y = int(240 + 141 * cos(ang));
			solidcircle(x, y, 6);
		}
		else if(i % 5 == 0) {
			setcolor(BLACK);
			setlinestyle(PS_SOLID, 5);
			x = int(225 + 142 * sin(ang));
			y = int(240 + 142 * cos(ang));
			x1 = int(x - 9 * sin(ang));
			y1 = int(y - 9 * cos(ang));
			line(x, y, x1, y1);
		}
		else {
			setcolor(BLACK);
			setlinestyle(PS_SOLID, 2);
			x = int(225 + 142 * sin(ang));
			y = int(240 + 142 * cos(ang));
			x1 = int(x - 5 * sin(ang));
			y1 = int(y - 5 * cos(ang));
			line(x, y, x1, y1);
		}
	}

	//绘制数字与文字
	settextcolor(BLACK);
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(210, 105, "12");
	outtextxy(335, 220, "3");
	outtextxy(215, 335, "6");
	outtextxy(95, 220, "9");
	outtextxy(170, 155, "Tongji");
}

/*绘制指针*/
void drawPins(tm t) {
	int x, y, x1, y1, x2, y2;
	double ang1, ang2, ang3;

	//绘制时针
	ang1 = (t.tm_hour + double(t.tm_min) / 60) * PI / 6;
	x = int(225 + 65 * sin(ang1));
	y = int(240 - 65 * cos(ang1));
	setcolor(BLACK);
	setlinestyle(PS_SOLID, 9);
	line(225, 240, x, y);
	
	//绘制分针
	ang2 = (t.tm_min + double(t.tm_sec) / 60) * PI / 30;
	x1 = int(225 + 100 * sin(ang2));
	y1 = int(240 - 100 * cos(ang2));
	setlinestyle(PS_SOLID, 6);
	line(225, 240, x1, y1);

	//绘制秒针
	ang3 = t.tm_sec * PI / 30;
	x2 = int(225 + 130 * sin(ang3));
	y2 = int(240 - 130 * cos(ang3));
	setcolor(RED);
	setlinestyle(PS_SOLID, 2);
	line(225, 240, x2, y2);
	
	//更新指针
	Sleep(1000);
	setcolor(WHITE);
	setlinestyle(PS_SOLID, 9);
	line(225, 240, x, y);
	setlinestyle(PS_SOLID, 6);
	line(225, 240, x1, y1);
	setlinestyle(PS_SOLID, 2);
	line(225, 240, x2, y2);

	//更新数字与文字
	settextcolor(BLACK);
	settextstyle(40, 0, _T("Consolas"));
	outtextxy(210, 105, "12");
	outtextxy(335, 220, "3");
	outtextxy(215, 335, "6");
	outtextxy(95, 220, "9");
	outtextxy(170, 155, "Tongji");
}

int main()
{
	struct tm t;
	initgraph(450, 480);				//初始化画板
	SetWindowText(GetHWnd(), "电子钟");	//命名
	//绘制模板
	drawClock();						//绘制钟表框架

	while (!_kbhit()) {
		time_t now;
		time(&now);
		localtime_s(&t, &now);			//获取当地时间
		drawPins(t);					//绘制指针
	}                
	char c;
	c=_getch();                
	closegraph();
	return 0;
}