/* ���ڿ������͸� �����ϴ� ť */
#include <stdio.h>

#define Q_ARR_MAX	16	//queue�� �迭�� ���� ũ��, queue�� �� �� �ִ� data�� ���� 15

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