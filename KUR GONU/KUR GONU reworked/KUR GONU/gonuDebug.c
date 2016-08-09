/***************************************************
 *고누 게임용 디버깅 함수들...
 *
 * 무쓸모.
 * 
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "GameData.h"
#include "ConsoleGraphics.h"
#include "MenuAndUI.h"

void printMapEnterables()
{
	static int turnNum = 0;
	Crossing** cursor;
	int count = 0;

	setColor(BLACK, WHITE); gotoXY(LOG_SCREEN_X, LOG_SCREEN_Y);
	printf("%d", turnNum);
	setColor(WHITE, BLACK); gotoXY(LOG_SCREEN_X, LOG_SCREEN_Y+1);

	cursor = mapCrossingArr;
	while( *cursor != NULL ){
		if( count % 5 == 0 ){
			_putch(' ');
		}

		printf("%d", (*cursor)->enterable.p1 );
		cursor++;
		count++;
	}

	gotoXY(LOG_SCREEN_X, LOG_SCREEN_Y+2);

	cursor = mapCrossingArr;
	while( *cursor != NULL ){
		if( count % 5 == 0 ){
			_putch(' ');
		}

		printf("%d", (*cursor)->enterable.p2 );
		cursor++;
		count++;
	}

	turnNum++;
}

