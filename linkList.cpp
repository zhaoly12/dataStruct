#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
define a linkList
*/ 
#define elemType int
typedef struct Node
{
	elemType data;
	Node * next;
} Node, *linkList;


/*
initialize a linkList
*/
linkList initList()
{
	linkList l;
	l = (linkList)malloc(sizeof(Node));
	if(!l)
	{
		printf("linkLisk initialization failed!\n");
		exit;
	}
	else
	{
		l->next = NULL;
		printf("new linkList initialized!\n");
		return l;
	}
}
/*
another way to create a linkList
*/
void initList2(linkList * p)
{
	*p = (linkList)malloc(sizeof(Node));
	if(!(*p))
	{
		printf("linkList initialization failed!\n");
		exit;
	}
	else
	{
		(*p)->next = NULL;
		printf("new linkList initialized!\n");
	}
}

/*
get the length of a certain linkList
*/
int listLength(linkList l)
{
	int count = 1;
	Node * p = l->next;
	while(p)
	{
		count ++;
		p = p->next;
	}
	//printf("the length of this linkList is %d\n", count);
	return count;
}

/*
show linkList
*/
void showList(linkList l)
{
	printf("start");
	Node * p = l;
	while(p)
	{
		printf("->%d", p->data);
		p = p->next;
	}
	printf("\n");
} 

/*
get an element from a linkList
*/
// the index of the element is i-1
elemType getElem(linkList l, int i)
{
	if(i <= 0)
	{
		printf("error:i should be positive!\n");
		exit;
	}
	else
	{
		Node * p = l;
		int count = 1;
		while(p)
		{
			if(count == i)
				return p->data;
			p = p->next;
			count++;
		}
		printf("index is out of range!\n");
		exit;
	}
}

/*
insert a node into a linkList from its head
*/
void headInsList(linkList* l, Node* n)
{
	n->next = (*l)->next;
	(*l)->next = n;
}

/*
insert a node into a linkList from its tail
*/
void tailInsList(linkList l, Node* n)
{
	Node * p = l;
	while((p->next))
	{
		p = p->next;
	}
	p->next = n;
	n->next = NULL;
}

/*
insert a node into a linkList
*/
// the node's index is i-1
void insList(linkList* l, int i, Node* n)
{
	if (i == 1)
	{
		printf("data in the first node can not be changed!\n");
	}
	else if(i == 2)
	{
		headInsList(l, n);
	}
	else
	{
		Node *p = (*l)->next;
		int k = 3;
		while(p)
		{
			if(k == i)
			{
				n->next = p->next;
				p->next = n;
				break;
			}
			else
			{
				k++;
				p = p->next;
			}
		}
		if(!p)
			printf("index out of range!\n");
	}
}


/*
delete an element from a linkList
*/
// delete the node whose index is i-1
void delList(linkList* l, int i)
{
	Node *p = *l;
	if(i == 1)
	{
		printf("can not delete the start point. try another one\n"); 
	}
	else
	{
		Node * p2 = p->next;
		int k = 2;
		while(p2)
		{
			if(k == i)
			{
				p->next = p2->next;
				break;
			}
			else
			{
				p = p->next;
				p2 = p2->next;
				k++;
			}
		}
		if(!p2)
			printf("index out of range!\n");
	}
}

/*
get the location of an element in a linkList
*/
int locate(linkList l, elemType e)
{
	Node * p = l;
	int i = 1;
	while(p)
	{
		if(p->data == e)
		{
			//printf("the element is the No.%d of this linkList\n", i);
			return i;
		}
		p = p->next;			
		i++;
	}
	printf("element not found!\n");
	return -1;
}

/*
clear a linkList
*/
void clearList(linkList *l)
{
	(*l)->next = NULL;
	printf("linkList cleared!\n");
}

//test
int main()
{
	Node a,b,c,d;
	a.data = 1;
	a.next = NULL;
	b.data = 2;
	b.next = NULL;
	c.data = 3;
	c.next = NULL;
	d.data = 4;	
	d.next = NULL;
	
	Node * pa = &a, *pb = &b, *pc = &c, *pd = &d;
	
	// initialization
	linkList l = initList();
	linkList* l2 = (linkList*)malloc(sizeof(linkList));
	initList2(l2);
	linkList * pl = &l;
	l->data = 0;
	(*l2)->data = 0;
	
	// add node by hand
	l->next = &a;
	(*l2)->next = &a;
	
	// add nodes
	// mind that no matter what kind of ways the data in start point will always 0, because l is not just a pointer but a node	
	headInsList(pl, pb);
	tailInsList(l, pc);
	insList(pl,3,pd);
	showList(l);
	printf("the length of this linkList is %d\n", listLength(l));
	printf("the 2nd number is %d\n", getElem(l,2));
	printf("number 3 is the No.%d data of this linkList\n", locate(l,3));
	
	// delete nodes and clear linkList
	delList(pl, 4);
	showList(l);
	printf("the 2nd number is %d\n", getElem(l,2));
	printf("number 3 is the No.%d data of this linkList\n", locate(l,3));
	clearList(pl);
	showList(l);
	printf("the length of this linkList is %d\n", listLength(l));

	return 0;
}
