
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType int 

#define M 10

/*
define a linked stack
*/
typedef struct node
{
	elemType data;
	node * next;
} node, *linkStack;
// use top[M] to control M linked lists
linkStack top[M];

/*
initialize a stack
*/
linkStack initStack();

void initStack2(linkStack *l);

/*
check a stack to find if it is empty
a linked stack will never full unless you run out of the memory of your computer
*/
void emptyStack(linkStack l);

/*
push an element into a stack
*/
void push(linkStack l, elemType e)
{
	node * newNode = (node*)malloc(sizeof(node));
	if(!newNode)
	{
		printf("ERROR:you have run out of the memory of your computer!\n");
	}
	else
	{
		newNode->next = l->next;
		newNode->data = e;
		l->next = newNode;
	}
}

/*
pop an element from a stack
*/
int pop(linkStack l, elemType* e)
{
	if(l->next == NULL)
	{
		printf("this stack is already empty!\n");
		return 0;
	}
	else
	{
		*e = l->next->data;
		l->next = l->next->next;
		return 1;	
	}
}

/*
clear a stack
*/
void clearStack(linkStack l);

/*
show a stack
*/
void showStack(linkStack l);

