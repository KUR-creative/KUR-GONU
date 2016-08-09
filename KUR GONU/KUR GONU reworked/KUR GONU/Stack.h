#ifndef _STACK_H_
#define	_SRACK_H_

#ifndef _INC_STDIO
# include <stdio.h>
#endif

#define STACK_MAX	30
#define FALSE		0
#define TRUE		!(FALSE)

typedef struct IntStack{
	int top;
	int arr[STACK_MAX];
} IntStack;
//ADT함수
void push(IntStack* pstack, int data);
int pop(IntStack* pstack);
void stackInit(IntStack* pstack);
int peek(IntStack stack);
int isEmptyStack(IntStack* pstack);
int isFullStack(IntStack* pstack);

#endif