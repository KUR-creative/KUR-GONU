/********************************************************
 *메뉴 루틴, 사용자 UI: 로그창, 사용자창 관련 함수 모음.
 * 
 * 사실 여기에 있는 함수만으로는 메뉴 인터페이스를 구현할 수 없다.
 * main()에서 직접 Digraph를 만들고 거기에 맞춰 구현해야 한다. 
 * 고누게임에선 쓸데없이 구조가 복잡해지기에 
 * 메뉴루틴을 구현하는 함수는 포함하지 않았다.
 *
 * 큐를 이용한 로그창 표현 함수가 있다.
 *
 *만든놈 : KUR	
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 ********************************************************/

#include "MenuAndUI.h"
#include "GonuInput.h"
#include "GameData.h"

// 장면에 따라 기능이 달라지는 함수들을 처음에 쓰고, 각 함수들을 장면마다 모아놓았다.

// 사용자 입력함수 반환값과 장면 ID는 다르기에 필요한 함수이다.
// 장면마다 입력에 다르게 반응하기 때문에 함수배열을 쓴다.
// input: 장면ID, 사용자 입력값		
// output: NULL_ID or 장면ID 
int getSceneId(int sceneId, int input)
{
	static int ( *inputInterpret[SCENE_NUM_MAX] ) (int) = 
	{
		onTitle,
		onMainMenu,
		onCredit,
		onOption,
		onHowToPlay,
		onModeSelect,
		onVsSelect,
		onModeExplanation,
		onGame,
		onEndGameMenu,
		onQuit,
	};

	return inputInterpret[sceneId]( input );
}

// sceneNumber를 입력하면 입력한 화면으로 전환된다.
void printScene(int scene)
{
	static void ( *sceneArr[SCENE_NUM_MAX] )() = // 함수원형, 함수선언, 장면 번호, 지역변수 배열 @ 
		{
			title,		//	0
			mainMenu,
			credit,
			option,
			howToPlay,
			modeSelect,	//	5
			vsSelect,
			modeExplanation,
			game,
			endGameMenu,
			quit,		// 10
		};

	system("cls");
	
	sceneArr[scene]();

}

//화살표 키를 이용하여 메뉴를 선택할 수 있다. 장면마다 기능이 달라진다.
int useArrowToSelectMenu(int currentScene)																					//////// h에 넣으쇼 /////////
{
	//방향키 메뉴 선택이 필요한 모든 장면들에 대한 이차원 배열들.
	
	// 1.복잡함, 2.메모리  문제 때문에 3차원 배열은 쓰지 않는다.
	static int mainMenuValues[4][VALUE_NUM] = 
	{
	//	반환값	출력할 것			X			 Y
		{'1',	(int)"1. 게임하기",	MENU_HEAD_X, 10},
		{'2',	(int)"2. 옵션",		MENU_HEAD_X, 12},
		{'3',	(int)"3. 만든놈?",	MENU_HEAD_X, 14},
		{qUIT,	(int)"quit. 종료",	MENU_HEAD_X, 17},
	};

	static int creditValues[1][VALUE_NUM] =
	{
		{'0',	(int)"0. 뒤로",		10,			 CONSOLE_HEIGHT_NUM /3 + 16	}
	};

	static int optionValues[1][VALUE_NUM] =
	{
		{'0',	(int)"0. 뒤로",		10,			 CONSOLE_HEIGHT_NUM /3 + 16	}
	};

	static int modeSelectValues[6][VALUE_NUM] = 
	{
		{'1',	(int)"1. simple mode",		MENU_HEAD_X, 10},
		{'2',	(int)"2. full mode",		MENU_HEAD_X, 12},
		{'3',	(int)"3. free deploy mode",	MENU_HEAD_X, 14},
		{'4',	(int)"4. custom mode 1",	MENU_HEAD_X, 16},
		{'5',	(int)"5. custom mode 2",	MENU_HEAD_X, 18},
		{'0',	(int)"0. 메인 메뉴로",		MENU_HEAD_X, 25},
	};

	static int vsSelectValues[4][VALUE_NUM] = 
	{
		{'1',	(int)"1. MAN  VS  MAN",						MENU_HEAD_X, 10},
		{'2',	(int)"2. MAN  VS  MACHINE (개발 중)",		MENU_HEAD_X, 12},
		{'3',	(int)"3. MACHINE  VS  MACHINE (개발 중)",	MENU_HEAD_X, 14},
		{'0',	(int)"0. 모드 선택으로",						MENU_HEAD_X, 17},
	};

	static int endGameMenuValues[4][VALUE_NUM] =
	{
		{'1',	(int)"1. 다시하기!!!",							MENU_HEAD_X, 10},
		{'2',	(int)"2. 게임 모드 선택으로",					MENU_HEAD_X, 12},
		{'3',	(int)"3. VS COM?  VS MAN? 대결 상대 선택으로",	MENU_HEAD_X, 14},
		{qUIT,	(int)"quit. 게임 종료",							MENU_HEAD_X, 17},
	};

	switch( currentScene ){
		case MAIN_MENU:
			return menuFocusChangeByArrow( mainMenuValues,	4,	MENU_HEAD_X,	25 );//배열, 배열의 행 수, pX, pY
			break;
		case CREDIT:
			return menuFocusChangeByArrow( creditValues,	1,	17,				CONSOLE_HEIGHT_NUM /3 + 16 );
			break;
		case OPTION:
			return menuFocusChangeByArrow( optionValues,	1,	17,				CONSOLE_HEIGHT_NUM /3 + 16 );
			break;
		case MODE_SELECT:
			return menuFocusChangeByArrow( modeSelectValues,6,	MENU_HEAD_X,	25 );
			break;
		case VS_SELECT:
			return menuFocusChangeByArrow( vsSelectValues,	4,	MENU_HEAD_X,	21 );
			break;
		case END_GAME_MENU:
			return menuFocusChangeByArrow( endGameMenuValues,4,	MENU_HEAD_X,	19 );
			break;
		default:
			//printf("방향키 인풋 시스템이 잘못 사용되었다.");
			return 0; //아무일도 안 생기나?
	}
}

//---------------------------------------------장면 함수들----------------------------------------
void title()
{
	gotoXY( CONSOLE_WIDTH_NUM /2 - 3, CONSOLE_HEIGHT_NUM /2 - 4 );
	puts("KUR's GONU ");

	gotoXY( CONSOLE_WIDTH_NUM /2 - 4, CONSOLE_HEIGHT_NUM - 7 );
	puts("press any key");

	gotoXY( CONSOLE_WIDTH_NUM /2 +10, CONSOLE_HEIGHT_NUM - 7 ); //커서 위치 조정
}
int onTitle(int input)
{
	// 타이틀에선 press any key
	return MAIN_MENU;
}


void mainMenu()
{
	gotoXY(MENU_HEAD_X, 10);	puts("1. 게임하기");

	gotoXY(MENU_HEAD_X, 12);	puts("2. 옵션");
	
	gotoXY(MENU_HEAD_X, 14);	puts("3. 만든놈?");
	
	
	gotoXY(MENU_HEAD_X, 17);	puts("quit. 종료");

	

	gotoXY(MENU_HEAD_X, 21);	puts("원하는 항목의 숫자키를 누르세요.");
	gotoXY(MENU_HEAD_X, 22);	puts("혹은 방향키를 눌러 선택하고 엔터를 눌러 결정하세요. ");

	gotoXY(MENU_HEAD_X, 25);//커서조절

}
int onMainMenu(int input)				
{
	switch( input )
	{
	case '1':
		return HOW_TO_PLAY;
		break;

	case '2':
		return OPTION;
		break;

	case '3':
		return CREDIT;
		break;

	case qUIT:
		return QUIT;
		break;

	default:
		return NULL_ID;
	}
}
	
void credit()
{
	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 - 4 );	puts("KUR creative ");

	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 - 2 );	puts("https://www.facebook.com/KURcreative");
	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 - 1 );	puts("kur941017@gmail.com");
	
	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 + 1 );	puts("이 겜 디자인에서 코딩까지 전부 내가 다함 :D ");




	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 + 7 );	puts("제 코드를 리뷰해 주시거나 질문에 답해주셨던 ");
	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 + 8 );	puts("133t    codesafer    ssonacy    꼬마야    ㅅㅅㅅ"	);
	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 + 9 );	puts("그리고 차*민 에게 감사를 표합니다.");


	



	gotoXY( 10, CONSOLE_HEIGHT_NUM /3 + 16 );	puts("0. 뒤로");		gotoXY( 17, CONSOLE_HEIGHT_NUM /3 + 16 );//커서 조절
}
int onCredit(int input)
{
	switch( input )
	{
	case '0':
		return MAIN_MENU;
		break;
	default:
		return NULL_ID;
	}
}

void option()
{
	printf("\n option... \
		  \n\n 원래는 옵션으로 뭔가를 바꿀수 있게 하려 했었지. 그 때는 C로 파일 입출력을 할 줄 몰랐었어. \
		    \n 근데 .gonu파일을 통해서 custom게임을 만들 수 있게 되니까, 쓸모가 없어졌지...\
		  \n\n 그런데도 이 공간을 남긴 건 순전히 귀찮아서 입니다. \
		    \n 여기를 지우려면 menu를 구현하는 FSM에서 정점 하나를 빼야하는데 귀찮아요. 코드 읽기도 귀찮아~ 그러니까 걍 냅뒀스빈다 낄낄 \
	    \n\n\n 0을 누르면 뒤로 갈 수 있을 겁니다. \n");
}
int onOption(int input)
{
	switch( input )
	{
	case '0':
		return MAIN_MENU;
		break;
	default:
		return NULL_ID;
	}
}

void howToPlay()
{
	game();
}
int onHowToPlay(int input)
{
	switch( input )
	{
	case sKIP:
		return MODE_SELECT;
		break;

	case SKIP:
		return MODE_SELECT;
		break;

	default:
		return NULL_ID;
	}
}

void modeSelect()
{
	
	gotoXY(MENU_HEAD_X, 10);
	puts("1. simple mode");			//정사각형 3개의 큰 맵, 해결사 X.
	gotoXY(MENU_HEAD_X, 12);	
	puts("2. full mode");			//정사각형 3개의 큰 맵, 해결사 O.
	gotoXY(MENU_HEAD_X, 14);
	puts("3. free deploy mode");	//정사각형 3개의 큰 맵, 해결사 O, 자유 배치 가능.
	gotoXY(MENU_HEAD_X, 16);
	puts("4. custom mode 1");		// "custom1.gonu"
	gotoXY(MENU_HEAD_X, 18);
	puts("5. custom mode 2");		// "custom2.gonu"
	gotoXY(MENU_HEAD_X, 21);
	puts("...더 많은 모드가 만들어질 수 있습니다! ");

	
	gotoXY(MENU_HEAD_X, 25);
	puts("0. 메인 메뉴로");
}
int onModeSelect(int input)//	전역변수 mode를 결정한다. 중요!!!
{
	switch( input )
	{
	case '1':
		lastGameMode = mode = SIMPLE;
		return VS_SELECT;
		break;

	case '2':
		lastGameMode = mode = FULL;
		return VS_SELECT;
		break;

	case '3':
		lastGameMode = mode = FREE_DEPLOY;
		return VS_SELECT;
		break;

	case '4':
		lastGameMode = mode = CUSTOM1;
		return VS_SELECT;
		break;

	case '5':
		lastGameMode = mode = CUSTOM2;
		return VS_SELECT;
		break;

	case '0':
		return MAIN_MENU;
		break;

	default:
		return NULL_ID;
	}
}


void vsSelect()
{
	gotoXY(MENU_HEAD_X, 10);
	puts("1. MAN  VS  MAN");
	gotoXY(MENU_HEAD_X, 12);
	puts("2. MAN  VS  MACHINE (개발 중)" );
	gotoXY(MENU_HEAD_X, 14);
	puts("3. MACHINE  VS  MACHINE (개발 중)");

	gotoXY(MENU_HEAD_X, 17);
	puts("0. 모드 선택으로");
}
int onVsSelect(int input)
{
	switch( input )
	{
	case '1':
		return MODE_EXPLANATION;
		break;

	case '0':
		return MODE_SELECT;
		break;

	default:
		return NULL_ID;
	}
}

void modeExplanation()
{
	printf("현재 mode 설명 \n\n");

	if( mode == SIMPLE ){
		printf("자세한 설명은 생략한다.\n");
	}else if( mode == FULL ){
		printf("★ 모양 말은 한번에 두 칸을 갈 수 있다. \
			\n 1칸만 가는 건 불가능 하고 무조건 2칸을 가야한다.");
	}else if( mode == FREE_DEPLOY ){
		printf(" 말을 유저 입맛대로 배치할 수 있는 모드입니다. \
			  \n 이 게임은 온라인 같은 건 지원하지 않으므로 옆에 앉은 사람과 할 수 밖에 없는데 \
			  \n 상대편이 말을 배치할 때는 다른 곳을 보고 있읍시다. \
			\n\n 말 배치는 숫자키만을 이용합니다. 위치를 한번 선택하면 반드시 말을 둬야하므로 \
			  \n 신중히 판단하시기 바랍니다. \
			\n\n free.gonu에서 F다음 숫자를 고치면 ●, ★, ③, ④, ⑤ 말이 나오는 수를 조절할 수 있습니다. \
			  \n 단 합계 10개 이하로 하시기 바랍니다. 그 이상은 undefined입니다." );
	}else if( mode == CUSTOM1 ){
		printf(" custom1.gonu 파일을 편집하여 자신만의 게임을 만들 수 있습니다. \
			  \n 파일을 어떻게 만들어야 하는지는 readme.txt를 보시면 됩니다. \
			  \n 예제파일의 이름을 custom1.gonu로 바꾸면 여기서 플레이 가능합니다." );
	}else if( mode == CUSTOM2 ){
		printf(" custom2.gonu 파일을 편집하여 자신만의 게임을 만들 수 있습니다. \
			  \n 파일을 어떻게 만들어야 하는지는 readme.txt를 보시면 됩니다. \
			  \n 예제파일의 이름을 custom2.gonu로 바꾸면 여기서 플레이 가능합니다." );
	}else{
		printf("존재하지 않는 모드입니다. 전역변수 mode에 잘못된 값이 대입되었습니다.");
	}
	
}
int onModeExplanation(int input)
{
	return GAME;
}

void game()
{
	printSquare( LOG_SCREEN_X, LOG_SCREEN_Y, LOG_SCREEN_WIDTH, LOG_SCREEN_HEIGHT, '@' );// 로그 창
	
	gotoXY(LOG_SCREEN_X, LOG_SCREEN_HEIGHT + 2);
	puts("※ gg, GG를 입력하여 항복할 수 있습니다."); // \n디버깅 : skip 으로 엔드 메뉴로 넘어가자");
	gotoXY(LOG_SCREEN_X, LOG_SCREEN_HEIGHT + 3);
	puts("※ re, RE 입력 혹은 ESC 키로 말을 재선택 합니다.");
	gotoXY(LOG_SCREEN_X, LOG_SCREEN_HEIGHT + 4);
	puts("※ next, NEXT를 입력하여 턴을 넘길 수 있습니다.");
	gotoXY(LOG_SCREEN_X, LOG_SCREEN_HEIGHT + 5);
	puts("   단 Life ♥가 하나 감소합니다.");
	//플레이어의 컨트롤 스크린은 활성화 : '#',	비활성화 : '.'
	printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 1p 창

	printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 2p 창

	
	gotoXY( P1_SCREEN_X + 2, P1_SCREEN_Y + 2 ); setColor(RED, BLACK);	puts("RED	");
	gotoXY( P1_SCREEN_X + 2, P1_SCREEN_Y + 4 ); setColor(WHITE, BLACK);	puts("Life"); 
	gotoXY( P1_SCREEN_X + 2, P1_SCREEN_Y + 5 ); setColor(WHITE, BLACK);	puts("Kills");

	gotoXY( P1_SCREEN_X + 2, P2_SCREEN_Y + 2 ); setColor(BLUE, BLACK);	puts("BLUE	");
	gotoXY( P1_SCREEN_X + 2, P2_SCREEN_Y + 4 ); setColor(WHITE, BLACK);	puts("Life"); 
	gotoXY( P1_SCREEN_X + 2, P2_SCREEN_Y + 5 ); setColor(WHITE, BLACK);	puts("Kills");

	setColor(DARK_GRAY, BLACK);
}
int onGame(int input)
{
	return END_GAME_MENU;
}

void endGameMenu()
{
	gotoXY(MENU_HEAD_X, 10);	puts("1. 다시하기!!!");
	
	gotoXY(MENU_HEAD_X, 12);	puts("2. 게임 모드 선택으로" );
	
	gotoXY(MENU_HEAD_X, 14);	puts("3. VS COM?  VS MAN? 대결 상대 선택으로");
	

	gotoXY(MENU_HEAD_X, 17);	puts("quit. 게임 종료");


	gotoXY(MENU_HEAD_X, 19);//커서 이동
}
int onEndGameMenu(int input)
{
	switch( input )
	{
	case '1':
		mode = lastGameMode;
		return GAME;
		break;

	case '2':
		return MODE_SELECT;
		break;

	case '3':
		mode = lastGameMode;
		return VS_SELECT;
		break;

	case qUIT:
		return QUIT;
		break;

	default:
		return NULL_ID;
	}
}

void quit()
{
	gotoXY( CONSOLE_WIDTH_NUM /2 - 10, CONSOLE_HEIGHT_NUM /2 - 4 );
	puts("Thank You For Playing!!");

	gotoXY( 0 , CONSOLE_HEIGHT_NUM -1 ); //커서 위치 조정
}
int onQuit(int input)
{
	return 0;//main()에서 아무키나 누르면 종료되게 하라.
}

//방향키를 이용한 메뉴의 변경. 문장들의 색변화, 값변화 모두 처리한다.
int menuFocusChangeByArrow(int values[][VALUE_NUM], int lineNumMax, int postX, int postY)																						
{
	int nowLine = 0;
	
	printMenuLine( RESERVE, values[nowLine], postX, postY );	

	while(1){
		int temp = gonuInput(1);///////////////		입력

		if(temp == ENTER){		//엔터로 선택한다.
			printMenuLine( SELECTED, values[nowLine], postX, postY  );	
			Sleep( SELECT_WAIT_TIME );
			printMenuLine( DEFAULT, values[nowLine], postX, postY  );	
			
			return values[nowLine][ RETURN ];
		}
		else if(temp == UP) {
			printMenuLine( DEFAULT, values[nowLine], postX, postY );
			nowLine = (nowLine + lineNumMax - 1) % lineNumMax;
			printMenuLine( RESERVE, values[nowLine], postX, postY );	
		}
		else if(temp == DOWN){
			printMenuLine( DEFAULT, values[nowLine], postX, postY );
			nowLine = (nowLine + 1) % lineNumMax;
			printMenuLine( RESERVE, values[nowLine], postX, postY );		
		}
		else{

			printMenuLine( DEFAULT, values[nowLine], postX, postY  );
			return temp;
		}
		
	}

}

//방향키를 이용한 메뉴선택에서의 문장 색 변화 함수
void printMenuLine( int lineState, int nowLine[], int postX, int postY )
{
	
	switch(lineState){
		case DEFAULT:
			setColor(WHITE, BLACK);
			break;

		case RESERVE:
			setColor(WHITE, DARK_YELLOW);
			break;

		case SELECTED:
			setColor(BLACK, YELLOW);
			break;

		default:
			printf("menu line out of index error!!");
	}

	gotoXY( nowLine[X], nowLine[Y] );
		 
	puts( (char*)nowLine[TXT] );
	
	setColor(WHITE, BLACK);	//메뉴 출력후 색상 조절
	gotoXY(postX, postY);	//메뉴 출력 후 커서 조절
}

//--------------

//지정한 플레이어의 입력 박스로 돌아갈 때 쓴다.
void gotoInputBox(int player)
{
	setColor(WHITE, BLACK);

	if(player == 1){
		gotoXY(P1_INPUT_BOX_X, P1_INPUT_BOX_Y);
	}else if(player == 2){
		gotoXY(P2_INPUT_BOX_X, P2_INPUT_BOX_Y);
	}else{
		printf("P%d? 이런 플레이어는 없어!", player);
	}
}

//지정한 플레이어의 입력 박스를 지우고 입력 박스의 첫 칸으로 커서를 옮긴다.
void clearInputBox(int player)
{
	int i; //39

	setColor(WHITE, BLACK);

	if(player == 1){
		gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){	putch(' ');	}

		gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y +1 );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){	putch(' ');	}

		gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y );
		return;

	}else if(player == 2){

		gotoXY( P2_INPUT_BOX_X, P2_INPUT_BOX_Y );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){	putch(' ');	}

		gotoXY( P2_INPUT_BOX_X, P2_INPUT_BOX_Y +1 );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){	putch(' ');	}

		gotoXY( P2_INPUT_BOX_X, P2_INPUT_BOX_Y );
		return;

	}else{
		printf("P%d? 이런 플레이어는 없어!", player);
	}
}

// 로그창을 빈 화면으로 만든다.
void clearLogScreen( void )
{
	int i;

	for(i = 0; i < 20; i++){
		logWriter(" ");
	}
}

// 큐에 출력할 문자열의 포인터를 넣는다.
void logWriter( char str[] )
{
	static StrQueue gameLog = {0};
	static StrQueue* logQueue = &gameLog;
	//-------------문자열 길이에 대한 예외처리-----------------
	int len = 0;
	char* check = str;
	while( *check != '\0' ){
		len++;
		check++;
	}
	if( len >= LOG_SCREEN_WIDTH ){
		printf("로그창에 출력할 문자열의 길이(%d)가 너무 깁니다. %d보다 작아야 합니다.", len, LOG_SCREEN_WIDTH);
		//exit(1);
	}
	//-------------------------------------------------------

	if( isFullQ( logQueue ) == 0 ){
		insertQ( logQueue, str );
	}else{
		popQ( logQueue );
		insertQ( logQueue, str );
	}

	printAtLogScreen( logQueue );
}

// 큐에 저장된 로그를 log screen에 출력한다.
void printAtLogScreen( StrQueue* logQueue )
{
	static const int LOG_BOX_Y_ARR[Q_ARR_MAX] = 
	{
		LOG_PRINT_BOX_Y,
		LOG_PRINT_BOX_Y + 1,
		LOG_PRINT_BOX_Y + 2,
		LOG_PRINT_BOX_Y + 3,
		LOG_PRINT_BOX_Y + 4,
		LOG_PRINT_BOX_Y + 5,
		LOG_PRINT_BOX_Y + 6,
		LOG_PRINT_BOX_Y + 7,
		LOG_PRINT_BOX_Y + 8,
		LOG_PRINT_BOX_Y + 9,
		LOG_PRINT_BOX_Y + 10,
		LOG_PRINT_BOX_Y + 11,
		LOG_PRINT_BOX_Y + 12,
		LOG_PRINT_BOX_Y + 13,
		LOG_PRINT_BOX_Y + 14,
	};
	int index;
	int i;					

	setColor( WHITE, BLACK );

	// [front(값이 항상 NULL) + 1] 에서부터 [rear]까지 출력한다.
	i = 0;
	index = ( logQueue->front + 1 ) % Q_ARR_MAX; 
	while( logQueue->queue[index] != NULL ){ 
		// clear
		int j;
		gotoXY( LOG_PRINT_BOX_X, LOG_BOX_Y_ARR[i] );	
		for(j = 0; j < LOG_SCREEN_WIDTH-1; j++){ 
			_putch(' '); 
		}
		// print one line
		gotoXY( LOG_PRINT_BOX_X, LOG_BOX_Y_ARR[i] );
		puts( logQueue->queue[index] );
		
		if( index > Q_ARR_MAX-2 ){// index가 최대 인덱스인 경우
			index = index - Q_ARR_MAX + 1;
		}else{
			index++;
		}
		i++;
	}
}

void playerScreenUpdate(int player)
{
	int i;
	int kills;

	if( player == 1)
	{
		kills = pieceNumOriginP2 - restP2;

		// clear Life
		gotoXY( P1_LIFE_BOX_X, P1_LIFE_BOX_Y ); setColor( BLACK, BLACK );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){ 
			_putch(' '); 
		}
		// update Life
		gotoXY( P1_LIFE_BOX_X, P1_LIFE_BOX_Y ); setColor( RED, BLACK );
		for(i = 1; i <= lifeP1; i++ ){
			printf("♥");

		}

		// clear Kills
		gotoXY( P1_LIFE_BOX_X, P1_LIFE_BOX_Y+1 ); setColor( BLACK, BLACK );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){ 
			_putch(' '); 
		}
		// update Kills
		gotoXY( P1_LIFE_BOX_X, P1_LIFE_BOX_Y+1 ); setColor( BLUE, BLACK );
		for(i = 1; i <= kills; i++ ){
			printf("●");
		}

	}
	else if( player == 2 )
	{
		kills = pieceNumOriginP1 - restP1;

		// clear Life
		gotoXY( P2_LIFE_BOX_X, P2_LIFE_BOX_Y ); setColor( BLACK, BLACK );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){ 
			_putch(' '); 
		}
		// update Life
		gotoXY( P2_LIFE_BOX_X, P2_LIFE_BOX_Y ); setColor( BLUE, BLACK );
		for(i = 1; i <= lifeP2; i++ ){
			printf("♥");
		}

		// clear Kills
		gotoXY( P2_LIFE_BOX_X, P2_LIFE_BOX_Y+1 ); setColor( BLACK, BLACK );
		for(i = 0; i < INPUT_BOX_LENGTH; i++){ 
			_putch(' '); 
		}
		// update Kills
		gotoXY( P2_LIFE_BOX_X, P2_LIFE_BOX_Y+1 ); setColor( RED, BLACK );
		for(i = 1; i <= kills; i++ ){
			printf("●");
		}

	}
	else
	{
		printf("inputRoutine함수: player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}