#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stackSize 100

#define elemType int 

/*
define a dual stack
*/
typedef struct
{
	elemType data[stackSize];
	elemType top[2];
} dqStack;

/*
initialize a stack
*/
void initStack(dqStack *s)
{
	s->top[0] = -1;
	s->top[1] = stackSize;
}

/*
check a stack to find if it is empty
*/
void emptyStack(dqStack* s)
{
	if(s->top[0] == -1)
		printf("the left stack is empty!\n");
	else
		printf("this left stack is not empty\n");
	if(s->top[1] == stackSize)
		printf("the right stack is empty!\n");
	else
		printf("this right stack is not empty\n");	
}

/*
check a stack to find if it is full
*/
void fullStack(dqStack* s)
{
	if(s->top[0] == s->top[1]-1)
		printf("this stack is full!\n");
	else
		printf("this stack is not full!\n");
	
}

/*
push an element into a stack
*/
void push(dqStack *s, elemType e, int choice)
{
	// 0 stands for the left stack 
	// 1 stands for the right stack
	if(choice != 0 && choice != 1)
	{
		printf("ERROR: only two stacks can be chosen 0 or 1!\n");
		exit;	
	}	
	else
	{
		if(s->top[0] == s->top[1]-1)
		{
			printf("ERROR:this stack is already full!\n");
			exit;
		}
		else
		{
			switch (choice)
			{
				case 0: 
					s->top[0]++;
					break;
				case 1:
					s->top[1]--;
					break;
			}	
			s->data[s->top[choice]] = e;
		}
	}
}

/*
pop an element from a stack
*/
void pop(dqStack* s, elemType* e, int choice)
{
	switch(choice)
	{
		case 0:
			if(s->top[0] == -1)
			{
				printf("the left stack is empty!\n");
				break;
			}
			*e = s->data[s->top[0]];
			s->top[0]--;
			break;
		case 1:
			if(s->top[1] == stackSize)
			{
				printf("the left stack is empty!\n");
				break;
			}
			*e = s->data[s->top[1]];
			s->top[1]++;
			break;
		default:
			printf("only have two choice 0 or 1!\n");
	}
}

/*
clear a stack
*/
void clearStack(dqStack* s)
{
	int choice;
	puts("input 0 to clear the left stack, input 1 to clear the right stack, input 2 clear all of them");
	scanf("%d", &choice);
	if(choice == 0)
		s->top[0] = -1;
	else if(choice == 1)
		s->top[1] = stackSize;
	else if(choice == 2)
	{
		s->top[0] = -1;
		s->top[1] = stackSize;
	}
	else
		printf("ERROR:please input 0 1 or 2!\n");
}

/*
show stack
*/
void showStack(dqStack *s)
{
	if(s->top[0] == -1)
		printf("the left stack is empty!\n");
	else
	{
		printf("the left stack is:\n");
		int i = 0;
		printf("rear");
		while(i != s->top[0]+1)
		{
			printf("->%d", s->data[i]);
			i++;
		}		
		printf("->top\n");
	}
	
	if(s->top[1] == stackSize)
		printf("the right stack is empty!\n");
	else
	{
		printf("the right stack is:\n");
		int i = s->top[1];
		printf("top");
		while(i != stackSize)
		{
			printf("<-%d", s->data[i]);
			i++;
		}		
		printf("<-rear\n");
	}
}

// test
int main()
{
	dqStack*  s = (dqStack*)malloc(sizeof(dqStack));
	elemType *e = (elemType*)malloc(sizeof(elemType));
	
	// initialization
	initStack(s);
	emptyStack(s);
	fullStack(s);
	
	// push
	push(s, 1, 0);
	push(s, 3, 0);
	push(s, 5, 0);
	emptyStack(s);
	puts("left stack done!");
	showStack(s);
	push(s, 2, 1);
	push(s, 4, 1);
	push(s, 6, 1);
	emptyStack(s);
	puts("right stack done!");
	showStack(s);	
		
	// pop
	pop(s, e, 0);
	printf("pop an element %d out of left stack:\n", *e);
	showStack(s);
	pop(s, e, 1);
	printf("pop an element %d out of right stack:\n", *e);
	showStack(s);
	
	// clear
	clearStack(s);
	showStack(s);
	
	push(s, 1, 0);
	push(s, 2, 1);
	puts("new stack made");
	showStack(s);
	clearStack(s); 
	showStack(s);
	
	return 0;
}
