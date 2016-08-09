/*다양한 기능을 수행할 수 있는 코드들을 테스트한다. 
 *제대로 작동하는 녀석들은 함수로 만들어 보존한다.
 */

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/*쓸 줄 아는 함수 목록*/

//Sleep(시간);	인수 시간만큼 대기한다.인수는 밀리세컨 단위로 입력한다.  						<Windows.h>	저걸 끝내려면 signal을 프로세스로 보내야 한다는데 시-발 모르겠다. 잘모르는 건 하지 말아야한다.
//system("mode con: cols=300 lines=20");	콘솔 화면 버퍼의 크기를 바꿔주는 system("명령").	<Windows.h>	************** 다른 컴퓨터에서는 어떤지 실험해봐야 함. 아마 안될듯. 해상도는 상관없음.
//kbhit();	 키보드의 입력이 있으면 1을 반환, 없으면 0을 반환하는 함수다.						
//방향키 체크 코드.. 함수로 만들기는 조금 애매하다.

/*커스텀 함수 목록-거의다 윈도우 API 함수에 커버만 씌운 수준.*/
void gotoXY(int x, int y);
void setColor(int txt, int back);

int main(void){
	int x = 1;
	int y = 1;
	char ch1 ='*';
	char ch2, ch3;
	COORD pos = {x,y};

	system("mode con: cols=150 lines=40");//콘솔 화면 버퍼의 크기를 바꿔주는 system("명령").

	//printf("###################################\n###################################");
	//printf("###################################\n###################################");
	//printf("###################################\n################");
	Sleep(5000);
	if(kbhit() != 0){//kbhit()은 키보드의 입력이 있으면 1을 반환, 없으면 0을 반환하는 함수다.
		ch1 = _getch();//사용자 입력을 받는 함수는 항상 무한한 시간동안 기다린다.
		printf("%d", ch1);//출력을 할지라도 Sleep(5000)은 끝나지 않는다. 저걸 끝내려면 signal을 프로세스로 보내야 한다는데 시-발 모르겠다. 잘모르는 건 하지 말아야한다.
	}
	
	gotoXY(75,301);
	
	printf("0--------------->");

	ch2 = getch();
	//printf("%d", ch2);
	if(ch2 == 0xffffffe0)	ch2 = getch();//이게 바로 방향키 체크 코드

	printf("%d", ch2);
	
	setColor(1,15);
	printf("\n\n하하! 함수로 만들었지!");
	Sleep(10000);//인수 시간만큼 대기한다.인수는 밀리세컨 단위로 입력한다.  Windows.h에 있음.
	system("cls");//"cls" 콘솔 창의 모든 내용을 지운다.
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