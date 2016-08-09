/***************************************************
 *메뉴와 UI를 구현하는 상수들
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/
#ifndef _MENU_AND_UI_H_
#define _MENU_AND_UI_H_

#ifndef	_INC_STDIO
# include <stdio.h>
#endif

#ifndef _WINDOWS_
# include <windows.h>
#endif

#ifndef _GRAPH_ADT_H_		
# include "GraphADT.h"
#endif

#ifndef _CONSOLE_GRAPHICS_
# include "ConsoleGraphics.h"
#endif

#include "StringQueue.h"

	

#define CONSOLE_WIDTH			"130"
#define CONSOLE_HEIGHT			"40"
#define	CONSOLE_WIDTH_NUM		130
#define	CONSOLE_HEIGHT_NUM		40

#define SELECT_WAIT_TIME		400	//밀리초 단위.
#define	VALUE_NUM				4// menuFocusChangeByArrow에 넣는 배열에서 쓰이는 값의 수.

enum sceneNumbers{// 함수원형, 함수선언, 장면 번호 @ , 지역변수 배열
	TITLE	=	0,
	MAIN_MENU,	
	CREDIT,
	OPTION,
	HOW_TO_PLAY,
	MODE_SELECT,//5
	VS_SELECT,
	MODE_EXPLANATION,
	GAME,
	END_GAME_MENU,
	QUIT,//10
		SCENE_NUM_MAX,
};

enum lengths{
	LOG_SCREEN_WIDTH		=	47,
	LOG_SCREEN_HEIGHT		=	16,
	PLAYER_SCREEN_WIDTH		=	LOG_SCREEN_WIDTH,
	PLAYER_SCREEN_HEIGHT	=	7,
	INPUT_BOX_LENGTH		=	PLAYER_SCREEN_WIDTH - 8,
};

enum coordinates{
	LOG_SCREEN_X	=	81,
	LOG_SCREEN_Y	=	1,

	LOG_PRINT_BOX_X	=	LOG_SCREEN_X + 1,
	LOG_PRINT_BOX_Y	=	LOG_SCREEN_Y + 1,
	
	P1_SCREEN_X		=	LOG_SCREEN_X,
	P1_SCREEN_Y		=	LOG_SCREEN_Y + LOG_SCREEN_HEIGHT + 5,
	P2_SCREEN_X		=	LOG_SCREEN_X,
	P2_SCREEN_Y		=	P1_SCREEN_Y + PLAYER_SCREEN_HEIGHT + 2,
	
	P1_INPUT_BOX_X	=	P1_SCREEN_X + 7,
	P1_INPUT_BOX_Y	=	P1_SCREEN_Y + 2,
	P2_INPUT_BOX_X	=	P2_SCREEN_X + 7,
	P2_INPUT_BOX_Y	=	P2_SCREEN_Y + 2,

	P1_LIFE_BOX_X	=	P1_INPUT_BOX_X,
	P1_LIFE_BOX_Y	=	P1_INPUT_BOX_Y + 2,
	P2_LIFE_BOX_X	=	P2_INPUT_BOX_X,
	P2_LIFE_BOX_Y	=	P2_INPUT_BOX_Y + 2,

	MENU_HEAD_X		=	10,
};

enum menuSelectIndexes{
	RETURN,
	TXT,
	X,
	Y,
};

enum menuLineStates{
	DEFAULT,
	RESERVE,
	SELECTED,
};

void printScene(int scene);// 함수원형 @ , 함수선언, 장면 번호, 지역변수 배열
	void title();		//0
	void mainMenu();
	void credit();
	void option();
	void howToPlay();
	void modeExplanation();
	void modeSelect();	//5
	void vsSelect();
	void game();
	void endGameMenu();
	void quit();		//10

int getSceneId(int sceneId, int input);
	int onTitle(int input);
	int onMainMenu(int input);
	int onCredit(int input);
	int onOption(int input);
	int onHowToPlay(int input);
	int onModeSelect(int input);
	int onVsSelect(int input);
	int onModeExplanation(int input);
	int onGame(int input);
	int onEndGameMenu(int input);
	int onQuit(int input);

int useArrowToSelectMenu(int currentScene);
int menuFocusChangeByArrow(int values[][VALUE_NUM], int lineNumMax, int postX, int postY);

void printSquare(int startX, int startY, int width, int height, char ch);
void printMenuLine( int lineState, int nowLine[], int postX, int postY );

void gotoInputBox(int player);
void clearInputBox(int player);

// log창, player창 관련함수
void logWriter( char str[] );
void printAtLogScreen( StrQueue* logQueue );
void playerScreenUpdate(int player);
void clearLogScreen( void );

#endif