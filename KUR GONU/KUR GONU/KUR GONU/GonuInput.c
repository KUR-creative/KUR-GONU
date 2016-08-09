/***************************************************
 *고누 게임용 입력함수
 *
 * 약간의 변형을 거치면 일반적으로
 * 예외처리된 입력함수로 사용가능.
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "GonuInput.h"

// \n이 읽혀질 때 까지 입력버퍼에 저장된 문자를 지우는 함수
void clearLineReadBuffer()
{
	while( getchar() != '\n');
	//버퍼가 빈 경우에는 쓰면 안된다.
}


	//노 버퍼 엔터			return//int값
	//ENTER		13			
	//--------방향키를 이용한 노 버퍼 선택-----
	//LEFT		-32	75
	//RIGHT		-32	77
	//UP		-32	72
	//DOWN		-32	80
	//--------정방형 노 버퍼 선택------
	//0			48
	//1			49
	//2			50
	//3			51
	//4			52
	//5			53
	//6			54
	//7			55
	//8			56
	//9			57
//사용자의 입력을 처음 받아 가공하는 함수. 문자열로 입력을 받으며 온갅 예외처리를 한다.
// return값은 int형이다. 
//		숫자는 (int)'3'이런 식으로 비교한다.
//		기능키와 문자열커맨드는 정의된 상수를 이용한다.
int gonuInput( int getStr )// getStr = 0:문자열을 받지 않는다.	getStr = 1: 문자열도 받는다.
{
	char firstCh = 0;

	firstCh = _getch();
	if( firstCh == ARROW_START){	//방향키							
		firstCh = _getch();

		switch(firstCh){
			case UP:
			case DOWN:
			case RIGHT:
			case LEFT:
				return firstCh;
		}
		return 0;
	}
	else if( firstCh == ENTER  ||  (firstCh >= '0' && firstCh <= '9') ){	//엔터, 숫자키
		return firstCh;
	}
	else if(	getStr == 1
			&&	(	(firstCh >= 'A' && firstCh <= 'Z')  
				||  (firstCh >= 'a' && firstCh <= 'z')	)	) {//알파벳 대문자 || 소문자
		char* endChecker = NULL;
		int strLen;
		char str[INPUT_STR_LEN_MAX];	//문자열 커맨드 입력을 위한 버퍼
		char firstStr[2 + INPUT_STR_LEN_MAX] ={ firstCh, '\0' };	//str을 여기에 붙이므로 검사에 이걸 쓴다.

		_putch(firstCh);
		
		endChecker = fgets(str, sizeof(str), stdin);

		strLen = 0;
		while(*endChecker != '\0'){
			strLen++;
			endChecker++;
		}
		if(strLen >= INPUT_STR_LEN_MAX){//버퍼에 사용자가 입력한 값이 남을 때만
			clearLineReadBuffer();
			//입력한 문자열 배열의 길이가 \n 포함해서 (INPUT_STR_LEN_MAX1) 이상이면 사용한다.
			//(INPUT_STR_LEN_MAX1)-2 이하부터는 입력을 한번 더 받기 때문에 어색하다.
		}

		strcat(firstStr, str);

		if( areSameStr(firstStr,"skip\n", 6) ){
			return sKIP;
		}else if( areSameStr(firstStr,"SKIP\n", 6) ){
			return SKIP;
		}else if( areSameStr(firstStr,"menu\n", 6) ){
			return mENU;
		}else if( areSameStr(firstStr,"MENU\n", 6) ){
			return MENU;
		}else if( areSameStr(firstStr,"gg\n", 4) ){
			return gG;
		}else if( areSameStr(firstStr,"GG\n", 4) ){
			return GG;
		}else if( areSameStr(firstStr,"next\n", 6) ){
			return nEXT;
		}else if( areSameStr(firstStr,"NEXT\n", 6) ){
			return NEXT;
		}else if( areSameStr(firstStr,"re\n", 4) ){
			return rE;
		}else if( areSameStr(firstStr,"RE\n", 4) ){
			return RE;
		}else if( areSameStr(firstStr,"quit\n", 6) ){
			return qUIT;
		}else{
			clearLineReadBuffer();
			return 0;
		}
	}
}

int areSameStr(char* str, char* cmp, int count)
{
	int result = 0;
	int i;

	for(i = 0; i < count; i++){
		if( str[i] != cmp[i] ){
			return 0;
		}
	}

	return 1;
}

// thanks to codesafer.
// 확실히 좋은 방법이다. 나중에 이걸 할 일이 있다면 이용해보자...
void getn(int* n )
{
    int ch;
	
	*n = 0;

   	while(1){
		ch = getchar(); 
		
		if( ch >= '0'  &&  ch <= '9' ){//숫자가 나올 때까지 돌린다.
			
			do{
				*n = *n * 10 + (ch - '0'); //아스키코드를 숫자로 바꾸고 자릿수까지 맞춰준다
				ch = getchar(); 
			}while(ch >= '0'  &&  ch <= '9');
			
			return;
		}
		else{
			*n = -1;
			return;
		}
	}

   

}