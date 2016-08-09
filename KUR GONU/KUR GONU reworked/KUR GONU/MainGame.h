/***************************************************
 *
 *본 게임 play에서 사용되는 대부분의 전역변수가 선언 된 헤더파일
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/
#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#ifndef _GRAPH_ADT_H_
# include "GraphADT.h"
#endif

#ifndef _GAME_DATA_H_
# include "GameData.h"
#endif

#ifndef _STACK_H_
# include "Stack.h"
#endif


#define RE_SELECT	-2000	//inputRoutine, inputForMove사이에 쓰이는 상수다.

#define PIECE		"●"		// 1p : RED		2p : BLUE
#define PIECE_2		"★"
#define PIECE_3		"③"
#define PIECE_4		"④"
#define PIECE_5		"⑤"


typedef struct InputReturn {
	Piece*		piece;
	Vertex*		vertex;
} InputReturn;


//일반적인 이동{Piece*, Crossing*} / 턴넘기기{NULL, NULL} / 항복{NULL, 2} or {NULL, 1}
extern struct InputReturn NEXT_TURN;
extern struct InputReturn GG_RETURN_P1;// 1p가 진 경우.
extern struct InputReturn GG_RETURN_P2;// 2p가 진 경우.

void initGame();
	void printMap(struct Graph* graph, char lineCh);
	void initEnterables( struct Crossing* crossingArr[], struct Piece* piecesP1[], struct Piece* piecesP2[] );
	void initPrintPieces( const struct Piece* piecesP1[], const struct Piece* piecesP2[] ); 
		void printPiece(const Piece* piece, int backColor);

void playGame(int who);
	int gameRoutine( int whoFirst );
		int turn( int player );
			InputReturn inputRoutine( int player );
				int inputForSelect(int player);
				int inputForMove(Piece* select);
			void pieceMove( InputReturn input );
	void showWinBox( int winner );

void endGame();
	void clearCrossingArrFromZero( Crossing* crossingArr[] );
	void clearPiecesFromZero( Piece* pieces[] );

//tempEnterables 관련 함수
void writeTempEnterables(Piece* origin, Vertex* prev, int count);	// 1	writeTempEnterables( piece, piece->occupying, 1 );
void sortTempEnterables( IntStack* tempEnterables );				// 2
	void vertexArrBubbleSort( Vertex* arr[], int size, char mode );
void clearTempEnterables( IntStack* tempEnterables );

void printTempEnterables( IntStack* tempEnterables);
void eraseTempEnterables( IntStack* tempEnterables );

// 선택가능한 숫자(id), effect, focus, piece등 화면 효과 관련
void printPiecesId(Piece* pieces[], int pieceNumOrigin);
void erasePiecesId(Piece* pieces[], int pieceNumOrigin);

void selectEffect( Crossing* crossing, int initialize );	
void focusChangeEffect( Crossing* crossing );

int changePieceFocus( int arrowKeyConst, Piece* pieces[], int pieceNumOrigin, int focus);
int changeVertexFocus( int arrowKeyConst, int focus, IntStack* tempEnterables );

void eraseEffect( Crossing* crossing );
void erasePiece( Crossing* crossing );

//free deploy관련
void piecesDeploy( Vertex* setSpots[] );
	void printSetSpots( Vertex* setSpots[] );
	int inputDeployWhere();
	int inputDeployWhat();
	void deployPiece( Vertex* vertex, int pieceId, int player, int range );
		void eraseSetSpots( Crossing* crossingArr[] );

// 유틸리티함수
Piece* getPiece( Piece* pieces[], int id );
Vertex* getEnterableAsVertex( IntStack* tempEnterables, int printedId );
int getVertexIdFromPrintedId( IntStack* tempEnterables, int printedId );
int isCastle(Crossing* crossing);


struct IntStack vertexStack;	// 이동 가능한 교차점을 표시할 때 일시적으로 저장하는 곳.
struct IntStack *tempEnterables;// vertexStack을 가리키기 위한 포인터변수.




#endif