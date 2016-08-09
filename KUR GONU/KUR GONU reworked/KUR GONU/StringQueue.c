/***************************************************
 *stringQueue
 * 
 *¸¸µç³ð : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "StringQueue.h"

void initQueue( StrQueue* queue )
{
	int i = 0;

	queue->front = queue->rear = 0;

	for( i = 0; i < Q_ARR_MAX; i++ ){
		queue->queue[i] = 0;
	}

}

int isEmptyQ( StrQueue* queue )
{
	if( queue->front == queue->rear ){
		return 1;
	}else{
		return 0;
	}
}

int isFullQ( StrQueue* queue )
{
	int check = (queue->rear + 1) % Q_ARR_MAX;

	if( queue->front == check ){
		return 1;
	}else{
		return 0;
	}
}

void insertQ( StrQueue* queue, char* str )
{
	if( isFullQ(queue) == 0 ){
		queue->rear = (queue->rear + 1) % Q_ARR_MAX;
		queue->queue[ queue->rear ] = str;
	}else{
		printf("queue is full");
	}
}

char* popQ( StrQueue* queue )
{
	if( isEmptyQ(queue) == 0 ){
		char* temp;

		queue->front = (queue->front + 1) % Q_ARR_MAX;
		temp = queue->queue[ queue->front ];
		queue->queue[ queue->front ] = 0;

		return temp;

	}else{
		printf("queue is empty");
		return NULL;
	}
}

void clearQueue( StrQueue* queue )
{
	int i;

	for( i = 0; i < Q_ARR_MAX; i++ ){
		queue->queue[i] = NULL;
	}

	queue->front = queue->rear = 0;
}