/***************************************************
 *말을 따는 것과 승리에 대한 함수들
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "Rull.h"
#include "MenuAndUI.h"

void killPiece( Piece* killed )
{
	if( killed->player == 1 ){					
		restP1--;	logWriter("◈플레이어 2, BLUE가 RED의 말을 땄습니다!");
		lifeP2++;	logWriter("♥플레이어 2, BLUE의 Life가 1 증가합니다!");
					playerScreenUpdate(1);
					playerScreenUpdate(2);
	}else if( killed->player == 2 ){					
		restP2--;	logWriter("◈플레이어 1, RED가 BLUE의 말을 땄습니다!");
		lifeP1++;	logWriter("♥플레이어 1, RED의 Life가 1 증가합니다!");
					playerScreenUpdate(1);
					playerScreenUpdate(2);
	}else{
		printf("killPiece함수: %d 플레이어가 존재하지 않습니다.", killed->player);
		//exit(1);
	}
}

//0: 무승부		1: 1p가 패배		2: 2p가 패배
int isDefeated( int player )
{	
	if( player == 1 )
	{
		if( isCastleCaptured(1) == 1){	
			logWriter("◈BLUE가 RED의 성을 함락하였습니다!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              BLUE의 승리입니다!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( lifeP1 == 0 ){
			logWriter("◈RED의 Life가 0이 되었습니다!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              BLUE의 승리입니다!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( restP1 == 0 ){
			logWriter("◈BLUE가 RED의 모든 말을 땄습니다!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              BLUE의 승리입니다!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else{
			return 0;
		}

	}
	else if( player = 2 )
	{
		if( isCastleCaptured(2) == 1){
			logWriter("◈RED가 BLUE의 성을 함락하였습니다!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              RED의 승리입니다!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( lifeP2 == 0 ){
			logWriter("◈BLUE의 Life가 0이 되었습니다!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              RED의 승리입니다!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( restP2 == 0 ){	
			logWriter("◈RED가 BLUE의 모든 말을 땄습니다!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              RED의 승리입니다!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else{
			return 0;
		}

	}
	else
	{
		printf("showWinBox함수: player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}
}

// 성이 털렸는지 체크하는 함수
int isCastleCaptured( int player )
{
	Crossing* nowCheck;
	int i;

	if( player == 1 )
	{
		i = 0;
		nowCheck = castlesP1[i];
		while( nowCheck != NULL ){
			if( nowCheck->occupier != NULL){
				return 1;
			}

			i++;
			nowCheck = castlesP1[i];
		}

	}
	else if( player = 2 )
	{
		i = 0;
		nowCheck = castlesP2[i];
		while( nowCheck != NULL ){
			if( nowCheck->occupier != NULL){
				return 1;
			}

			i++;
			nowCheck = castlesP2[i];
		}

	}
	else
	{
		printf("showWinBox함수: player%d는 존재하지 않는 플레이어입니다.", player);
		//exit(1);
	}

	return 0;
}
