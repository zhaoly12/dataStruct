#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType int
#define maxSize 100

/*
define a linked queue
*/ 
struct node
{
	elemType data;
	node* next;
};
// "front" points at the first node which has no data
// "rear" points at the last node which has data
struct linkQ
{
	node* front;
	node* rear;	
};


/*
initialize a queue
*/
void init(linkQ* q)
{
	q->front = (node*)malloc(sizeof(node));
	if(q->front)
	{
		q->rear = q->front;
		q->front->next = NULL;
	}
	else
		printf("ERROR:you have run out of the memory of your computer!\n");
}

/*
check if a queue is empty
*/
void empty(linkQ* q)
{
	if(q->rear == q->front)
		printf("the queue is empty!\n");
	else
		printf("the queue is not empty!\n");
}

/*
enter an element into a queue
*/ 
void enter(linkQ* q, elemType e)
{
	node* p = (node*)malloc(sizeof(node));
	if(!p)
	{
		printf("ERROR: you have run out of the memory of your computer!\n");
		return;
	}
	p->next = NULL;
	p->data = e;
	q->rear->next = p;
	q->rear = p;
}

/*
delete an element from a queue
*/
void del(linkQ* q, elemType * e)
{
	if(q->front == q->rear)
	{
		printf("the queue is already empty!\n");
		return;
	}
	*e = q->front->next->data;
	if(q->front->next == q->rear)
		q->rear = q->front;
	q->front->next = q->front->next->next;
}

/*
get an element from a queue 
*/
void get(linkQ* q, elemType* e);

/*
clear a queue
*/
void clear(linkQ* q)
{ 
	q->rear = q->front;
	q->front->next = NULL;
}

/*
show a queue
*/
void show(linkQ* q)
{
	if(q->front == q->rear)
	{
		puts("empty queue!\n");
		return;
	}
	
	node * p = q->front->next;
	while(p)
	{
		printf("%d<-", p->data);
		p = p->next;
	}
	printf("rear\n");
}


// test
int main()
{
	linkQ* q = (linkQ*)malloc(sizeof(linkQ));
	// initialize a queue
	init(q);
	empty(q);
	show(q);
	
	// insert
	enter(q, 1);
	enter(q, 3);
	enter(q, 5);
	enter(q, 7);
	empty(q);
	show(q);
	
	// delete
	elemType *e = (elemType*)malloc(sizeof(elemType));
	del(q,e);
	printf("delete an element %d\n", *e);
	show(q);
	del(q,e);
	printf("delete an element %d\n", *e);
	show(q);
	
	// clear
	clear(q);
	puts("queue cleared!\n");
	empty(q);
	show(q);
	
	// create a queue again
	enter(q, 2);
	enter(q, 4);
	enter(q, 6);
	enter(q, 8);
	empty(q);
	show(q);

	return 0;
}
