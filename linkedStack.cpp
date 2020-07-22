#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedStack.h"

/*
initialize a stack
*/
linkStack initStack()
{
	linkStack l = (linkStack)malloc(sizeof(node));
	if(!l)
	{
		printf("linked stack initialization failed!\n");
		exit;
	}
	else
	{
		l->next = NULL;
		printf("linked stack initialized!\n");
		return l;
	}
}

void initStack2(linkStack *l)
{
	*l = (linkStack)malloc(sizeof(node));
	if(!(*l))
	{
		printf("linked stack initialization failed!\n");
	}
	else
	{
		(*l)->next = NULL;
		printf("linked stack initialized!\n");
	}
}

/*
check a stack to find if it is empty
a linked stack will never full unless you run out of the memory of your computer
*/
void emptyStack(linkStack l)
{
	if(l->next == NULL)
		printf("this stack is empty!\n");
	else
		printf("this stack is not empty!\n");
}

/*
push an element into a stack
*/
void push(linkStack l, elemType e);

/*
pop an element from a stack
*/
int pop(linkStack l, elemType* e);


/*
clear a stack
*/
void clearStack(linkStack l)
{
	l->next = NULL;
}

/*
show a stack
*/
void showStack(linkStack l)
{
	if(!(l->next))
	{
		printf("empty stack!\n");
		exit;
	}
	else
	{
		printf("top");
		node *p = l->next;
		while(p)
		{
			printf("<-%d", p->data);
			p = p->next;
		}		
		printf("<-rear\n");
	}
}


// test
int main()
{
	
	// initialization
	elemType * e = (elemType*)malloc(sizeof(elemType));
	linkStack l = initStack();
	linkStack* l0 = (linkStack *)malloc(sizeof(linkStack));
	initStack2(l0);
	emptyStack(l);
	linkStack l1 = *l0;
	
	// push
	push(l, 1);
	push(l, 3);
	push(l, 5);
	emptyStack(l);
	showStack(l);
	
	// pop
	pop(l,e);
	printf("pop an element %d out of the stack\n", *e);
	showStack(l);
	pop(l, e);
	pop(l, e);
	pop(l, e);
	
	// clear
	clearStack(l);
	puts("stack cleared!");
	showStack(l);
	
	// create multipule stacks
	top[0] = initStack();
	top[1] = initStack();
	top[2] = initStack();
	top[3] = initStack();
	
	push(top[0], 1);
	push(top[0], 3);
	push(top[0], 5);
	
	push(top[1], 2);
	push(top[1], 4);
	push(top[1], 6);
	
	push(top[2], 1);
	push(top[2], 2);
	push(top[2], 3);
	
	push(top[3], 4);
	push(top[3], 5);
	push(top[3], 6);
	
	puts("multipule stacks created!");
	int no = 0;
	char s[10] = "\0";
	while(1)
	{
		puts("input a number 0, 1, 2, 3 to  choose a stack to display:");
		scanf("%d", &no);
		showStack(top[no]);
		puts("input exit to quit");
		scanf("%s", s);
		if(strcmp(s, "exit") == 0)
		{
			printf("\nbye!\n");
			break;
		}
	}
	
	system("pause");

	return 0;
}
