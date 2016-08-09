/***************************************************
 *���� ���� �Ͱ� �¸��� ���� �Լ���
 * 
 *����� : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "Rull.h"
#include "MenuAndUI.h"

void killPiece( Piece* killed )
{
	if( killed->player == 1 ){					
		restP1--;	logWriter("���÷��̾� 2, BLUE�� RED�� ���� �����ϴ�!");
		lifeP2++;	logWriter("���÷��̾� 2, BLUE�� Life�� 1 �����մϴ�!");
					playerScreenUpdate(1);
					playerScreenUpdate(2);
	}else if( killed->player == 2 ){					
		restP2--;	logWriter("���÷��̾� 1, RED�� BLUE�� ���� �����ϴ�!");
		lifeP1++;	logWriter("���÷��̾� 1, RED�� Life�� 1 �����մϴ�!");
					playerScreenUpdate(1);
					playerScreenUpdate(2);
	}else{
		printf("killPiece�Լ�: %d �÷��̾ �������� �ʽ��ϴ�.", killed->player);
		//exit(1);
	}
}

//0: ���º�		1: 1p�� �й�		2: 2p�� �й�
int isDefeated( int player )
{	
	if( player == 1 )
	{
		if( isCastleCaptured(1) == 1){	
			logWriter("��BLUE�� RED�� ���� �Զ��Ͽ����ϴ�!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              BLUE�� �¸��Դϴ�!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( lifeP1 == 0 ){
			logWriter("��RED�� Life�� 0�� �Ǿ����ϴ�!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              BLUE�� �¸��Դϴ�!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( restP1 == 0 ){
			logWriter("��BLUE�� RED�� ��� ���� �����ϴ�!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              BLUE�� �¸��Դϴ�!");
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
			logWriter("��RED�� BLUE�� ���� �Զ��Ͽ����ϴ�!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              RED�� �¸��Դϴ�!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( lifeP2 == 0 ){
			logWriter("��BLUE�� Life�� 0�� �Ǿ����ϴ�!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              RED�� �¸��Դϴ�!");
			logWriter(" ");
			logWriter(" ");
			return 1;
		}
		else if( restP2 == 0 ){	
			logWriter("��RED�� BLUE�� ��� ���� �����ϴ�!!");
			logWriter(" ");
			logWriter(" ");
			logWriter("              RED�� �¸��Դϴ�!");
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
		printf("showWinBox�Լ�: player%d�� �������� �ʴ� �÷��̾��Դϴ�.", player);
		//exit(1);
	}
}

// ���� �зȴ��� üũ�ϴ� �Լ�
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
		printf("showWinBox�Լ�: player%d�� �������� �ʴ� �÷��̾��Դϴ�.", player);
		//exit(1);
	}

	return 0;
}
