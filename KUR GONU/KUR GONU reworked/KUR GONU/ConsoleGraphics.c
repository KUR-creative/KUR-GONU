/***************************************************
 *콘솔 게임용 그래픽 출력 함수들.
 *
 * Graph ADT.h, GameData.h를 사용하는 부분을 없애면 
 * 좀 더 일반적인 콘솔 게임에 사용 가능.
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "ConsoleGraphics.h"
#include "GraphADT.h"
#include "GameData.h"


//현재 커서를 x,y 좌표로 옮기는 함수.
//만일 x나 y중 하나의 값이라도 현재 콘솔의 화면 버퍼 크기를 넘어서면 작동을 안함.
void gotoXY(int x, int y)
{
	COORD coordinates = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

//현재 커서를 Point변수의 (x,y)로 옮겨주는 함수
//input : 커서를 옮기고 싶은 좌표값을 가진 Point변수의 주소
void gotoPoint(const Point *pos)
{
	COORD coordinates = {pos->x, pos->y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void printPoint(Point* pos, char ch)
{
	gotoPoint(pos);
	_putch(ch);
}

//현재 출력하려는 텍스트의 색과 배경색을 설정하는 함수.
/* 
 색깔		숫자
 
 검정		 0
 어두운 파랑	 1
 어두운 초록	 2
 어두운 하늘	 3
 어두운 빨강	 4
 어두운 보라	 5
 어두운 노랑	 6
 회색		 7
 어두운 회색	 8
 파랑		 9
 초록		10
 하늘		11
 빨강		12
 보라		13
 노랑		14
 하양		15
 */
void setColor(int txt, int back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16*back + txt);
}

//반올림 함수. 입력한 값을 소수 첫째자리에서 반올림하여 정수값으로 만든다.
int round(double num)
{
	if(num >= 0)	return (int)(num + 0.5);
	else	return (int)(num - 0.5);
}

//두 Point변수의 주소를 입력하면 (두 좌표가 형성하는) 선분 위의 모든 좌표들에 입력한 문자변수ch를 출력한다.
//이 때 두 좌표 그 자체에도 ch가 출력된다.(선분을 이루는 점까지 출력)
void drawLine(Point *p1, Point *p2, char ch)
{	
	
	int x1 = (p1->x), y1 = (p1->y);	//p1
	int x2 = (p2->x), y2 = (p2->y);	//p2
	//일차함수 y = a*x + b
	float a;//기울기
	float b;//y절편
	
	int length;//length는 선분의 길이. 선분을 이루는 점까지 포함한다.
	int i, temp;

	if(x1 == x2  &&  y1 == y2){
		gotoXY(x1, y1);
		_putch(ch);
		return;
	}
	
	if(x2 - x1){
		a = (float)(y2 - y1) / (float)(x2 - x1);
		b = (float)y1 - a*(float)x1;
	}else{//기울기가 무한일 때의 예외처리.( /0 처리) 
		
		length = y2 - y1;//x값 차이는 0이기에 y기준으로 출력된다.
		temp = abs(length);

		if(length > 0){
			for(i =	0; i <= temp; i++){//두 점까지 포함시키기 위해 0~length까지다.
				gotoXY( x1, y1+i );//x값은 y=ax+b에서 x를 묶어내어 x=(y-b)/a이다.
				_putch(ch);
			}
		}else{
			for(i =	0; i <= temp; i++){
				gotoXY( x1, y2+i );
				_putch(ch);
			}
		}

		return;
	} 

	//좌표간의 차이가 큰 놈으로 출력한다. 그래야 점선이 출력되지 않는다.
	if( abs(x2 - x1) > abs(y2 - y1) ){										//x기준 출력
		length = x2 - x1;	//'선분+두 점'의 길이보다 1이 작다.
		temp = abs(length);

		if(length > 0){
			float pre = a*x1 + b;

			for(i =	0; i <= temp; i++){//두 점까지 포함시키기 위해 0~length까지다.
				gotoXY(x1+i, round( pre + a*i ) );//y값은 일차식 y=ax+b를 내린 값이다.
				
				_putch(ch);
			}
		}else{
			float pre = a*x2 + b;

			for(i =	0; i <= temp; i++){
				gotoXY(x2+i, round( pre + a*i ) );
				_putch(ch);
			}
		}
	}else{																	//y기준 출력
		length = y2 - y1;
		temp = abs(length);
		
		if(length > 0){
			for(i =	0; i <= temp; i++){//두 점까지 포함시키기 위해 0~length까지다.
				gotoXY(  round( (y1+i - b)/a ), y1+i  );//x값은 y=ax+b에서 x를 묶어내어 x=(y-b)/a이다.
				_putch(ch);
			}
		}else{
			for(i =	0; i <= abs(length); i++){
				gotoXY(  round( (y2+i - b)/a ), y2+i  );
				_putch(ch);
			}
		}
		// a==0일때의 예외처리가 필요 없는 이유가, a==0일 때는 y가 같을 때인데 이때는 x를 기준으로 출력하기 때문이다. 이쪽 블럭으로는 오지도 않는다는 말.
	}
	
}

//빈 사각형을 대입한 값에 따라 만든다.
void printSquare(int startX, int startY, int width, int height, char ch)
{
	int i;

	for(i = 0; i <= width; i++){// 두개의 세로선 긋기
		gotoXY(startX + i, startY);
		putchar(ch);
		gotoXY(startX + i, startY + height);
		putchar(ch);
	}
	for(i = 0; i <= height; i++){// 두개의 가로선 긋기
		gotoXY(startX, startY + i);
		putchar(ch);
		gotoXY(startX + width, startY + i);
		putchar(ch);
	}

}

//꽉 찬 사각형을 대입한 값에 따라 만든다.
void printFullSquare(int startX, int startY, int width, int height, char ch)
{
	int x, y;

	for(y = 0; y <= height; y++){
		for(x = 0; x <= width; x++){
			gotoXY(startX + x, startY + y);
			putchar(ch);
		}
	}
	
}