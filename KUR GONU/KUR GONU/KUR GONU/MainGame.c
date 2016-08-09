/***************************************************
 *고누 실제 게임 사용 함수들
 *
 * 게임 play 시에 사용되는 대부분의 함수들.
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/
#include <time.h>
#include "MainGame.h"
#include "ConsoleGraphics.h"
#include "MenuAndUI.h"
#include "GonuInput.h"
#include "Rull.h"


int passedTurn = 0;

struct InputReturn NEXT_TURN	= {NULL, NULL};	
struct InputReturn GG_RETURN_P1	= {NULL, (Vertex*)1};// 1p가 진 경우.
struct InputReturn GG_RETURN_P2	= {NULL, (Vertex*)2};// 2p가 진 경우.

void initGame()//게임 모드에 대한 정보는 전역변수 2가지 mode와 players에서 취급한다.
{			
	if( mode == SIMPLE ){
		loadDataFile( SIMPLE_MODE_FILE );
		
		lifeP1 = LIFE;	//RULL
		lifeP2 = LIFE;	//RULL
	}
	else if( mode == FULL ){
		loadDataFile( FULL_MODE_FILE );
		
		lifeP1 = LIFE;	//RULL
		lifeP2 = LIFE;	//RULL
	}
	else if( mode == FREE_DEPLOY ){
		loadDataFile( FREE_DEPLOY_MODE_FILE );
		
		lifeP1 = LIFE;	//RULL
		lifeP2 = LIFE;	//RULL
	}
	else if( mode == CUSTOM1 ){
		loadDataFile( CUSTOM1_MODE_FILE );
		
		lifeP1 = LIFE;	//RULL
		lifeP2 = LIFE;	//RULL
	}
	else if( mode == CUSTOM2 ){
		loadDataFile( CUSTOM2_MODE_FILE );
		
		lifeP1 = LIFE;	//RULL
		lifeP2 = LIFE;	//RULL
	}
	else if( mode == HOW_TO_PLAY_MODE ){
		loadDataFile( HOW_TO_PLAY_MODE_FILE );
		
		lifeP1 = LIFE;	//RULL
		lifeP2 = LIFE;	//RULL
	}
	else{
		puts(" 아직 지원하지 않는 모드다. mode의 대입이 잘못되었다.");
		exit(1);
	}

	printMap( &mapGraph, lineElement );

	if( mode == _MODE_F ){
		logWriter(" ");
		logWriter("플레이어 1, RED가 먼저 배치합니다.");
		logWriter("플레이어 2, BLUE는 보지 마세요! :)");
		logWriter(" ");
		piecesDeploy( tempSetSpotsP1 );

		logWriter(" ");
		logWriter(" ");
		logWriter(" ");
		logWriter("플레이어 1, RED의 배치가 끝났습니다.");
		logWriter("RED는 BLUE에게 알려주세요. ");
		logWriter(" ");
		logWriter(" ");
		logWriter("아무키나 누르면 BLUE의 배치를 시작합니다.");
		_getch();

		logWriter(" ");
		logWriter("플레이어 2, BLUE가 배치합니다.");
		logWriter("플레이어 1, RED는 보지 마세요! :)");
		logWriter(" ");
		piecesDeploy( tempSetSpotsP2 );
	}

	initPrintPieces( piecesP1, piecesP2 );
	initEnterables( mapCrossingArr, piecesP1, piecesP2 );

	tempEnterables = &vertexStack;
	stackInit( tempEnterables );

	logWriter("초기화가 완료되었습니다.");
}


// 다시하기를 위한 초기화 함수.
void endGame()
{
	int i;

	//heap 메모리에 있는 변수들 해제하기
	clearGraphFromZero( &mapGraph );
	clearCrossingArrFromZero( mapCrossingArr );
	clearPiecesFromZero( piecesP1 );
	clearPiecesFromZero( piecesP2 );

	//전역변수들 0, NULL로.
	pieceNumOriginP1 = pieceNumOriginP2 = 0;
	restP1 = restP2 = 0;
	lifeP1 = lifeP2 = 0;
	
	i = 0;
	while( castlesP1[i] != NULL ){
		castlesP1[i] = NULL;
		i++;
	}
	i = 0;
	while( castlesP2[i] != NULL ){
		castlesP2[i] = NULL;
		i++;
	}

	mode = 0;
	range1PieceNumMax = range2PieceNumMax = range3PieceNumMax = range4PieceNumMax = range5PieceNumMax = 0;

	clearTempEnterables( tempEnterables );
	
	passedTurn = 0;
}

// 1.heap영역의 Crossing들을 해제 2.Crossig*의 배열에 NULL넣기
void clearCrossingArrFromZero( Crossing* crossingArr[] )
{
	int i;

	i = 0;
	while( crossingArr[i] != NULL ){
		free( (void*)crossingArr[i] );
		crossingArr[i] = NULL;
		i++;
	}
}

// 1.heap영역의 Piece들을 해제 2.Piece*의 배열에 NULL넣기
void clearPiecesFromZero( Piece* pieces[] )
{
	int i;

	i = 0;
	while( pieces[i] != NULL ){
		free( (void*)pieces[i] );
		pieces[i] = NULL;
		i++;
	}
}

// 입력 who에 따라 순서를 결정한다.
// 승자에 따라 승리 메시지를 띄운다.
void playGame(int whoFirst)
{
	int temp;
	int winner;

	logWriter("게임이 시작되었습니다.");
	playerScreenUpdate(1);
	playerScreenUpdate(2);

	if(whoFirst){
		winner = gameRoutine( whoFirst );		// 1 => 1p먼저, 2 => 2p먼저
	}else{
		srand(  (unsigned)( time(NULL)+clock() )  );
		temp = rand()%2 + 1;
		winner = gameRoutine( temp );	// who = 0 => random
	}

	showWinBox( winner );
}

void showWinBox( int winner )
{
	Sleep(1000);
	
	setColor(WHITE, WHITE);		printFullSquare(33, 13, 60, 13, ' ');

	if(winner == 1)
	{
		setColor(RED, RED);			printSquare(33, 13, 60, 13, ' ');
	}
	else if(winner == 2)
	{
		setColor(BLUE, BLUE);		printSquare(33, 13, 60, 13, ' ');
	}
	else
	{
		printf("showWinBox함수: player%d는 존재하지 않는 플레이어입니다.", winner);
		//exit(1);
	}

	setColor(BLACK, WHITE);
	gotoXY(54, 16);				printf("플레이어 %d의 승리!", winner);
	gotoXY(44, 19);				printf("당신은 %d턴 만에 이겼습니다! 축하합니다!", passedTurn);
	gotoXY(78, 24);				printf("press any key");

	Sleep(1000);
	setColor(WHITE, BLACK);

	_getch();	// press any key

	system("cls");
	clearLogScreen();
}

// 게임 한 판에 단 한번만 호출되는 함수다.
int gameRoutine( int whoFirst )
{
	int winner = 0;
	int temp;

	if(whoFirst == 1)
	{
		while(1){
			if( temp = turn(1) ){	winner = temp;	break;	}			
			if( temp = turn(2) ){	winner = temp;	break;	}			
		}
	}
	else if(whoFirst == 2)
	{
		while(1){
			if( temp = turn(2) ){	winner = temp;	break;	}			
			if( temp = turn(1) ){	winner = temp;	break;	}			
		}
	}
	else
	{
		printf("gameRoutine함수: player%d는 존재하지 않는 플레이어입니다.", whoFirst);
		//exit(1);
	}

	return winner;
}

//0: 무승부, 1: 1p 승리, 2:2p승리
int turn( int player )
{
	InputReturn input;

	passedTurn++;

	if(player == 1)
	{
		logWriter(" ");
		logWriter("플레이어 1, RED의 턴입니다.");
		printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '#' );// 1p 창
		printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 2p 창
		
		//입력
		input = inputRoutine(1);

		if( input.piece == GG_RETURN_P1.piece  &&  input.vertex == GG_RETURN_P1.vertex ){
			//p1이 gg를 치면
			return 2;

		}else if( input.piece == NEXT_TURN.piece  &&  input.vertex == NEXT_TURN.vertex ){
			//p1이 턴을 넘기면
			lifeP1--;					//RULL	
			playerScreenUpdate(1);
			
			if( isDefeated(1) ){
				return 2;
			}else{
				return 0;
			}

		}

		pieceMove( input );

		if( isDefeated(2) == 1 ){	
			return 1;	
		}else{
			return 0;
		}

	}
	else if(player == 2)
	{
		logWriter(" ");
		logWriter("플레이어 2, BLUE의 턴입니다.");
		printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 1p 창
		printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '#' );// 2p 창
		input = inputRoutine(2);

		if( input.piece == GG_RETURN_P2.piece  &&  input.vertex == GG_RETURN_P2.vertex ){
			//p1이 gg를 치면
			return 1;

		}else if( input.piece == NEXT_TURN.piece  &&  input.vertex == NEXT_TURN.vertex ){
			//p1이 턴을 넘기면
			lifeP2--;					//RULL	
			playerScreenUpdate(2);
			
			if( isDefeated(2) ){
				return 1;
			}else{
				return 0;
			}

		}

		pieceMove( input );

		if( isDefeated(1) == 1 ){	
			return 2;	
		}else{
			return 0;
		}

	}
	else
	{
		printf("trun함수: player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}

// 반환값의 정보 : Piece* ~가 Vertex* ~로 이동한다.
//		일반적인 이동	{Piece*, Vertex*} 
//		턴넘기기			{NULL, NULL} 
//		항복				1p가 항복: {NULL, 1}  2p가 항복: {NULL, 2}
InputReturn inputRoutine( int player )
{
	int selectId;
	int moveId;
	
	InputReturn returnValue;

	if(player == 1)
	{
		while(1){
			logWriter("플레이어 1, RED가 움직일 말을 선택하세요.");
			selectId = inputForSelect(1);

			if( selectId == GG ){
				logWriter(" ");
				logWriter("플레이어 1, RED가 항복하였습니다!! ");
				logWriter(" ");
				logWriter(" ");
				logWriter("           BLUE의 승리입니다!");
				logWriter(" ");
				logWriter(" ");
				return GG_RETURN_P1;
			}
			else if( selectId == NEXT ){
				logWriter("플레이어 1, RED가 턴을 넘겼습니다.");
				return NEXT_TURN;	
			}

			logWriter("선택한 말을 움직일 장소를 선택하세요.");
			moveId = inputForMove( piecesP1[selectId] );

			if( moveId == GG ){
				logWriter(" ");
				logWriter("플레이어 1, RED가 항복하였습니다!! ");
				logWriter(" ");
				logWriter(" ");
				logWriter("           BLUE의 승리입니다!");
				logWriter(" ");
				logWriter(" ");
				return GG_RETURN_P1;	
			}
			else if( moveId == NEXT ){	
				logWriter("플레이어 1, RED가 턴을 넘겼습니다.");
				return NEXT_TURN;		
			}
			else if( moveId == RE_SELECT ){	
				continue;	
			}
			else{
				logWriter("플레이어 1, RED가 말을 움직였습니다.");
				returnValue.piece = piecesP1[selectId];
				returnValue.vertex = mapGraph.vertices[moveId];
				return returnValue;		
			}
		}

	}
	else if(player == 2)
	{
		while(1){
			logWriter("플레이어 2, BLUE가 움직일 말을 선택하세요.");
			selectId = inputForSelect(2);

			if( selectId == GG ){
				logWriter(" ");
				logWriter("플레이어 2, BLUE가 항복하였습니다!! ");
				logWriter(" ");
				logWriter(" ");
				logWriter("            RED의 승리입니다!");
				logWriter(" ");
				logWriter(" ");
				return GG_RETURN_P2;	
			}
			else if( selectId == NEXT ){
				logWriter("플레이어 2, BLUE가 턴을 넘겼습니다.");
				return NEXT_TURN;	
			}

			logWriter("선택한 말을 움직일 장소를 선택하세요.");
			moveId = inputForMove( piecesP2[selectId] );

			if( moveId == GG ){
				logWriter(" ");
				logWriter("플레이어 2, BLUE가 항복하였습니다!! ");
				logWriter(" ");
				logWriter(" ");
				logWriter("          RED의 승리입니다!");
				logWriter(" ");
				logWriter(" ");
				return GG_RETURN_P2;	
			}
			else if( moveId == NEXT ){
				logWriter("플레이어 2, BLUE가 턴을 넘겼습니다.");
				return NEXT_TURN;	
			}
			else if( moveId == RE_SELECT ){
				continue;	
			}
			else{
				logWriter("플레이어 2, BLUE가 말을 움직였습니다.");
				returnValue.piece = piecesP2[selectId];
				returnValue.vertex = mapGraph.vertices[moveId];
				return returnValue;		
			}
		}

	}
	else
	{
		printf("inputRoutine함수: player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}

// 사용자의 입력과 현재 player에 따라 값을 반환한다.
// 선택된 말의 ID 값이 반환 된다.
// 방향키를 이용한 입력의 경우 엔터를 누르기 전까지 지속된다.
int inputForSelect(int player)
{
	static int focusP1 = -1;	// 방향키에 의한 이동을 위한 변수 focus
	static int focusP2 = -1;
	int input;

	if( player == 1 )
	{
		while(1){
			printPiecesId(piecesP1, pieceNumOriginP1);
			
			clearInputBox( player );
			input = gonuInput(1);

			if( input >= (int)'0'  &&  input <= (int)'9' ){
				
				int selectedId = charToInt( (char)input );
				Piece* piece = getPiece( piecesP1, selectedId );
				
				if( piece != NULL ){
					selectEffect( ((Crossing*)piece->occupying->data) , 1);
					erasePiecesId( piecesP1, pieceNumOriginP1 );
					return selectedId;
				}else{
					continue;
				}

			}
			else if(	input == UP		||	input == DOWN
					||	input == RIGHT	||	input == LEFT	){
						
						int _input; 
					
						//이전의 포커스로 한번 effect출력.
						if(focusP1== -1){
							focusP1= 0;
						}
						focusP1= changePieceFocus( input, piecesP1, pieceNumOriginP1, focusP1 );
						focusChangeEffect( (Crossing*)piecesP1[focusP1]->occupying->data );
						
						while(1){
							
							clearInputBox( player );
							_input = gonuInput(1);
													
							if( _input >= (int)'0'  &&  _input <= (int)'9' ){
				
								int selectedId = charToInt( (char)_input );
								Piece* piece = getPiece( piecesP1, selectedId );
				
								if( piece != NULL ){
									selectEffect( ((Crossing*)piece->occupying->data) , 1);
									erasePiecesId( piecesP1, pieceNumOriginP1 );
									return selectedId;
								}else{
									continue;
								}

							}
							else if(	_input == UP	||	_input == DOWN
									||	_input == RIGHT	||	_input == LEFT	){
						
										//				이거 바꿔라! static을 쓸 수 있게!
										focusP1 = changePieceFocus( _input, piecesP1, pieceNumOriginP1, focusP1 );
										focusChangeEffect( (Crossing*)piecesP1[focusP1]->occupying->data );
										continue;
							}
							else if( _input == ENTER ){
								erasePiecesId( piecesP1, pieceNumOriginP1 );
								selectEffect( (Crossing*)piecesP1[focusP1]->occupying->data , 1);
								return focusP1;
							}
							else if( _input == gG || _input == GG ){
								erasePiecesId( piecesP1, pieceNumOriginP1 );
								return GG;
							}
							else if( _input == nEXT || _input == NEXT ){
								erasePiecesId( piecesP1, pieceNumOriginP1 );
								return NEXT;
							}
							else{
								continue;
							}
						}

			}
			else if( input == ENTER ){
				if( focusP1== -1 ){
					continue;
				}else{
					erasePiecesId( piecesP1, pieceNumOriginP1 );
					selectEffect( (Crossing*)piecesP1[focusP1]->occupying->data , 1);
					return focusP1;
				}
			}
			else if( input == gG || input == GG ){
				erasePiecesId( piecesP1, pieceNumOriginP1 );
				return GG;
			}
			else if( input == nEXT || input == NEXT ){
				erasePiecesId( piecesP1, pieceNumOriginP1 );
				return NEXT;
			}
			else{
				continue;
			}
		}

	}
	else if( player == 2 )
	{
		
		while(1){
			printPiecesId(piecesP2, pieceNumOriginP2);
			clearInputBox( player );

			input = gonuInput(1);

			if( input >= (int)'0'  &&  input <= (int)'9' ){
				
				int selectedId = charToInt( (char)input );
				Piece* piece = getPiece( piecesP2, selectedId );
				
				if( piece != NULL ){
					selectEffect( ((Crossing*)piece->occupying->data), 1);
					erasePiecesId( piecesP2, pieceNumOriginP2 );
					return selectedId;
				}else{
					continue;
				}

			}
			else if(	input == UP		||	input == DOWN
					||	input == RIGHT	||	input == LEFT	){
						
						int _input; 
						//입력 이전의 포커스로 한번 effect출력.
						if(focusP2== -1){
							focusP2= 0;
						}
						focusP2= changePieceFocus( input, piecesP2, pieceNumOriginP2, focusP2 );
						focusChangeEffect( (Crossing*)piecesP2[focusP2]->occupying->data );
						
						while(1){
							
							clearInputBox( player );
							_input = gonuInput(1);
													
							if( _input >= (int)'0'  &&  _input <= (int)'9' ){
				
								int selectedId = charToInt( (char)_input );
								Piece* piece = getPiece( piecesP2, selectedId );
				
								if( piece != NULL ){
									selectEffect( ((Crossing*)piece->occupying->data), 1);
									erasePiecesId( piecesP2, pieceNumOriginP2 );
									return selectedId;
								}else{
									continue;
								}

							}
							else if(	_input == UP	||	_input == DOWN
									||	_input == RIGHT	||	_input == LEFT	){
						
										focusP2= changePieceFocus( _input, piecesP2, pieceNumOriginP2, focusP2 );
										focusChangeEffect( (Crossing*)piecesP2[focusP2]->occupying->data );
										continue;
							}
							else if( _input == ENTER ){
								erasePiecesId( piecesP2, pieceNumOriginP2 );
								selectEffect( (Crossing*)piecesP2[focusP2]->occupying->data, 1);
								return focusP2;
							}
							else if( _input == gG || _input == GG ){
								erasePiecesId( piecesP2, pieceNumOriginP2 );
								return GG;
							}
							else if( _input == nEXT || _input == NEXT ){
								erasePiecesId( piecesP2, pieceNumOriginP2 );
								return NEXT;
							}
							else{
								continue;
							}
						}

			}
			else if( input == ENTER ){
				if( focusP2== -1 ){
					continue;
				}else{
					erasePiecesId( piecesP2, pieceNumOriginP2 );
					selectEffect( (Crossing*)piecesP2[focusP2]->occupying->data, 1);
					return focusP2;
				}
			}
			else if( input == gG || input == GG ){
				erasePiecesId( piecesP2, pieceNumOriginP2 );
				return GG;
			}
			else if( input == nEXT || input == NEXT ){
				erasePiecesId( piecesP2, pieceNumOriginP2 );
				return NEXT;
			}
			else{
				continue;
			}
		}

	}
	else
	{
		printf("player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}


// 사용자의 입력과 현재 player에 따라 값을 반환한다.
// 선택된 정점의 "화면에 표시된 숫자"가 반환된다.( 이것은 vertex->IDnum이 아니다! )
// getEnterablesAsVertex("화면에 표시된 숫자")로 Vertex*에 접근 가능하다.
// 방향키를 이용한 입력의 경우 엔터를 누르기 전까지 지속된다.
int inputForMove(Piece* select)
{
	int player = select->player;
	int printedFocusP1 = -1;	// 방향키에 의한 이동을 위한 변수 focus,
	int printedFocusP2 = -1;	// printedFocus는  화면에 표시된 수와 같다. 
	int input;
	
	if( player == 1 )
	{			
		
		while(1){

			writeTempEnterables( select, select->occupying, 1 );				
			sortTempEnterables( tempEnterables );
			printTempEnterables( tempEnterables );
		
			clearInputBox( player );
			input = gonuInput(1);

			if( input >= (int)'0'  &&  input <= (int)'9' ){
				
				int selectedPrintedId = charToInt( (char)input );
				Vertex* vertex = getEnterableAsVertex( tempEnterables, selectedPrintedId );
								
				if( vertex != NULL ){
					//반환값은 vertex의 IDnum이므로 입력값을 적절히 가공한다.
					int vertexId = getVertexIdFromPrintedId( tempEnterables, selectedPrintedId );
					
					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );
					
					selectEffect( (Crossing*)vertex->data, 1);
					
					return vertexId;

				}else{
					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );
					eraseEffect( (Crossing*)select->occupying->data );
					return RE_SELECT;
				}

			}
			else if(	input == UP		||	input == DOWN
					||	input == RIGHT	||	input == LEFT	){
						
						int moreInput;// printedFocus를 옮길 수 있는 입력
						Crossing* focusedCrossing;

						if( tempEnterables->top == 0 ){
							eraseTempEnterables( tempEnterables );
							clearTempEnterables( tempEnterables );
							eraseEffect( (Crossing*)select->occupying->data );
							return RE_SELECT;
						}
						
						if( printedFocusP1 == -1 ){
							printedFocusP1 = 0;
						}
						//입력 전의 포커스로 한번 effect출력.
						printedFocusP1 = changeVertexFocus( input, printedFocusP1, tempEnterables );
						focusedCrossing =  (Crossing*)( getEnterableAsVertex(tempEnterables, printedFocusP1)->data );
						focusChangeEffect( focusedCrossing );

						while(1){
							
							clearInputBox( player );
							moreInput = gonuInput(1);
													
							if( moreInput >= (int)'0'  &&  moreInput <= (int)'9' ){
				
								int selectedPrintedId = charToInt( (char)moreInput );
								Vertex* vertex = getEnterableAsVertex( tempEnterables, selectedPrintedId );
				
								if( vertex != NULL ){
									//반환값은 vertex의 IDnum이므로 입력값을 적절히 가공한다.
									int vertexId = getVertexIdFromPrintedId( tempEnterables, selectedPrintedId );
					
									eraseTempEnterables( tempEnterables );
									clearTempEnterables( tempEnterables );
					
									selectEffect( (Crossing*)vertex->data, 1);
					
									return vertexId;
								}else{
									eraseTempEnterables( tempEnterables );
									clearTempEnterables( tempEnterables );
									eraseEffect( (Crossing*)select->occupying->data );
									return RE_SELECT;
								}

							}
							else if(	moreInput == UP		||	moreInput == DOWN
									||	moreInput == RIGHT	||	moreInput == LEFT	){
						
										printedFocusP1 = changeVertexFocus( moreInput, printedFocusP1, tempEnterables );
										focusedCrossing =  (Crossing*)( getEnterableAsVertex(tempEnterables, printedFocusP1)->data );
										focusChangeEffect( focusedCrossing );
										continue;
							}
							else if( moreInput == ENTER ){
								//반환값은 vertex의 IDnum이므로 
								Vertex* vertex = getEnterableAsVertex( tempEnterables, printedFocusP1);

								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );

								selectEffect( (Crossing*)vertex->data, 1);

								return vertex->IDnum;
							}
							else if( moreInput == gG || moreInput == GG ){
								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );
								return GG;
							}
							else if( moreInput == nEXT || moreInput == NEXT ){
								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );
								eraseEffect( (Crossing*)select->occupying->data );
								return NEXT;
							}
							else{
								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );
								eraseEffect( (Crossing*)select->occupying->data );
								return RE_SELECT;
							}
						}

			}
			else if( input == ENTER ){
				if( printedFocusP1 == -1 ){
					continue;
				}else{
					//반환값은 vertex의 IDnum이므로 
					Vertex* vertex = getEnterableAsVertex( tempEnterables, printedFocusP1);

					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );

					selectEffect( (Crossing*)vertex->data, 1);

					return vertex->IDnum;
				}
			}
			else if( input == gG || input == GG ){
				eraseTempEnterables( tempEnterables );
				clearTempEnterables( tempEnterables );
				return GG;
			}
			else if( input == nEXT || input == NEXT ){
				eraseTempEnterables( tempEnterables );
				clearTempEnterables( tempEnterables );
				eraseEffect( (Crossing*)select->occupying->data );
				return NEXT;
			}
			else{
				eraseTempEnterables( tempEnterables );
				clearTempEnterables( tempEnterables );
				eraseEffect( (Crossing*)select->occupying->data );
				return RE_SELECT;
			}
		}

	}
	else if( player == 2 )
	{
		while(1){
		
			writeTempEnterables( select, select->occupying, 1 );				
			sortTempEnterables( tempEnterables );
			printTempEnterables( tempEnterables );

			clearInputBox( player );
			input = gonuInput(1);

			if( input >= (int)'0'  &&  input <= (int)'9' ){
				
				int selectedPrintedId = charToInt( (char)input );
				Vertex* vertex = getEnterableAsVertex( tempEnterables, selectedPrintedId );
								
				if( vertex != NULL ){
					//반환값은 vertex의 IDnum이므로 입력값을 적절히 가공한다.
					int vertexId = getVertexIdFromPrintedId( tempEnterables, selectedPrintedId );
					
					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );
					
					selectEffect( (Crossing*)vertex->data, 1);
					
					return vertexId;

				}else{
					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );
					eraseEffect( (Crossing*)select->occupying->data );
					return RE_SELECT;
				}

			}
			else if(	input == UP		||	input == DOWN
					||	input == RIGHT	||	input == LEFT	){
					
						int moreInput;// printedFocus를 옮길 수 있는 입력
						Crossing* focusedCrossing;

						if( tempEnterables->top == 0 ){
							eraseTempEnterables( tempEnterables );
							clearTempEnterables( tempEnterables );
							eraseEffect( (Crossing*)select->occupying->data );
							return RE_SELECT;
						}
						
						if( printedFocusP2 == -1 ){
							printedFocusP2 = 0;
						}
						//입력 전의 포커스로 한번 effect출력.
						printedFocusP2 = changeVertexFocus( input, printedFocusP2, tempEnterables );
						focusedCrossing =  (Crossing*)( getEnterableAsVertex(tempEnterables, printedFocusP2)->data );
						focusChangeEffect( focusedCrossing );

						while(1){
							
							clearInputBox( player );
							moreInput = gonuInput(1);
													
							if( moreInput >= (int)'0'  &&  moreInput <= (int)'9' ){
				
								int selectedPrintedId = charToInt( (char)moreInput );
								Vertex* vertex = getEnterableAsVertex( tempEnterables, selectedPrintedId );
				
								if( vertex != NULL ){
									//반환값은 vertex의 IDnum이므로 입력값을 적절히 가공한다.
									int vertexId = getVertexIdFromPrintedId( tempEnterables, selectedPrintedId );
					
									eraseTempEnterables( tempEnterables );
									clearTempEnterables( tempEnterables );
					
									selectEffect( (Crossing*)vertex->data, 1);
					
									return vertexId;
								}else{
									eraseTempEnterables( tempEnterables );
									clearTempEnterables( tempEnterables );
									eraseEffect( (Crossing*)select->occupying->data );
									return RE_SELECT;
								}

							}
							else if(	moreInput == UP		||	moreInput == DOWN
									||	moreInput == RIGHT	||	moreInput == LEFT	){
						
										printedFocusP2 = changeVertexFocus( moreInput, printedFocusP2, tempEnterables );
										focusedCrossing =  (Crossing*)( getEnterableAsVertex(tempEnterables, printedFocusP2)->data );
										focusChangeEffect( focusedCrossing );
										continue;
							}
							else if( moreInput == ENTER ){
								//반환값은 vertex의 IDnum이므로 
								Vertex* vertex = getEnterableAsVertex( tempEnterables, printedFocusP2);

								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );

								selectEffect( (Crossing*)vertex->data, 1);

								return vertex->IDnum;
							}
							else if( moreInput == gG || moreInput == GG ){
								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );
								return GG;
							}
							else if( moreInput == nEXT || moreInput == NEXT ){
								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );
								eraseEffect( (Crossing*)select->occupying->data );
								return NEXT;
							}
							else{
								eraseTempEnterables( tempEnterables );
								clearTempEnterables( tempEnterables );
								eraseEffect( (Crossing*)select->occupying->data );
								return RE_SELECT;
							}
						}

			}
			else if( input == ENTER ){
				if( printedFocusP2 == -1 ){
					continue;
				}else{
					//반환값은 vertex의 IDnum이므로 
					Vertex* vertex = getEnterableAsVertex( tempEnterables, printedFocusP2);

					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );

					selectEffect( (Crossing*)vertex->data, 1);

					return vertex->IDnum;
				}
			}
			else if( input == gG || input == GG ){
				eraseTempEnterables( tempEnterables );
				clearTempEnterables( tempEnterables );
				return GG;
			}
			else if( input == nEXT || input == NEXT ){
				eraseTempEnterables( tempEnterables );
				clearTempEnterables( tempEnterables );
				eraseEffect( (Crossing*)select->occupying->data );
				return NEXT;
			}
			else{
				eraseTempEnterables( tempEnterables );
				clearTempEnterables( tempEnterables );
				eraseEffect( (Crossing*)select->occupying->data );
				return RE_SELECT;
			}
		}

	}
	else
	{
		printf("player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}

//입력한 그래프에 따라 맵을 그린다.
void printMap(Graph* graph, char lineCh)
{
	int id;
	int numV = graph->numV;

	//선 그리기
	for(id = 0; id < numV; id++){
		Crossing* crossing = (Crossing*)graph->vertices[id]->data;//현재 기준되는 정점
		Vertex* traveler = graph->vertices[id]->link;

		while(traveler != NULL){
			Crossing* travelCrossing = (Crossing*)(traveler->data);//

			drawLine( &crossing->point, &travelCrossing->point, lineCh );
			traveler = traveler->link;
		} 
	}
	//점 그리기
	for(id = 0; id < numV; id++){
		Crossing* crossing = (Crossing*)graph->vertices[id]->data;

		setColor(crossing->txtColor.txt, crossing->txtColor.back);
		printPoint( &crossing->point, crossing->crossingType);
		setColor(WHITE, BLACK);
	}
}

// 저장된 말 정보를 이용하여 모든 말을 그린다(초기화 함수)
void initPrintPieces(const struct Piece* piecesP1[], const struct Piece* piecesP2[])
{
	int id;

	id = 0;
	while( piecesP1[id] != NULL ){
		printPiece( piecesP1[id], BLACK );
		id++;
	}

	id = 0;
	while( piecesP2[id] != NULL ){
		printPiece( piecesP2[id], BLACK );
		id++;
	}
}

// 말 1개를 출력하는 함수
void printPiece(const Piece* piece, int backColor)
{
	gotoXY( ((Crossing*)piece->occupying->data)->point.x - 1,	//x
			((Crossing*)piece->occupying->data)->point.y	 );	//y
	
	if(piece->player == 1){
		setColor(RED, backColor);//색
	}
	else if(piece->player == 2){
		setColor(BLUE, backColor);//색
	}
	else{
		printf("%d 플레이어가 존재하지 않습니다.", piece->player);
		//exit(1);
	}

	switch( piece->range ){
			case 1:	puts( PIECE );		break;
			case 2:	puts( PIECE_2 );	break;
			case 3:	puts( PIECE_3 );	break;
			case 4:	puts( PIECE_4 );	break;
			case 5:	puts( PIECE_5 );	break;
		}
}

// mapGraph에서 dataFileLoad()시에 결정되지 않은 것들 결정하기
// piecee들이 있기 전에는 결정이 불가능한 변동가능한 변수들을 초기화한다.
void initEnterables( Crossing* crossingArr[], Piece* piecesP1[], Piece* piecesP2[] )
{
	int id;

	// 1p가 있는 칸에 1p는 갈 수 없음.
	// occupier 설정
	id = 0;
	while( piecesP1[id] != NULL ){
		Crossing* crossing = (Crossing*)piecesP1[id]->occupying->data;
		
		crossing->occupier = piecesP1[id];
		crossing->enterable.p1 = 0;
		crossing->enterable.p2 = 1;

		id++;
	}

	// 2p가 있는 칸에 2p는 갈 수 없음.
	// occupier 설정
	id = 0;
	while( piecesP2[id] != NULL ){
		Crossing* crossing = (Crossing*)piecesP2[id]->occupying->data;
		
		crossing->occupier = piecesP2[id];
		crossing->enterable.p1 = 1;
		crossing->enterable.p2 = 0;

		id++;
	}

}

//살아있는 말들 기준(-1, -1)에 말의 ID를 출력한다.
void printPiecesId(Piece* pieces[], int pieceNumOrigin)
{
	int i; 
	Point piecePos;

	setColor(WHITE, BLACK);

	for(i = 0; i < pieceNumOrigin; i++){
		if( pieces[i] != NULL){
			piecePos = ( (Crossing*)pieces[i]->occupying->data )->point;
			gotoXY(piecePos.x -1, piecePos.y -1); printf("%d", pieces[i]->pieceId );
		}
	}

}

// printPiecesId 에서 출력했던 ID들을 모두 지운다. 
void erasePiecesId(Piece* pieces[], int pieceNumOrigin)
{
	int i;
	Point piecePos;

	setColor(WHITE, BLACK);

	for(i = 0; i < pieceNumOrigin; i++){
		if( pieces[i] != NULL){
			piecePos = ( (Crossing*)pieces[i]->occupying->data )->point;
			gotoXY(piecePos.x -1 , piecePos.y -1); puts( " " );
		}	//어차피 말 수는 10개 이하다.... 10개를 넘으면 고쳐야한다.
	}
}

// 말 origin이 이동할 수 있는 정점들을 tempEnterables에 넣어주는 재귀함수.
// 사용예시 : writeTempEnterables( piece, piece->occupying, 1 ); 무조건 이렇게 써야함. 바뀌는건 piece뿐.
//						todo tempEnterables를 이용해 나중에 숫자를 입력하여 이동하는 함수... 10개 이상의 정점을 표시하면 방향키로만 선택가능.
void writeTempEnterables(Piece* origin, Vertex* prev, int count)
{
	Vertex* traveler = prev->link;
	int range= origin->range;
	int player = origin->player;

	if( player == 1 )
	{
		if( count == range ){
			while(traveler != NULL){
				Crossing* nowCrossing = (Crossing*)traveler->data;
				//출발점이 아니며 출입가능하다면
				if(  traveler != origin->occupying  &&  nowCrossing->enterable.p1 == 1  ){
					int i, isRepeated = 0;
					int maxIndex = tempEnterables->top;

					for( i = 1; i <= maxIndex; i++ ){
						// 또한 전에 넣은 정점과 중복되지 않는다면
						if(   ((Vertex*)tempEnterables->arr[i])->IDnum  == traveler->IDnum   ){
							isRepeated++;
							break;
						}
					}
					if( isRepeated == 0 ){// 스택에 항목을 넣는다.
						push( tempEnterables, (int)traveler );
					}

				}
				traveler = traveler->link;
			}
		}else if( count < range){

			
			while( traveler != NULL ){
				Crossing* nowCrossing = (Crossing*)traveler->data;

				if(		nowCrossing->enterable.p1 == 1		// 출입 가능하고
					&&	nowCrossing->occupier == NULL		// 놓인 말이 없고
					&&	isCastle(nowCrossing) == 0		){	// 성이 아니라면
						   
					writeTempEnterables( origin, mapGraph.vertices[traveler->IDnum], count+1 );
					// 현재의 traveler와 인접한 맵그래프의 vertex로 가서 조사한다.
				}

				traveler = traveler->link;
			}


		}
	}
	else if( player == 2 )
	{
		if( count == range ){
			while(traveler != NULL){
				Crossing* nowCrossing = (Crossing*)traveler->data;
				//출발점이 아니며 출입가능하다면
				if(  traveler != origin->occupying  &&  nowCrossing->enterable.p2 == 1  ){
					int i, isRepeated = 0;
					int maxIndex = tempEnterables->top;

					for( i = 1; i <= maxIndex; i++ ){
						// 또한 전에 넣은 정점과 중복되지 않는다면
						if(   ((Vertex*)tempEnterables->arr[i])->IDnum  == traveler->IDnum   ){
							isRepeated++;
							break;
						}
					}
					if( isRepeated == 0 ){// 스택에 항목을 넣는다.
						push( tempEnterables, (int)traveler );
					}

				}
				traveler = traveler->link;
			}

		}else if( count < range){

			while( traveler != NULL ){
				Crossing* nowCrossing = (Crossing*)traveler->data;

				if(		nowCrossing->enterable.p1 == 1		// 출입 가능하고
					&&	nowCrossing->occupier == NULL		// 놓인 말이 없고
					&&	isCastle(nowCrossing) == 0		){	// 성이 아니라면
						   
					writeTempEnterables( origin, mapGraph.vertices[traveler->IDnum], count+1 );
					// 현재의 traveler와 인접한 맵그래프의 vertex로 가서 조사한다.
				}

				traveler = traveler->link;
			}

		}else{

			puts("카운트가 레인지보다 큰 경우다. writeEnterables()에서 인수 대입이 잘못되었을 가능성이 크다.");
			//exit(1);
		
		}

	}
	else
	{
		puts("그런 플레이어는 없어. .gonu파일 문제 가능성이 크므로 파일을 수정하시오.");
		exit(1);
	}
}

// sortTempEnterables를 1.y의 오름차순 2.같은 y를 가진 녀석들은 x의 오름차순으로 정렬.
// 1)외관이 아름다워진다 2)*키보드를 이용한 선택 알고리즘이 간단해진다.
void sortTempEnterables( IntStack* tempEnterables )
{
	Vertex** vertexArr = (Vertex**)( &tempEnterables->arr[1] );	// stack의 배열은 [1]부터 자료가 저장되어있다.
	int size = tempEnterables->top; // 그래서 top은 실질적으로 저장된 자료의 수와 같다.
	
	int indexArr[STACK_MAX] = {0};
	int key, index, prevY = -1;
	int i;

	// y에 대해 오름차순으로 버블정렬
	vertexArrBubbleSort( vertexArr, size, 'y' );

	// y가 같은 정점끼리 묶은 뒤 x에 대해 오름차순으로 버블정렬
	prevY = -1;
	key = 0;
	for( index = 0; index < size; index++ ){
		Crossing* nowCrossing = (Crossing*)vertexArr[index]->data;
		if( prevY != nowCrossing->point.y ){
			indexArr[key] = index;
			key++;
			prevY = nowCrossing->point.y ;
		}
	}
	indexArr[key] = index; // 마지막 인덱스 추가
	
	i = 0;
	while( indexArr[i+1] != 0 ){
		int nowIndex	= indexArr[i];
		int nextIndex	= indexArr[i+1];
		
		vertexArrBubbleSort( &vertexArr[nowIndex], nextIndex-nowIndex, 'x' );

		i++;
	}

}

//vertex*의 배열을 넣으면 오름차순으로 정렬해주는 함수.
// mode가 'y'는 y에 따라 오름차순, 'x'는 x에 따라 오름차순
void vertexArrBubbleSort( Vertex* arr[], int size, char mode )
{
	int i;
	int isSorted = 1;
	Vertex* temp;
	
	Crossing* nowCrossing;
	Crossing* nextCrossing;

	if( mode == 'x' || mode == 'X'){

		while( isSorted != 0 ){
			isSorted = 0;

			for( i = 0; i < size -1; i++ ){//size == 1이면 그냥 아무 일 없이 return한다.
				nowCrossing		= (Crossing*)arr[i]->data;
				nextCrossing	= (Crossing*)arr[i+1]->data;

				if( nowCrossing->point.x == nextCrossing->point.x ){
					continue;
				}
				else if( nowCrossing->point.x > nextCrossing->point.x ){
					temp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = temp;

					isSorted = 1;
				}

			}
		}
		return;

	}else if( mode == 'y' || mode == 'Y'){

		while( isSorted != 0 ){
			isSorted = 0;

			for( i = 0; i < size -1; i++ ){
				nowCrossing		= (Crossing*)arr[i]->data;
				nextCrossing	= (Crossing*)arr[i+1]->data;

				if( nowCrossing->point.y == nextCrossing->point.y ){
					continue;
				}
				else if( nowCrossing->point.y > nextCrossing->point.y ){
					temp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = temp;

					isSorted = 1;
				}

			}
		}
		return;

	}else{

		puts("2차원 평면만 표현할 수 있습니다. vertexArrBubbleSort함수의 mode인수대입이 잘못되었습니다.");
		//exit(1);

	}
}

// tempEnterables에 들어있는 교차점들 각각의 위치에 저장된 순서대로 숫자(0~9)를 출력한다.
// 9이상의 수가 필요하다면 '#'으로 출력한다.
void printTempEnterables( IntStack* tempEnterables )
{
	int i; // index가 아닌, index+1값이다. stack이라서 그렇다.
	int len = tempEnterables->top;

	if( len > 10 ){	// 2자리수가 생긴다. 
		for( i = 1; i <= len; i++ ) { // i는 index + 1 이다!
			Vertex* vertex = (Vertex*)tempEnterables->arr[i];
			Crossing* crossing = (Crossing*)vertex->data;

			setColor(GREEN,BLACK);	gotoXY( crossing->point.x -1, crossing->point.y -1 );
			putch( '#' );
										//printf( "%d", i-1 );
		}

		return;
	}else{
		for( i = 1; i <= len; i++ ) { // i는 index + 1 이다!
			Vertex* vertex = (Vertex*)tempEnterables->arr[i];
			Crossing* crossing = (Crossing*)vertex->data;

			setColor(GREEN,BLACK);	gotoXY( crossing->point.x -1, crossing->point.y -1 );
			printf( "%d", i-1 );
		}
	}
}

// printTempEnterables로 출력했던 숫자나 #들을 지운다.
void eraseTempEnterables( IntStack* tempEnterables )
{
	int i; // index가 아닌, index+1값이다. stack이라서 그렇다.
	int len = tempEnterables->top;
 
	for( i = 1; i <= len; i++ ) { // i는 index + 1 이다!
		Vertex* vertex = (Vertex*)tempEnterables->arr[i];
		Crossing* crossing = (Crossing*)vertex->data;

		setColor(WHITE,BLACK);	gotoXY( crossing->point.x -1, crossing->point.y -1 );
		putch( ' ' );
	}
}

void clearTempEnterables( IntStack* tempEnterables )
{
	while( pop(tempEnterables) != 0 );
	stackInit( tempEnterables );
}

Piece* getPiece( Piece* pieces[], int id )
{
	if( pieces[id] != NULL ){
		return pieces[id];
	}else{
		return NULL;
	}
}

// tempEnterables에서 현재 화면에 표시된 index로 Vertex*를 얻어내는 함수
Vertex* getEnterableAsVertex( IntStack* tempEnterables, int printedId )
{
	int index = printedId + 1;

	if( tempEnterables->arr[index] != 0 ){
		return (Vertex*)tempEnterables->arr[index];
	}else{
		return 0;
	}
	
}

// 화면에 출력된 ID가 가리키는 Vertex의 vertex->IDnum을 반환한다.
int getVertexIdFromPrintedId( IntStack* tempEnterables, int printedId )
{
	Vertex* vertex = getEnterableAsVertex( tempEnterables, printedId );
	return vertex->IDnum;
}


//선택한 crossing의 배경색을 노랑색으로 바꾼다.
// mode가 1이면 이전의 노랑색 crossing은 초기화시킨다.
// mode가 0이면 초기화시키지 않는다.
void selectEffect( Crossing* crossing, int initialize )
{
	static Crossing* prev = NULL;

	//이전 교차점 배경 까맣게.(초기화)
	if( initialize == 1  &&  prev != NULL ){
		if( prev->occupier == NULL ){
			gotoPoint( &prev->point ); setColor( WHITE, BLACK );
			_putch( prev->crossingType );
		}else{
			printPiece( prev->occupier, BLACK );
		}
	}
	//현재 교참점 배경 노랗게
	if( crossing->occupier == NULL ){
		gotoPoint( &crossing->point ); setColor( WHITE, YELLOW );
		_putch( crossing->crossingType );
		prev = crossing;
		return;
	}else{
		printPiece( crossing->occupier, YELLOW );
		prev = crossing;
		return;
	}
}

// 키보드로 선택할 때의 focus가 맞춰진 곳 배경을 DARK_GREEN으로 바꾼다.
// 이전 focus의 색은 초기화시킨다.
void focusChangeEffect( Crossing* crossing )
{
	static Crossing* prev = NULL;

	//이전 교차점 배경 까맣게.(초기화)
	if( prev != NULL ){
		if( prev->occupier == NULL ){
			gotoPoint( &prev->point ); setColor( WHITE, BLACK );
			_putch( prev->crossingType );
		}else{
			printPiece( prev->occupier, BLACK );
		}
	}
	//현재 교참점 배경 DARK_GREEN
	if( crossing->occupier == NULL ){
		gotoPoint( &crossing->point ); setColor( WHITE, DARK_GRAY);
		_putch( crossing->crossingType );
		prev = crossing;
		return;
	}else{
		printPiece( crossing->occupier, DARK_GRAY );
		prev = crossing;
		return;
	}
}

void eraseEffect( Crossing* crossing )
{
	if( crossing != NULL ){
		if( crossing->occupier == NULL ){
			gotoPoint( &crossing->point ); setColor( WHITE, BLACK );
			_putch( crossing->crossingType );
			return;
		}else{
			printPiece( crossing->occupier, BLACK );
			return;
		}
	}
}

void erasePiece( Crossing* crossing )
{
	gotoPoint( &crossing->point ); setColor( WHITE, BLACK );
	_putch( crossing->crossingType );
	return;
}

// index와 key보드 값을 넣으면 pieces배열에 따라 증가하거나 감소한 index가 반환된다.
int changePieceFocus( int arrowKeyConst, Piece* pieces[], int pieceNumOrigin, int focus)
{
	if( focus < 0 ){
		printf( "fatal error. changerVertexFocus의 focus인수( == %d )대입이 잘못되었습니다.", focus);
		//exit(1);
	}

	switch( arrowKeyConst ){
		case UP:
		case RIGHT:

			do{
				if( focus == pieceNumOrigin - 1 ){
					focus = 0;
				}else{
					focus++;
				}					
			}while( pieces[focus] == NULL );

			break;

		case DOWN:
		case LEFT:

			do{
				if( focus == 0 ){
					focus = pieceNumOrigin - 1;
				}else{
					focus--;
				}					
			}while( pieces[focus] == NULL );

			break;

		default:
			puts("changePieceFocus함수 호출이 잘못되었다");
			//exit(1);
			break;
	}

	return focus;
	
}

// index와 key보드 값을 넣으면 tempEnterables에 따라 증가하거나 감소한 focus(배열의index)가 반환된다.
// RIGHT : x증가		LEFT : x 감소 (index ++ or -- )
// UP	 : y증가		DOWN : y 감소 (index = y가 바뀌는 index)
int changeVertexFocus( int arrowKeyConst, int focus, IntStack* tempEnterables )
{
	Vertex** vertexArr = (Vertex**)( &tempEnterables->arr[1] );	
	int maxIndex = tempEnterables->top - 1;// 새 배열 vertexArr의 최대 인덱스이다.
	Crossing* prevCrossing = NULL;
	Crossing* nowCrossing = NULL;

	if( focus < 0 ){
		printf( "fatal error. changerVertexFocus의 focus인수( == %d )대입이 잘못되었습니다.", focus);
		//exit(1);
	}

	switch( arrowKeyConst ){

		case RIGHT:
			if( focus == maxIndex ){
				focus = 0;
			}else{
				focus++;
			}
			break;
		
		case LEFT:
			if( focus == 0 ){
				focus = maxIndex;
			}else{
				focus--;
			}
			break;
			
		case UP:
			do{
				if( focus == 0 ){
					focus = maxIndex;
					break;
				}else{
					prevCrossing = (Crossing*)vertexArr[focus]->data;
					nowCrossing = (Crossing*)vertexArr[focus-1]->data;
					focus--;
				}
			}while(prevCrossing->point.y == nowCrossing->point.y);
				
			break;

		case DOWN:
			do{
				if( focus == maxIndex ){
					focus = 0;
					break;
				}else{
					prevCrossing = (Crossing*)vertexArr[focus]->data;
					nowCrossing = (Crossing*)vertexArr[focus+1]->data;
					focus++;
				}
			}while(prevCrossing->point.y == nowCrossing->point.y);
				
			break;
			
		default:
			puts("changeVertexFocus함수 호출이 잘못되었다");
			//exit(1);
			break;
	}
	
	return focus;
	
}

// InputReturn에 따라 1)데이터를 바꾸고 2)화면을 재출력한다.
void pieceMove( InputReturn input )
{
	Piece* selected	= input.piece;
	Vertex* moveTo = input.vertex;
	Crossing* starting = (Crossing*)selected->occupying->data;
	Crossing* destination = (Crossing*)moveTo->data;

	if( destination->occupier == NULL ){
		//암것도 안함.
	}else{
		//	움직이는 말의 플레이어와 / 도착지의 말 플레이어가 다르면
		if( selected->player != destination->occupier->player ){
			Piece* killedPiece = destination->occupier;

			if( killedPiece->player == 1 ){
				piecesP1[ killedPiece->pieceId ] = NULL;
			}
			else if( killedPiece->player == 2 ){
				piecesP2[ killedPiece->pieceId ] = NULL;
			}
			else{
				printf("%d 플레이어가 존재하지 않습니다.", killedPiece->player);
				//exit(1);
			}

			killPiece( killedPiece );
				
		}else{//아군을 따는 것은 일단 불가능하다. stack변수가 0이 아닌 모드는 괜찮지만...
			printf("현재 모드에서는 말 쌓기가 불가능합니다. 에러입니다.");
			//exit(1);
		}
	}

	erasePiece( starting ); //출발점 지우기
	//출발점 enterable 변경
	starting->enterable.p1 = 1;
	starting->enterable.p2 = 1;
	//출발점 occupier 변경
	starting->occupier = NULL;

	selected->occupying = moveTo;	//말 위치 갱신

	//도착점 enterable 변경
	if( selected->player == 1 ){	
		destination->enterable.p1 = 0;
		destination->enterable.p2 = 1;
	}
	else if( selected->player == 2 ){
		destination->enterable.p1 = 1;
		destination->enterable.p2 = 0;
	}
	else{
		printf("%d 플레이어가 존재하지 않습니다.", selected->player);
		//exit(1);
	}
	//도착점 occupier 변경
	destination->occupier = selected;

	printPiece( selected, BLACK );
}

//대입한 Crossing이 castle인지 확인한다
//	castle이 아니라면 0 반환
//	1p의 castle이면 1 반환
//	2p의 castle이면 2 반환
int isCastle(Crossing* crossing)
{
	int i;

	i = 0;
	while( castlesP1[i] != NULL ){
		if( crossing == castlesP1[i] ){
			return 1;
		}
		i++;
	}

	i = 0;
	while( castlesP2[i] != NULL ){
		if( crossing == castlesP2[i] ){
			return 2;
		}
		i++;
	}

	return 0;
}


// 사용자의 선택으로 piecesP1, 2를 만든다.
// 낙 장 불 입 이다.
void piecesDeploy( Vertex* setSpots[] )
{
	const int selectedNumMax =	range1PieceNumMax 
								+ range2PieceNumMax
								+ range3PieceNumMax
								+ range4PieceNumMax
								+ range5PieceNumMax;
	int selectedNum = 0;

	int index;
	int what;
	int pieceId = 0;
	
	int range1PieceNum = 0;
	int range2PieceNum = 0;
	int range3PieceNum = 0;
	int range4PieceNum = 0;
	int range5PieceNum = 0;


	printSetSpots( setSpots );

	while(1){

		index = inputDeployWhere();
		
		if(		index <= MAX_PIECE_NUM
			&&  setSpots[index] != NULL ){
		
			Crossing* crossing = (Crossing*)setSpots[index]->data;
			selectEffect(crossing, 0);

			if( crossing->crossingType == '*' ){

				gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( RED, WHITE );
				printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																range2PieceNumMax - range2PieceNum,
																range3PieceNumMax - range3PieceNum,
																range4PieceNumMax - range4PieceNum,
																range5PieceNumMax - range5PieceNum );

				while(1){
					what = inputDeployWhat();
					
					if( what == 1  &&  range1PieceNum < range1PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 1, what );
						printPiece( piecesP1[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range1PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( RED, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 2  &&  range2PieceNum < range2PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 1, what );
						printPiece( piecesP1[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range2PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( RED, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 3  &&  range3PieceNum < range3PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 1, what );
						printPiece( piecesP1[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range3PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( RED, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 4  &&  range4PieceNum < range4PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 1, what );
						printPiece( piecesP1[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range4PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( RED, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 5  &&  range5PieceNum < range5PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 1, what );
						printPiece( piecesP1[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range5PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( RED, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else{
						continue;
					}

				}
			}
			else if( crossing->crossingType == '+' ){
				
				gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( BLUE, WHITE );
				printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																range2PieceNumMax - range2PieceNum,
																range3PieceNumMax - range3PieceNum,
																range4PieceNumMax - range4PieceNum,
																range5PieceNumMax - range5PieceNum );
				while(1){
					what = inputDeployWhat();
					
					if( what == 1  &&  range1PieceNum < range1PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 2, what );
						printPiece( piecesP2[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range1PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( BLUE, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 2  &&  range2PieceNum < range2PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 2, what );
						printPiece( piecesP2[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range2PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( BLUE, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 3  &&  range3PieceNum < range3PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 2, what );
						printPiece( piecesP2[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range3PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( BLUE, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 4  &&  range4PieceNum < range4PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 2, what );
						printPiece( piecesP2[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range4PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( BLUE, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else if( what == 5  &&  range5PieceNum < range5PieceNumMax ){
						deployPiece( setSpots[index], pieceId, 2, what );
						printPiece( piecesP2[pieceId], BLACK );

						setSpots[index] = NULL;

						pieceId++;
						range5PieceNum++;

						gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 ); setColor( BLUE, WHITE );
						printf( "남은 말 수 ●:%d ★:%d ③:%d ④:%d ⑤:%d ", range1PieceNumMax - range1PieceNum, 
																		range2PieceNumMax - range2PieceNum,
																		range3PieceNumMax - range3PieceNum,
																		range4PieceNumMax - range4PieceNum,
																		range5PieceNumMax - range5PieceNum );
						break;
					}
					else{
						continue;
					}

				}
			}
			else{
				printf("setSpots에 올바르지 못한 Crossing이 들어갔거나 그냥 버그다");
				//exit(1);
			}

		}
		
		// setSpots속의 모든 교차점들이 선택되었다면
		if(		range1PieceNum == range1PieceNumMax  
			&&  range2PieceNum == range2PieceNumMax
			&&  range3PieceNum == range3PieceNumMax
			&&  range4PieceNum == range4PieceNumMax
			&&  range5PieceNum == range5PieceNumMax){  

				Sleep(1300);
				gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 );						setColor( WHITE, BLACK );	printf( "                                    " );
				gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y+2 );		setColor( WHITE, BLACK );	printf( "                                    " );
				eraseSetSpots( mapCrossingArr );
				return;

		}else{
			continue;
		}

	}
}

// free deploy에서 일시적으로 쓰이는 배열 setSpots에 따른 출력
void printSetSpots( Vertex* setSpots[] )
{
	int i;

	setColor( GREEN,BLACK );

	i = 0;
	while( setSpots[i] != NULL ){
		Crossing* crossing = (Crossing*)setSpots[i]->data;

		gotoXY( crossing->point.x -2, crossing->point.y -1 );
		printf( "%d", i );

		i++;
	}
}


// 말 배치에 사용한 말들과 숫자들을 지운다.
void eraseSetSpots( Crossing* crossingArr[] )
{
	int i;

	i = 0;
	while( crossingArr[i] != NULL ){
		Crossing* crossing = crossingArr[i];

		if( crossing->crossingType == '*'  ||  crossing->crossingType == '+' ){
			gotoXY( crossing->point.x - 2,  crossing->point.y - 1 ); setColor(WHITE, BLACK);
			printf("  ");
			eraseEffect( crossing );
		}

		i++;
	}
}

// Piece를 heap에 동적할당하고 매개변수에 따라 값을 넣는다.
void deployPiece( Vertex* vertex, int pieceId, int player, int range )
{
	Piece* piece = (Piece*)malloc( sizeof(Piece) );
	// 말 관련
	piece->occupying = vertex;
	piece->pieceId = pieceId;
	piece->player = player;
	piece->range = range;
	piece->stackable = 0;
	
	if( player == 1 )
	{
		piece->txtColor.txt = RED;
		piece->txtColor.back = BLACK;
		// 기타 1p 관련
		piecesP1[pieceId] = piece;
		restP1++;
		pieceNumOriginP1++;
	}
	else if( player == 2)
	{
		piece->txtColor.txt = BLUE;
		piece->txtColor.back = BLACK;

		piecesP2[pieceId] = piece;
		restP2++;
		pieceNumOriginP2++;
	}
	else
	{
		printf("deployPiece함수: player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}

int inputDeployWhere()
{
	int input = -1;

	while(1){
		logWriter(" ");
		logWriter("말을 놓을 곳의 수를 입력하고 엔터를 누르시오");
		logWriter("방향키 입력은	불가능합니다.");
		logWriter(" ");

		clearInputBox(1);
		gotoXY( P1_INPUT_BOX_X, P1_INPUT_BOX_Y );
		
		getn( &input );
				
		if( input != -1){
			return input;
		}else{
			continue;
		}

	}
}

int inputDeployWhat()
{
	int input;

	while(1){
		logWriter(" ");
		logWriter("선택한 위치에 둘 말을 선택하세요.");
		logWriter(" 1을 누르면 ●, 2를 누르면 ★을 둡니다.");
		logWriter(" 3을 누르면 ③, 4를 누르면 ④을 둡니다.");
		logWriter(" 5를 누르면 ⑤를 둡니다.");
		logWriter(" ");

		input = gonuInput(0);

		if( input >= (int)'1'  &&  input <= (int)'5' ){
			return charToInt( (char)input );
		}else{
			continue;
		}
	}
}

