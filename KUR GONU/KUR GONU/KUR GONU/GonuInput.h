#ifndef _GONU_INPUT_H_
#define _GONU_INPUT_H_


#ifndef _INC_STDIO
# include <stdio.h>
#endif

#ifndef _INC_CONIO
# include <conio.h>
#endif

#ifndef _INC_STRING
# include <string.h>
#endif

#ifndef _WINDOWS_
# include <Windows.h>
#endif


#define INPUT_STR_LEN_MAX	10


enum strCommand{
	sKIP	=	1000,
	SKIP,
	mENU	=	2000,
	MENU,
	gG		=	3000,
	GG,
	nEXT	=	4000,
	NEXT,
	rE		=	5000,
	RE,
	qUIT	=	-1000,
};

enum fnKey{
	ARROW_START	=	0xffffffe0,
	UP			=	72,
	DOWN		=	80,
	RIGHT		=	77,
	LEFT		=	75,

	ENTER		=	13,
};


int areSameStr(char* str, char* cmp, int count);
void clearLineReadBuffer();
int gonuInput( int getStr );

void getn(int* n );


#endif
