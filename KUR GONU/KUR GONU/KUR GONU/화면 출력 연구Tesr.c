/*�پ��� ����*/
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>

typedef struct Point {	//��ǥ �ϳ��� ��Ÿ���� ����ü
	int x;
	int y;
} Point;

void gotoXY(int x, int y);	//Window.h
void setColor(int txt, int back);	//Window.h	
void gotoPoint(const Point *pos);	//Window.h, Point	
void drawLine(const Point *p1,const Point *p2, char ch);	//Window.h, conio.h, math.h, Point, gotoXY, round()
int round(double num);	//����!

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
	//Point p1 = {30,0}, p2 = {30,30};//���� �̰͵� ������. 0���� ������ ����� ����ó�� �ʿ�.
	//Point p1 = {31,0}, p2 = {30,30};
	//Point p1 = {50,0}, p2 = {30,30};
	//Point p1 = {50,10}, p2 = {30,30};
	//Point p1 = {50,30}, p2 = {30,30}; //���� ���� �������� ����ϸ� �ƹ�Ű�� ��� ������ ����
	//Point p1 = {50,40}, p2 = {30,30};
	//Point p1 = {50,50}, p2 = {30,30};
	//Point p1 = {40,50}, p2 = {30,30};
	//Point p1 = {33,50}, p2 = {30,30};
	//Point p1 = {30,50}, p2 = {30,30};//�갡 ��¥ �̻���. �Ƹ��� ����ó��!
	//Point p1 = {25,50}, p2 = {30,30};
	//Point p1 = {10,50}, p2 = {30,30};
	//Point p1 = {0,50}, p2 = {30,30};//�� ��쿡�� (int)�� �̿��Ͽ� �������� �����ؼ� �׷���, �ݿø� �Լ��� ���� ������ ������.
	//Point p1 = {0,32}, p2 = {30,30};//���� ����.
	//Point p1 = {0,30}, p2 = {30,30};
	//Point p1 = {0,28}, p2 = {30,30};
	//Point p1 = {0,1}, p2 = {30,30};//������ ����.

	//Point p1 = {30,30}, p2 = {30,30};
	/*-------------------------------------------------------���ݱ��� �ߴ� �����.


	// puts, printf �� gotoXY�� �̿��� ��� ���ϱ�.
	printf("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	Sleep(1000);
	for(i = 0; i < 800; i++){
		gotoXY(i,5);
		putch('m');
	}
	Sleep(1000);
	puts("\n\nmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
	Sleep(1000);
	

	//gotoPoint�Լ� ����, ������.
	gotoPoint(&p1);
	putch('Y');
	

	//round�Լ� ����. ������.
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

	-------------------------------������ �ʿ���� �����(���߿� �ٽ� �ּ� ���ߵ�)*/
	
	
	//drawLine�Լ� ����, ������!!

	for(i = 0; i < 10; i++){
		drawLine(pointArr_1 + i, &p2, '#');
	}
	
	/*gotoPoint(&p1);
	_putch('1');
	gotoPoint(&p2);
	_putch('2');*/
	
	_getch();//����Ϸ��� �ƹ�Ű��.. �����θ�

	


	return 0;
}

//���� Ŀ���� x,y ��ǥ�� �ű�� �Լ�.
//���� x�� y�� �ϳ��� ���̶� ���� �ܼ��� ȭ�� ���� ũ�⸦ �Ѿ�� �۵��� ����.
//"mode con: �� �ҽ����� �˻��غ��� ���� �ִ�ũ�⸦ �� �� ����. �ִ�ũ�� -1 ������ �Ѱ��.
void gotoXY(int x, int y)
{
	COORD coordinates = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

//���� Ŀ���� Point������ (x,y)�� �Ű��ִ� �Լ�
//input : Ŀ���� �ű�� ���� ��ǥ���� ���� Point������ �ּ�
void gotoPoint(const Point *pos)
{
	COORD coordinates = {pos->x, pos->y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}


//���� ����Ϸ��� �ؽ�Ʈ�� ���� ������ �����ϴ� �Լ�.
//�ؿ� ��ϵ��� ���߿� enum�� �Ἥ ����� �����.
/* 
 ����		����
 
 ����		 0
 ��ο� �Ķ�	 1
 ��ο� �ʷ�	 2
 ��ο� �ϴ�	 3
 ��ο� ����	 4
 ��ο� ����	 5
 ��ο� ���	 6
 ȸ��		 7
 ��ο� ȸ��	 8
 �Ķ�		 9
 �ʷ�		10
 �ϴ�		11
 ����		12
 ����		13
 ���		14
 �Ͼ�		15
 */
void setColor(int txt, int back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16*back + txt);
}

//�� Point������ �ּҸ� �Է��ϸ� (�� ��ǥ�� �����ϴ�) ���� ���� ��� ��ǥ�鿡 �Է��� ���ں���ch�� ����Ѵ�.
//�� �� �� ��ǥ �� ��ü���� ch�� ��µȴ�.(������ �̷�� ������ ���)
//$$�� ����� DDA �˰����̴�. �ڵ弼���۴� mid-point line / bresenham's �˰����� ��õ�ߴ�. ��. ���߿� �ʿ��ϸ� �غ���.
void drawLine(const Point *p1,const Point *p2, char ch)
{	
	
	int x1 = (p1->x), y1 = (p1->y);	//p1
	int x2 = (p2->x), y2 = (p2->y);	//p2
	//�����Լ� y = a*x + b
	float a;//����
	float b;//y����
	
	int length;//length�� ������ ����. ������ �̷�� ������ �����Ѵ�.
	int i, temp;

	if(x1 == x2  &&  y1 == y2){
		gotoXY(x1, y1);
		_putch(ch);
		return;
	}
	
	if(x2 - x1){
		a = (float)(y2 - y1) / (float)(x2 - x1);
		b = (float)y1 - a*(float)x1;
	}else{//���Ⱑ ������ ���� ����ó��.( /0 ó��) 
		
		length = y2 - y1;//x�� ���̴� 0�̱⿡ y�������� ��µȴ�.
		temp = abs(length);

		if(length > 0){
			for(i =	0; i <= temp; i++){//�� ������ ���Խ�Ű�� ���� 0~length������.
				gotoXY( x1, y1+i );//x���� y=ax+b���� x�� ����� x=(y-b)/a�̴�.
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
	/*�ڼ��� ��õ: x1 �� min(x1, x2), x2 �� max(x1, x2) �� �����ϸ� �ϳ��� �ٰڳ�. ����, if ������ x1, x2 �� ���ϰ� length ��������� ��, x1, x2 swap �� ���� ������ �����ϰ� �ϴ½����� Ǯ��� ������ �ϴ°���.
	if (x1 < x2) {
		length = x2 - x1; 
	} else { 
		length = x1 - x2; 
		x1 ^= x2 ^= x1 ^= x1; //��Ŵ� ������ �ϴ� ����̷���. ... �� �ɽ��ؼ� �����ŷ�
	} 
	��� ���� ������ for���� �ϳ��� ����.*/

	//��ǥ���� ���̰� ū ������ ����Ѵ�. �׷��� ������ ��µ��� �ʴ´�.
	if( abs(x2 - x1) > abs(y2 - y1) ){										//x���� ���
		length = x2 - x1;	//'����+�� ��'�� ���̺��� 1�� �۴�.
		temp = abs(length);

		if(length > 0){
			float pre = a*x1 + b;

			for(i =	0; i <= temp; i++){//�� ������ ���Խ�Ű�� ���� 0~length������.
				gotoXY(x1+i, round( pre + a*i ) );//y���� ������ y=ax+b�� ���� ���̴�.
				
				_putch(ch);
			}
		}else{
			float pre = a*x2 + b;

			for(i =	0; i <= temp; i++){
				gotoXY(x2+i, round( pre + a*i ) );
				_putch(ch);
			}
		}
	}else{																	//y���� ���
		length = y2 - y1;
		temp = abs(length);
		
		if(length > 0){
			for(i =	0; i <= temp; i++){//�� ������ ���Խ�Ű�� ���� 0~length������.
				gotoXY(  round( (y1+i - b)/a ), y1+i  );//x���� y=ax+b���� x�� ����� x=(y-b)/a�̴�.
				_putch(ch);
			}
		}else{
			for(i =	0; i <= abs(length); i++){
				gotoXY(  round( (y2+i - b)/a ), y2+i  );
				_putch(ch);
			}
		}
		// a==0�϶��� ����ó���� �ʿ� ���� ������, a==0�� ���� y�� ���� ���ε� �̶��� x�� �������� ����ϱ� �����̴�. ���� �����δ� ������ �ʴ´ٴ� ��.
	}
	
}

//�ݿø� �Լ�. �Է��� ���� �Ҽ� ù°�ڸ����� �ݿø��Ͽ� ���������� �����.
int round(double num)
{
	if(num >= 0)	return (int)(num + 0.5);
	else	return (int)(num - 0.5);
}