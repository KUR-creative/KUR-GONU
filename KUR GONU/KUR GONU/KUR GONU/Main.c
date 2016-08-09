/***************************************************
 *고누 게임의 main 함수가 있는 파일.
 *
 * 게임 메뉴를 만드는 graph를 생성하고 사용함.
 * 본 게임 루틴의 가장 큰 틀 제공.
 * how to play에 대한 코드가 있음
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "MenuAndUI.h"
#include "GonuInput.h"
#include "GameData.h"
#include "MainGame.h"

						#include "gonuDebug.h"

int main(){
	//menu UI FSM를 구현하는데 필요한 방향그래프.
	const Data sceneNumArr[] = 
	{
		TITLE,		//0
		MAIN_MENU,	
		CREDIT,
		OPTION,
		HOW_TO_PLAY,
		MODE_SELECT,//5
		VS_SELECT,
		MODE_EXPLANATION,
		GAME,
		END_GAME_MENU,
		QUIT,		//10
			NULL_DATA,
	};
	const int sceneIdArr[ SCENE_NUM_MAX+1 ][ ADJACENT_NUM_MAX ] =
	{
		{MAIN_MENU,								NULL_ID},// 0 TITLE
		{CREDIT, OPTION, HOW_TO_PLAY, QUIT,		NULL_ID},// MAIN_MENU,	
		{MAIN_MENU,								NULL_ID},// CREDIT,
		{MAIN_MENU,								NULL_ID},// OPTION,
		{MODE_SELECT,							NULL_ID},// HOW_TO_PLAY,
		{MAIN_MENU, VS_SELECT,					NULL_ID},// 5 MODE_SELECT,
		{MODE_SELECT, MODE_EXPLANATION,			NULL_ID},// VS_SELECT,
		{GAME,									NULL_ID},// MODE_EXPLANATION,
		{END_GAME_MENU,							NULL_ID},// GAME,
		{MODE_SELECT, GAME, VS_SELECT, QUIT,	NULL_ID},// END_GAME_MENU,
		{END_GAME_MENU,							NULL_ID},// 10 QUIT,		//end game menu로 돌아갈 수 있는 인터페이스는 없지만 간선이 없는 정점은 허용되지 않기 때문에 설정됨.
		{										NULL_ID},//		NULL_DATA,
	};
	Graph menuFsm = createGraphByIdArr(sceneIdArr, sceneNumArr);
	Vertex* indicator = getVertex(&menuFsm, TITLE);
	
	system("mode con: cols=" CONSOLE_WIDTH "lines=" CONSOLE_HEIGHT );
	
	while(1){
		int input; 
		int tempId;
		int currentScene = indicator->data;
		
		printScene(currentScene);						//장면 출력
		
		while(1){
			//장면에 따른 입력
			if( currentScene == GAME ){
			
			initGame();										
			playGame( 0 );	//본 게임은 이 함수에서 진행되며 모두 이 함수의 서브루틴이다. 
							// 0: 순서는 랜덤	1: 1p먼저	2: 2p먼저
			endGame();	//게임 재시작을 위해 heap메모리 해제, 전역변수 초기화를 한다.
						
			//	input이 상관이 없다. on~이 붙은 함수들을 보면 각 장면에서 input이 어떻게 처리되는지 알 수 있다.

			}else if( currentScene == TITLE  || currentScene == QUIT ){
				
				input = _getch();	//TITLE, QUIT에선 press any key
				
				if( (char)input == ARROW_START ){//기능키에 의한 입력 오류 예외처리
					continue;
					//이렇게 하면 자동으로 한번 더 getch()가 일어난다.
				}

			}else if( currentScene == HOW_TO_PLAY ){
				int skipRate = 0;
				InputReturn tempInput = {NULL, NULL};
				
				mode = HOW_TO_PLAY_MODE;
				initGame();	
					playerScreenUpdate(1);
					playerScreenUpdate(2);
					
					logWriter(" 안녕하세요? how to play에 오신 것을 ");
					logWriter(" 환영합니다!");
					logWriter(" ");
					logWriter(" KUR GONU를 어떻게 플레이하는지 ");
					logWriter(" 간단히 설명해드리고");
					logWriter(" 연습게임을 한 판하겠습니다.");
					logWriter(" ");
					logWriter(" KUR GONU는 혼자서 할 수 없는 게임입니다.");
					logWriter(" 개발자가 인공지능을 만들 줄 모른다는데요?");
					logWriter(" 서버니 네트워크니 하나도 모른데요! ");
					logWriter(" ");
					logWriter(" 그러므로 반드시 같이 게임할 친구 하나와");
					logWriter(" 함께 how to play를 해 보시기 바랍니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					
						while(1){
							int temp;
							
							clearInputBox(1);
							gotoInputBox(1);
							temp = gonuInput(1);

							if( temp == sKIP  ||  temp == SKIP){
								skipRate++;
								break;
							}else if( temp == ENTER ){
								break;
							}else{
								continue;
							}
						}

					if( skipRate != 1 ){ 			
					logWriter(" ");
					logWriter(" 제가 말하고 있는 이곳이 log창입니다. ");
					logWriter(" ");
					logWriter(" 여기서 플레이어가 해야할 일이나 ");
					logWriter(" 이벤트를 표시해줍니다.");
					logWriter(" ");
					logWriter(" 그러므로 언제나 예의주시 해주시기 바랍니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	}
					logWriter(" ");
					logWriter(" 먼저 말을 조작해보겠습니다.");
					logWriter(" ");
					logWriter(" 말의 조작에는 2단계가 있습니다. ");
					logWriter(" ");
					logWriter(" 1단계가 [선택], 2단계가 [이동]입니다.");
					logWriter(" ");
					logWriter(" 먼저 말을 [선택]하는 방법부터 알아보겠습니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	}

					logWriter(" 말을 선택하는 방법은 두가지가 있습니다. ");
					logWriter(" ");
					Sleep(500);
					logWriter(" 1. 말 왼쪽 상단의 숫자와 일치하는");
					logWriter("    키보드의 숫자키를 눌러서 선택합니다.");
					logWriter(" ");
					Sleep(1000);
						printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '#' );// 1p 창
						printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 2p 창
						printPiecesId( piecesP1, pieceNumOriginP1 );
						
						clearInputBox(1);	gotoInputBox(1);
					logWriter(" RED의 턴일 때 빨간말 위에 숫자가 뜹니다.");
					logWriter(" ");

					logWriter(" 숫자 2 키를 눌러보세요");
					while(1){	if( gonuInput(0) == '2' ) break;	}
						selectEffect( mapCrossingArr[4], 1);

					logWriter(" ");
					logWriter(" 2번 말이 선택되었습니다.");
						Sleep(600);
						printPiece( piecesP1[2], BLACK );
						erasePiecesId( piecesP1, pieceNumOriginP1 );
												
					logWriter(" ");
					logWriter(" ");
					logWriter(" 이번엔 두번째 방법을 소개합니다.");
						clearInputBox(1);	gotoInputBox(1);
					Sleep(600);

					logWriter(" ");
					logWriter(" 2. 방향키↑↓→←를 이용해 커서를 옮기고");
					logWriter("    엔터키를 눌러 선택합니다.");
					logWriter(" ");


					logWriter(" 방향키 ←를 누르세요");
					while(1){	if( gonuInput(0) == LEFT ) break;	}
						printPiecesId( piecesP1, pieceNumOriginP1 );
						focusChangeEffect( mapCrossingArr[4]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 ←를 누르세요");
					while(1){	if( gonuInput(0) == LEFT ) break;	}
						focusChangeEffect( mapCrossingArr[2]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 ←를 누르세요");
					while(1){	if( gonuInput(0) == LEFT ) break;	}
						focusChangeEffect( mapCrossingArr[0]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 ←를 누르세요");
					while(1){	if( gonuInput(0) == LEFT ) break;	}
						focusChangeEffect( mapCrossingArr[4]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 →를 누르세요");
					while(1){	if( gonuInput(0) == RIGHT ) break;		}
						focusChangeEffect( mapCrossingArr[0]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 →를 누르세요");
					while(1){	if( gonuInput(0) == RIGHT ) break;		}
						focusChangeEffect( mapCrossingArr[2]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 →를 누르세요");
					while(1){	if( gonuInput(0) == RIGHT ) break;		}
						focusChangeEffect( mapCrossingArr[4]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 방향키 →를 누르세요");
					while(1){	if( gonuInput(0) == RIGHT ) break;		}
						focusChangeEffect( mapCrossingArr[0]);
						clearInputBox(1);	gotoInputBox(1);

					logWriter(" 엔터키를 누르세요");
					while(1){	if( gonuInput(0) == ENTER ) break;	}
						selectEffect( mapCrossingArr[0], 1);

					logWriter(" 0번 말이 선택되었습니다.");
						Sleep(600);
						//printPiece( piecesP1[2], BLACK );
						erasePiecesId( piecesP1, pieceNumOriginP1 );

					logWriter("       --------------------------------------");
					logWriter(" ");
					logWriter(" 이제는 말을 [이동]시킬 차례입니다.");
					logWriter(" ");
					logWriter(" 말은 모양에 따라 이동 가능거리가 다릅니다.");
					logWriter(" ");
					logWriter(" ● 말은 1칸, ★ 말은 2칸을 움직입니다.");
					logWriter(" ③은 3칸, ④는 4칸, ⑤는 5칸 움직입니다.");
					logWriter(" ");
					logWriter(" 말을 이동하는 경우에도  ");
					logWriter(" 두 가지 방법이 있습니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	} 
						
						writeTempEnterables( piecesP1[0], piecesP1[0]->occupying, 1 );
						sortTempEnterables( tempEnterables );
						printTempEnterables( tempEnterables );
						clearInputBox(1);	gotoInputBox(1);
					logWriter(" 1.말이 이동하길 원하는 곳의 수와 ");
					logWriter("   같은 숫자키를 누르면 이동합니다.");
					logWriter(" ");
					logWriter(" 0을 눌러보세요");
					while(1){	if( gonuInput(0) == '0' ) break;	} 
					tempInput.piece = piecesP1[0];
					tempInput.vertex = mapGraph.vertices[3];
					eraseEffect( mapCrossingArr[0] );
					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );
					pieceMove( tempInput );

					logWriter(" 0번 말이 이동하였습니다.");
					logWriter(" ");
					logWriter(" ");
					Sleep(500);

					logWriter(" 말이 이동했기 때문에 BLUE의 턴입니다.");
					logWriter(" ");
					printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 1p 창
					printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '#' );// 2p 창
					printPiecesId( piecesP2, pieceNumOriginP2 );
					Sleep(500);

					
						clearInputBox(2);	gotoInputBox(2);
					logWriter(" 이번에도 0을 눌러 0번 말을 선택합니다.");
					while(1){	if( gonuInput(0) == '0' ) break;	}
					selectEffect( mapCrossingArr[20], 1);
					erasePiecesId( piecesP2, pieceNumOriginP2 );

					writeTempEnterables( piecesP2[0], piecesP2[0]->occupying, 1 );
					sortTempEnterables( tempEnterables );
					printTempEnterables( tempEnterables );
					logWriter(" ");
					logWriter(" 이 말은 ③입니다. 즉 3칸을 갈 수 있습니다.");
					logWriter(" ");
					logWriter("       --------------------------------------");
					logWriter(" ");
					logWriter(" 말이 갈 수 있는 곳이 10개보다 많으므로");
					logWriter(" 숫자키를 이용한 이동은 불가능하며");
					logWriter(" ");
					logWriter(" 2. 반드시 방향키 + 엔터키를 통해");
					logWriter("    이동할 곳을 선택해야합니다.");
					logWriter(" ");
					Sleep(500);

					clearInputBox(2);	gotoInputBox(2);
					logWriter(" 방향키 ↑를 누르세요");
					while(1){	if( gonuInput(0) == UP ) break;		}
						focusChangeEffect( mapCrossingArr[16]);

					clearInputBox(2);	gotoInputBox(2);
					logWriter(" 방향키 ↑를 누르세요");
					while(1){	if( gonuInput(0) == UP ) break;		}
						focusChangeEffect( mapCrossingArr[9]);

					clearInputBox(2);	gotoInputBox(2);
					logWriter(" 방향키 ↑를 누르세요");
					while(1){	if( gonuInput(0) == UP ) break;		}
						focusChangeEffect( mapCrossingArr[3]);

					clearInputBox(2);	gotoInputBox(2);
					logWriter(" 엔터키를 누르세요");
					logWriter(" ");
					logWriter(" ");
					while(1){	if( gonuInput(0) == ENTER ) break;	}
					//자동으로 life와 kills가 갱신된다. 
					tempInput.piece = piecesP2[0];
					tempInput.vertex = mapGraph.vertices[3];
					eraseEffect( mapCrossingArr[20] );
					eraseTempEnterables( tempEnterables );
					clearTempEnterables( tempEnterables );
					pieceMove( tempInput );

					logWriter(" ");
					logWriter(" BLUE의 0번말③이 RED의 1번말●을 땄습니다.");
					logWriter(" 이때 BLUE의 상태 창을 보십시오.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	}

					logWriter(" Life, Kills에 하나씩 추가되었습니다.");
					logWriter(" ");
					Sleep(500);

					printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '#' );// 1p 창
					printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 2p 창
					
					logWriter(" 이제 KUR GONU의 ");
					logWriter(" [ 승리조건 ] 에 대해 말씀드리겠습니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	} 

					logWriter(" KUR GONU에서 이기는 방법은 4가지 입니다.");
					logWriter(" ");
					Sleep(500);
					logWriter(" 1. 적의 성 $ 을 함락한다.");
					logWriter(" 2. 적이 gg 혹은 GG를 입력한다.");
					logWriter(" 3. 적의 모든 말을 딴다.");
					logWriter(" 4. 적이 모든 Life를 소진한다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	} 
					
					logWriter(" ");
					logWriter(" 1.과 4.에 대해 설명하겠습니다.");
					logWriter(" ");
					logWriter(" ");
					logWriter(" 1. 적의 성 $ 을 함락한다.");
					logWriter(" ");
					logWriter(" 성 $ 이란 독특한 교차점입니다.");
					logWriter(" ");
					logWriter(" RED와 BLUE는 각자의 진영의 중심에 ");
					logWriter(" 자신들의 성 $을 가지고 있습니다.");
					logWriter(" ");
					logWriter(" 성은 BLUE와 RED에게 그 무엇보다");
					logWriter(" 중요한 곳입니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	} 

					logWriter(" 적의 성에 자신의 말이 들어갈 수 있습니다만 ");
					logWriter(" ");
					logWriter(" 자신의 성에 자신의 말은 들어갈 수 없습니다.");
					logWriter(" ");
					logWriter(" ");
					logWriter(" KUR GONU의 목표 1.은 적의 성에");
					logWriter(" 자신의 말을 침투시켜 함락하는 것입니다.");
					logWriter(" ");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	} 
					logWriter(" ");
					logWriter(" 자... 이제 조건 4.에 대해 설명해야하는데. ");
					logWriter(" ");
					logWriter(" ");
					logWriter(" 이번에는 next나 NEXT를 입력해보세요.");
						
						while(1){
							int temp;
							
							clearInputBox(1);
							temp = gonuInput(1);

							if( temp == nEXT  ||  temp == NEXT){
								lifeP1--;
								break;
							}
						}

					printSquare( P1_SCREEN_X, P1_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '.' );// 1p 창
					printSquare (P2_SCREEN_X, P2_SCREEN_Y, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT, '#' );// 2p 창
					
					logWriter(" ");
					logWriter(" ");
					logWriter(" next나 NEXT를 입력하면 턴이 넘어갑니다.");
					logWriter(" ");
					logWriter(" 턴넘기기는 KUR GONU에서 매우 중요합니다.");
					logWriter(" 교착상태를 해소시켜주기 때문이죠.");
					logWriter(" ");
					logWriter(" 그래서 턴을 넘기는데는 패널티가 있습니다.");
					logWriter(" ");
					logWriter(" 턴을 넘길 경우 Life가 하나 줄어듭니다.");
					logWriter(" ");
					logWriter(" 그리고 모든 Life를 소진할 경우 패배합니다.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	} 
					logWriter(" ");
					logWriter(" ");

					logWriter(" KUR GONU의 모든 룰에 대해 설명하였습니다.");
					logWriter(" ");
					logWriter(" how to play를 스킵하는 방법은");
					logWriter(" 가장 첫번째로 나오는 press enter key에서");
					logWriter(" skip이나 SKIP을 입력하면 됩니다.");
					logWriter(" ");
					logWriter(" ");
					logWriter(" 이제 연습게임을 하신 다음");
					logWriter(" 친구와 함께 본 게임을 즐기십시오.");
					logWriter(" ");
					logWriter("       ------- press enter key --------");
					logWriter(" ");	
					logWriter(" ");
						while(1){	if( gonuInput(0) == ENTER ) break;	}
										

				playGame( 1 );

					}else{	
						system("cls");
						clearLogScreen();
					}
								
				endGame();
				
				input = sKIP;
				
			}else{
				input = gonuInput(1);						//입력
				
				if(	input == UP		||
					input == DOWN	||
					input == RIGHT	||
					input == LEFT)	{

					input = useArrowToSelectMenu(currentScene);
				}
			}

			//장면에 따라 달라지는 입력에 대한 결과
			if( currentScene == QUIT){
				//clearGraphFromZero( &menuFsm );	그대로는 문제가 생긴다. 
				//방향그래프 클리어 함수를 만들어야하지만, 그냥 귀찮아서 안 만듬.
				return 0;	//묻지도 따지지도 않고 종료
			}else{
				tempId = getSceneId(currentScene, input);	//입력값을 장면ID로 해석
			}

			if( hasNodeById( indicator, tempId ) ){			//input을 해석한 ID가 리스트 안에 있다면
				indicator = getVertex(&menuFsm, tempId);
				break;
			}
		}

	}
	
	return 0;
}

