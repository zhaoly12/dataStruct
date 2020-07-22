#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
double circular linked list
define a node
*/ 
#define elemType int
typedef struct Node
{
	elemType data;
	Node * prior, * next;
} Node, *rear;


/*
initialize a double circular linkList
*/
rear initList()
{
	rear r = (rear)malloc(sizeof(Node));
	if(!r)
	{
		printf("double circular linked list initialization failed!\n");
		exit;
	}
	else
	{
		r->next = r;
		r->prior = r;
		r->data = 0;
		printf("double circular linked list initialized!\n");
		return r;
	}
}
/*
another way to create a double circular linkList
*/
void initList2(rear * p)
{
	*p = (rear)malloc(sizeof(Node));
	if(!(*p))
	{
		printf("double circular linked list initialization failed!\n");
		exit;
	}
	else
	{
		(*p)->next = *p;
		(*p)->prior = *p;
		(*p)->data = 0;
		printf("double circular linked list initialized!\n");
	}
}

/*
get the length of a certain linkList
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list

int listLength()
{
	
}


get an element from a linkList
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list

// the index of the element is i-1
elemType getElem()
{

}


get the location of an element in a linkList
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list

int locate()
{

}


clear a linkList
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list

void clearList()
{

}


check if a linkList is empty
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list 
 
// empty means the linkList only has one start point 
void emptyList()
{

}


merge two linkList in order
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list

rear mergeLists()
{

} 
*/

/*
insert a node into a double circular linkList from its head
*/
void headInsList(Node* n, rear * r)
{
	if((*r)->next == (*r))
	{
		(*r)->next = n;
		(*r)->prior = n;
		n->prior = *r;
		n->next = *r;
		*r = n;
	}
	else
	{
		(*r)->next->next->prior = n;  
		n->next = (*r)->next->next;
		(*r)->next->next = n;
		n->prior = (*r)->next;
	}
}

/*
insert a node into a double circular linkList from its tail
*/
void tailInsList(Node *n, rear* r)
{
	n->prior = *r;
	n->next = (*r)->next;
	(*r)->next->prior = n;
	(*r)->next = n;
	*r = n;
}

/*
insert a node into a double circular linkList
*/
// the node's index is i-1
void insList(rear * r, int i, Node *n)
{
	if(i <= 1)
	{
		printf("index should be more than 1!\n");
		exit;
	}
	else
	{
		int k = 2;
		Node *p = (*r)->next->next;
		while(p != (*r)->next)
		{
			if(k == i)
			{
				p->prior->next = n;
				n->next = p;
				n->prior = p->prior;
				p->prior = n;
				break;
			}
			k++;
			p = p->next;
		}
		if(p == (*r)->next)
		{
			if(k == i)
				tailInsList(n,r);
			else
				printf("index out of range!\n");
		}		
	}
}

/*
delete an element from a double circular linkList
*/
// delete the node whose index is i-1
void delList(rear * r, int i)
{
	if(i<=1)
	{
		printf("index should be more than 1!\n");
		exit;
	}
	else
	{
		int k = 2;
		Node *p = (*r)->next->next;
		while(p != (*r)->next)
		{
			if(k == i)
			{
				p->prior->next = p->next;
				p->next->prior = p->prior;
				break;
			}
			k++;
			p = p->next;
		}
		if(p == *r)
			*r = p->prior;
		if(p == (*r)->next)
			printf("index out of range!\n");
	}
}

/*
show linkList
if it is a double linked list this method is the same with what we do in linked list
if it is a double circular linked list this method is the same with what we do in circular linked list
*/
void showList(rear r)
{
	printf("start<=>%d", r->next->data);
	Node *p = r->next->next;
	while(p != r->next)
	{
		printf("<=>%d", p->data);
		p = p->next;
	}
	printf("<=>start\n");
} 

//test
int main()
{
	Node a,b,c,d;
	a.data = 1;
	b.data = 2;
	c.data = 3;
	d.data = 4;
	Node *pa = &a, *pb = &b, *pc = &c, *pd = &d;
	
	// initialize a list
	rear r = initList();
	rear *pr = &r;
	
	// add elements
	showList(r);
	tailInsList(pa,pr);
	showList(r);
	headInsList(pb,pr);
	showList(r);
	insList(pr,2,pc);
	showList(r);
	insList(pr,5,pd);
	showList(r);
	// delete elements
	delList(pr, 4);
	showList(r);
		
	system("pause");
		
	return 0;
}
