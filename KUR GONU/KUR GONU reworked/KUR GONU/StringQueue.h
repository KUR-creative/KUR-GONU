/* 문자열포인터를 저장하는 큐 */
#include <stdio.h>

#define Q_ARR_MAX	16	//queue속 배열의 실제 크기, queue에 들어갈 수 있는 data의 수는 15

typedef struct StrQueue{
	char* queue[Q_ARR_MAX];
	int front;
	int rear;
} StrQueue;

void initQueue( StrQueue* queue );
int isEmptyQ( StrQueue* queue );
int isFullQ( StrQueue* queue );
void insertQ( StrQueue* queue, char* str );
char* popQ( StrQueue* queue );
void clearQueue( StrQueue* queue );