#ifndef _CONSOLE_GRAPHICS_H_
#define _CONSOLE_GRAPHICS_H_

#ifndef _INC_STDIO
# include <stdio.h>
#endif

#ifndef _WINDOWS_
# include <Windows.h>
#endif

#ifndef _INC_CONIO
# include <conio.h>
#endif

#ifndef _INC_MATH
# include <math.h>
#endif


typedef struct Point {	//좌표 하나를 나타내는 구조체
	int x;
	int y;
} Point;

void gotoXY(int x, int y);	//Window.h
void setColor(int txt, int back);	//Window.h	
void gotoPoint(const Point *pos);	//Window.h, Point	
void drawLine(Point *p1, Point *p2, char ch);	//Window.h, conio.h, math.h, Point, gotoXY, round()
int round(double num);	//없음!
void printPoint(Point* pos, char ch);
void printSquare(int startX, int startY, int width, int height, char ch);
void printFullSquare(int startX, int startY, int width, int height, char ch);


enum colors{
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_AZURE,
	DARK_RED,
	DARK_PURPLE,//5
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,//10
	AZURE,
	RED,
	PURPLE,
	YELLOW,
	WHITE,//15
};

#endif