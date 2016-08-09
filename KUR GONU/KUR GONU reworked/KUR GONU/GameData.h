/***************************************************
 *본 게임 play에서 사용되는 구조체들 정의.
 *그리고 게임 데이터와 관련된 변수들.
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/
#ifndef	_GAME_DATA_H_
#define _GAME_DATA_H_

#ifndef _CONSOLE_GRAPHICS_H_
# include "ConsoleGraphics.h"
#endif

#ifndef _INC_STDIO
# include <stdio.h>
#endif

#ifndef _GRAPH_ADT_H_		
# include "GraphADT.h"
#endif

#define MAX_CASTLE_NUM	7
#define MAX_PIECE_NUM	30
#define LIFE			3	//life는 말 수와는 별 관계 없다.	
#define MAX_RANGE		10
//RULL

typedef struct Enterable{
	short p1;	// 0:통과 불가		1:통과 가능
	short p2;
} Enterable;

typedef struct TextColor{
	int txt;
	int back;
} TextColor;

typedef struct Crossing{
	//불변
	struct Point		point;			//좌표
	char				crossingType;	// 성: $ / 말 놓는 곳 1p: * 2p: + / 일반: ,
	int					IDnum;			
	//유동적
	struct Enterable	enterable;		
	struct TextColor	txtColor;
	struct Piece	   *occupier;		//현재 위치한 말을 가리킴
} Crossing;

typedef struct Piece{
	//불변	
	int					pieceId;	
	int					player;			//어느 플레이어의 말인가?
	//유동적
	struct Vertex	   *occupying;		//현재 위치한 곳의 정점 데이터를 가리킴
	struct TextColor	txtColor;	
	int					range;			//공격범위 기본 1
	//옵션 혹은 확장사항.
	short				stackable;		//쌓을 수 있는가?	1:yes	0:no
} Piece;


short loadDataFile( char fileName[] );
int	charToInt(char ch);
int readNumAndMoveFilePtr(char** fptr);

// heap영역 메모리 해제
void clearCrossingArrFromZero( Crossing* crossingArr[] );
void clearPiecesFromZero( Piece* pieces[] );



Graph mapGraph;//현재 게임 맵의 그래프 정보를 저장한다.
Crossing* mapCrossingArr[VERTEX_NUM_MAX];
// mapGraph 생성시 dataArr역할을 한다.
// 교차점의 ID(인덱스)를 통한 접근이 가능하므로 간편하게 사용할 수 있다.

struct Piece* piecesP1[MAX_PIECE_NUM];
struct Piece* piecesP2[MAX_PIECE_NUM];

int pieceNumOriginP1;//원래의 말 수.
int pieceNumOriginP2;

int restP1;//남은 말 수
int restP2;

int lifeP1;
int lifeP2;

Crossing* castlesP1[MAX_CASTLE_NUM];
Crossing* castlesP2[MAX_CASTLE_NUM];


int mode, players; // 게임 모드, VS선택 저장 변수(unused).
#define	SIMPLE			1
#define	FULL			2
#define	FREE_DEPLOY		3
#define CUSTOM1			4
#define CUSTOM2			5
#define HOW_TO_PLAY_MODE	6

#define SIMPLE_MODE_FILE		"simple.gonu"
#define FULL_MODE_FILE			"full.gonu"
#define FREE_DEPLOY_MODE_FILE	"free.gonu"
#define CUSTOM1_MODE_FILE		"custom1.gonu"
#define CUSTOM2_MODE_FILE		"custom2.gonu"
#define HOW_TO_PLAY_MODE_FILE	"how to play.gonu"

#define _MODE_F		-10	// GameData.c 144line에서 'F'인 경우, 말 배치 함수가 활성화된다.


int range1PieceNumMax;
int range2PieceNumMax;
int range3PieceNumMax;
int range4PieceNumMax;
int range5PieceNumMax;
//range가 1인 말 수, range가 2인 말 수. free deploy용이다. 
int maxArrPieceRangeIs[MAX_RANGE];


Vertex* tempSetSpotsP1[MAX_PIECE_NUM];
Vertex* tempSetSpotsP2[MAX_PIECE_NUM];
// 말을 배치시킬 수 있는 정점을 모아두는 배열. free deploy용이다.
// piecesDeploy에서 자동으로 원소들이 NULL로 초기화된다.

//간선을 그릴 때 쓰는 char 저장.
char lineElement;

///////////////// endGame()에서 초기화시키면 안되는 변수!! ////////////////////
int lastGameMode, lastGamePlayers;
///////////////// 이전 게임의 mode와 players. 즉 게임 설정을 저장한다./////////
#endif

