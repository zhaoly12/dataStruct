#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
use linked list to solve polynomial problem 
*/

typedef struct node
{
	int index;
	int coefficient;
	node * next;
} node, * linkList;

/*
get a polynomial
*/
void get(linkList l)
{
	puts("please input the first polynomial:");
	puts("input -100 to end"); 
	node* n = (node*)malloc(sizeof(node));
	l->next = n;
	int flag = 0;
	while(1)
	{
		puts("the index of this term:");
		scanf("%d", &(n->index));
		puts("the coefficient of this term:");
		scanf("%d", &(n->coefficient));
		puts("if you want to end input -100 now:");
		scanf("%d", &flag);
		if(flag == -100)
			break;
		node* tmp = (node*)malloc(sizeof(node));
		n->next = tmp;
		n = tmp; 
	}
	n->next = NULL;
}

/*
show a polynomial
*/
void show(linkList l)
{
	printf("\n");
	node * p = l->next;
	while(p)
	{
		printf("%dx^%d",p->coefficient, p->index);
		if(p->next)
			printf("+");
		p = p->next;
	}
	printf("\n");
}

linkList cal(linkList la, linkList lb)
{
	linkList l = (linkList)malloc(sizeof(node));
	node * pa = la->next, *pb = lb->next, *n = l;
	while(pa&&pb)
	{
		n->next = (linkList)malloc(sizeof(node));
		n = n->next;
		if(pa->index < pb->index)
		{
			n->coefficient = pa->coefficient;
			n->index = pa->index;
			pa = pa->next;
		}
		else if(pa->index > pb->index)
		{
			n->coefficient = pb->coefficient;
			n->index = pb->index;
			pb = pb->next;
		}
		else
		{
			n->coefficient = pa->coefficient + pb->coefficient;
			n->index = pa->index;
			pa = pa->next;
			pb = pb->next;
		}
	}
	if(pa)
	{
		while(pa)
		{
			n->next = (linkList)malloc(sizeof(node));
			n = n->next;
			n->coefficient = pa->coefficient;
			n->index = pa->index;
			pa = pa->next;			
		}
		n->next = NULL;
		
	}
	else if (pb)
	{
		while(pb)
		{
			n->next = (linkList)malloc(sizeof(node));
			n = n->next;
			n->coefficient = pb->coefficient;
			n->index = pb->index;
			pb = pb->next;			
		}		
		n->next = NULL;
	}
	else
	{
		n->next = NULL;
	}
	
	return l;
}

int main()
{
	puts("input the first polynomial");
	linkList la = (linkList)malloc(sizeof(node));
	get(la);
	
	puts("input the second polynomial");
	linkList lb = (linkList)malloc(sizeof(node));
	get(lb);
	
	linkList l = cal(la, lb);
	
	show(la);
	puts("plus");
	show(lb);
	puts("equals");
	show(l);
		
	return 0;
}
