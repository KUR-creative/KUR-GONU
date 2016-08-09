/***************************************************
 *IntStack
 *
 *만든놈 : KUR 
 * https://www.facebook.com/KURcreative
 * kur941017@gmail.com
 *
 *********************************************/

#include "Stack.h"

int isEmptyStack(IntStack* pstack)
{
	if( pstack->top <= -1 ){
		return TRUE;
	}else{
		return FALSE;
	}
}

int isFullStack(IntStack* pstack)
{
	if(pstack->top == STACK_MAX - 1){
		return TRUE;
	}else{
		return FALSE;
	}
}

void push(IntStack* pstack, int data)
{
	if( isFullStack(pstack) ){
		printf("stack overflow!");
	}else{
		(pstack->top)++;
		pstack->arr[ (pstack->top) ] = data;
	}

}
int pop(IntStack* pstack)
{
	if( isEmptyStack(pstack) ){
		//printf("stack memory error!"); 
		return FALSE;
	}
	else{
		int temp = pstack->arr[ (pstack->top)-- ];
		int tmp = pstack->top + 1;
		pstack->arr[ tmp ] = 0;
		return temp;
	}
	
}

void stackInit(IntStack* pstack)
{
	pstack->top = NULL;
}

int peek(IntStack stack)
{
	return stack.arr[stack.top];
}
