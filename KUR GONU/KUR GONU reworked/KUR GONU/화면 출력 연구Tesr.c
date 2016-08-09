/*다양한 연구*/
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>

typedef struct Point {	//좌표 하나를 나타내는 구조체
	int x;
	int y;
} Point;

void gotoXY(int x, int y);	//Window.h
void setColor(int txt, int back);	//Window.h	
void gotoPoint(const Point *pos);	//Window.h, Point	
void drawLine(const Point *p1,const Point *p2, char ch);	//Window.h, conio.h, math.h, Point, gotoXY, round()
int round(double num);	//없음!

int main(){
	Point pointArr_1[10]=
	{
		{0,80},
		{10,70},
		{20,60},
		{40,50},
		{60,40},
		{70,30},
		{60,20},
		{50,10},
		{30,0},
		{10,10},
	};
	Point p2 = {30,30};

	int i;
	//Point p1 = {0,0}, p2 = {30,30};
	//Point p1 = {10,0}, p2 = {30,30};
	//Point p1 = {28,0}, p2 = {30,30};
	//Point p1 = {30,0}, p2 = {30,30};//역시 이것도 문제됨. 0으로 나누는 경우의 예외처리 필요.
	//Point p1 = {31,0}, p2 = {30,30};
	//Point p1 = {50,0}, p2 = {30,30};
	//Point p1 = {50,10}, p2 = {30,30};
	//Point p1 = {50,30}, p2 = {30,30}; //문제 없음 ㅋㅋㅋㅋ 계속하면 아무키나 요거 때문임 ㅋㅋ
	//Point p1 = {50,40}, p2 = {30,30};
	//Point p1 = {50,50}, p2 = {30,30};
	//Point p1 = {40,50}, p2 = {30,30};
	//Point p1 = {33,50}, p2 = {30,30};
	//Point p1 = {30,50}, p2 = {30,30};//얘가 진짜 이상함. 아마도 예외처리!
	//Point p1 = {25,50}, p2 = {30,30};
	//Point p1 = {10,50}, p2 = {30,30};
	//Point p1 = {0,50}, p2 = {30,30};//이 경우에는 (int)를 이용하여 버림값을 선택해서 그런데, 반올림 함수를 직접 만들어야 할지도.
	//Point p1 = {0,32}, p2 = {30,30};//위와 같음.
	//Point p1 = {0,30}, p2 = {30,30};
	//Point p1 = {0,28}, p2 = {30,30};
	//Point p1 = {0,1}, p2 = {30,30};//내림값 문제.

	//Point p1 = {30,30}, p2 = {30,30};
	/*-------------------------------------------------------지금까지 했던 실험들.


	// puts, printf 와 gotoXY를 이용한 출력 비교하기.
	printf("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	Sleep(1000);
	for(i = 0; i < 800; i++){
		gotoXY(i,5);
		putch('m');
	}
	Sleep(1000);
	puts("\n\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	Sleep(1000);
	

	//gotoPoint함수 실험, 성공적.
	gotoPoint(&p1);
	putch('Y');
	

	//round함수 실험. 성공적.
	printf("%d \n", round(3.0) );
	printf("%d \n", round(2.8) );
	printf("%d \n", round(2.5) );
	printf("%d \n", round(2.569) );
	printf("%d \n", round(2.498) );
	printf("%d \n", round(2.3) );
	printf("%d \n", round(2.1) );
	printf("%d \n", round(2.0) );
	printf("%d \n", round(1.9) );
	printf("%d \n", round(1.4) );
	printf("%d \n", round(-1.4) );
	printf("%d \n", round(0) );
	printf("%d \n", round(-1.5) );
	printf("%d \n", round(-1.6) );
	printf("%d \n", round(1.4) );

	-------------------------------지금은 필요없는 실험들(나중엔 다시 주석 빼야됨)*/
	
	
	//drawLine함수 실험, 성공적!!

	for(i = 0; i < 10; i++){
		drawLine(pointArr_1 + i, &p2, '#');
	}
	
	/*gotoPoint(&p1);
	_putch('1');
	gotoPoint(&p2);
	_putch('2');*/
	
	_getch();//계속하려면 아무키나.. 지워두림

	


	return 0;
}

//현재 커서를 x,y 좌표로 옮기는 함수.
//만일 x나 y중 하나의 값이라도 현재 콘솔의 화면 버퍼 크기를 넘어서면 작동을 안함.
//"mode con: 을 소스에서 검색해보면 버퍼 최대크기를 알 수 있음. 최대크기 -1 까지가 한계다.
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


//현재 출력하려는 텍스트의 색과 배경색을 설정하는 함수.
//밑에 목록들은 나중에 enum을 써서 상수로 만들라.
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

//두 Point변수의 주소를 입력하면 (두 좌표가 형성하는) 선분 위의 모든 좌표들에 입력한 문자변수ch를 출력한다.
//이 때 두 좌표 그 자체에도 ch가 출력된다.(선분을 이루는 점까지 출력)
//$$이 방법은 DDA 알고리즘이다. 코드세이퍼는 mid-point line / bresenham's 알고리즘을 추천했다. 음. 나중에 필요하면 해보자.
void drawLine(const Point *p1,const Point *p2, char ch)
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
	/*코세의 추천: x1 을 min(x1, x2), x2 를 max(x1, x2) 로 정의하면 하나로 줄겠네. 물론, if 문에서 x1, x2 를 비교하고 length 양수값으로 셋, x1, x2 swap 을 할지 말지를 선택하게 하는식으로 풀어야 정상동작 하는거지.
	if (x1 < x2) {
		length = x2 - x1; 
	} else { 
		length = x1 - x2; 
		x1 ^= x2 ^= x1 ^= x1; //요거는 스왑을 하는 방법이랜다. ... 걍 심심해서 넣은거래
	} 
	요걸 써준 다음에 for문을 하나만 쓴다.*/

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

//반올림 함수. 입력한 값을 소수 첫째자리에서 반올림하여 정수값으로 만든다.
int round(double num)
{
	if(num >= 0)	return (int)(num + 0.5);
	else	return (int)(num - 0.5);
}