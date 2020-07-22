#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stackSize 100

#define elemType int 

/*
define a stack
*/
typedef struct
{
	elemType data[stackSize];
	int top;
} seqStack;

/*
initialize a stack
*/
void initStack(seqStack *s)
{
	s->top = -1;
}

/*
check a stack to find if it is empty
*/
void emptyStack(seqStack* s)
{
	if(s->top == -1)
		printf("this stack is empty!\n");
	else
		printf("this stack is not empty\n");
}

/*
check a stack to find if it is full
*/
void fullStack(seqStack* s)
{
	if(s->top == stackSize-1)
		printf("this stack is full!\n");
	else
		printf("this stack is not full!\n");
	
}

/*
push an element into a stack
*/
void push(seqStack *s, elemType e)
{
	if(s->top == stackSize-1)
	{
		printf("ERROR:this stack is already full!\n");
		exit;
	}
	else
	{
		s->data[s->top+1] = e;
		s->top = s->top +1;	
	}
}

/*
pop an element from a stack
*/
void pop(seqStack* s, elemType* e)
{
	if(s->top == -1)
	{
		printf("this stack is already empty!\n");
		exit;
	}
	else
	{
		*e = s->data[s->top];
		s->top--;
	}
}

/*
get an element from a sequential stack
*/
void getTop(seqStack*s, elemType* e)
{
	if(s->top == -1)
	{
		printf("this stack is already empty!\n");
		exit;
	}
	else
	{
		*e = s->data[s->top];
	}	
}

/*
clear a stack
*/
void clearStack(seqStack* s)
{
	s->top = -1;
}

/*
show a stack
*/
void showStack(seqStack *s)
{
	if(s->top == -1)
	{
		printf("empty stack!\n");
		exit;
	}
	else
	{
		int i = 0;
		printf("start");
		while(i != s->top+1)
		{
			printf("->%d", s->data[i]);
			i++;
		}		
		printf("->end\n");
	}
}


// test
int main()
{
	seqStack *s = (seqStack*)malloc(sizeof(seqStack));
	elemType *e = (elemType*)malloc(sizeof(elemType));
	
	// initialize a sequential stack
	initStack(s); 
	emptyStack(s); 
	
	// push
	push(s, 1);
	push(s, 2);
	push(s, 3);
	push(s, 4);
	push(s, 5);
	emptyStack(s);
	fullStack(s);
	printf("the stack is:\n");
	showStack(s);
	
	// get
	getTop(s, e);
	printf("the top element of this stack is %d\n", *e);	 
	
	// pop
	pop(s, e);
	printf("pop an element %d out of stack\n", *e);
	showStack(s);
	pop(s, e);
	printf("pop an element %d out of stack\n", *e);
	showStack(s);
	
	// get 
	getTop(s, e);
	printf("the top element of this stack is %d\n", *e);
	
	// clear
	clearStack(s);
	emptyStack(s);
	showStack(s);
	pop(s, e);
	push(s, 1);
	push(s, 3);
	push(s, 5);
	printf("now stack is:\n");
	showStack(s);
	
	system("pause");
	
	return 0;
}
