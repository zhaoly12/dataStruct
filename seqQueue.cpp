#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType int
#define maxSize 100

/*
define a circular queue
*/ 
// sequential queue can overflow fakely so we use circular queue instead
typedef struct
{
	elemType data[maxSize];
	int front;   // delete element from head
	int rear;	// insert element from rear
} cirQ;

/*
initialize a queue
*/
// "front" point at the first element of the queue and "rear" point at the next position of the last element of the queue
void init(cirQ* q)
{
	q->front = 0;
	q->rear = 0;
}

/*
check if a queue is empty
*/
void empty(cirQ* q)
{
	if(q->rear == q->front)
		printf("the queue is empty!\n");
	else
		printf("the queue is not empty!\n");
}

/*
check if a queue is full
*/
void full(cirQ*q)
{
	if(q->front == (q->rear + 1)%maxSize)
		printf("the queue is full!\n");
	else
		printf("the queue is not full!\n");
}

/*
enter an element into a queue
*/ 
void enter(cirQ* q, elemType e)
{
	if(q->front == (q->rear + 1)%maxSize)
	{
		printf("the queue is already full!\n");
		return;
	}
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % maxSize;
}

/*
delete an element from a queue
*/
void del(cirQ* q, elemType * e)
{
	if(q->front == q->rear)
	{
		printf("the queue is already empty!\n");
		return;
	}
	*e = q->data[q->front];
	q->front = (q->front + 1) % maxSize;
}

/*
get an element from a queue
*/
void get(cirQ* q, elemType* e)
{
	if(q->front == q->rear)
	{
		printf("the queue is already empty!\n");
		return;
	}
	*e = q->data[q->front];	
}

/*
clear a queue
*/
void clear(cirQ* q)
{ 
	q->front = q->rear = 0;
}

/*
show a queue
*/
void show(cirQ* q)
{
	if(q->front == q->rear)
	{
		printf("empty queue!\n");
		return;
	}
	
	int  k = q->front;
	while(k != q->rear)
	{
		printf("%d<-", q->data[k]);
		k++;
	}
	printf("rear\n");
}

/*
an example: draw yang hui triangle using queue
*/
void yangHuiTriangle(int len)
{
	cirQ *q = (cirQ*)malloc(sizeof(cirQ));
	init(q);
	elemType *e = (elemType*)malloc(sizeof(elemType));

	enter(q, 1);
	
	int i;	
	for(i = 2;i <= len;i++)
	{
		enter(q, 1);// enter the first element into the No.i row
		int no;
		int j;
		// calculate the elements which not equal to 1 of the No.i row
		for(j = 1;j <= i-2;j++)
		{
			del(q, e);// pull the NO.(j) element out of the No.(i-1) row and display it
			printf("%d ", *e);
			no = *e;
			get(q, e);
			no = no + *e;
			enter(q, no);// calculat the No.(j+1) element of the No.i row 
		}
		del(q, e);// pull the last element out of the No.(i-1) row
		printf("%d ", *e);
		enter(q, 1);// enter the last element into the No.i row
		printf("\n");
	}
	
	// display the last row
	while(q->rear != q->front)
	{
		del(q, e);
		printf("%d ", *e);
	}
}


// test
int main()
{
	cirQ * q = (cirQ *)malloc(sizeof(cirQ));
	
	// initialize a queue
	init(q);
	empty(q);
	show(q);
	
	// enter
	enter(q, 1);
	enter(q, 2);
	enter(q, 3);
	enter(q, 4);
	empty(q);
	full(q);
	show(q);
	
	// get
	elemType* e = (elemType*)malloc(sizeof(elemType));
	get(q, e);
	printf("get the top element %d\n", *e);
		
	// delete
	del(q, e);
	printf("delete an element %d\n", *e);
	show(q);
	del(q, e);
	printf("delete an element %d\n", *e);
	show(q);
	
	// clear
	clear(q);
	puts("queue cleared!\n");
	empty(q);
	show(q);
	
	// create a queue again
	enter(q, 1);
	enter(q, 2);
	enter(q, 3);
	enter(q, 4);
	empty(q);
	full(q);
	show(q);
	
	// an example of the use of circular queue
	puts("draw a yang hui triangle using queue");
	puts("input the length of the triangle:");
	int len;
	scanf("%d", &len);
	yangHuiTriangle(len);
	system("pause");	
	return 0;
}
