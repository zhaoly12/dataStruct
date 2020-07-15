#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
define a node
*/ 
#define elemType int
typedef struct Node
{
	elemType data;
	Node * next;
} Node, *rear;
// for circular linked list we use rear pointer instead of head pointer
// also mind that head = rear->next

/*
initialize a circular linkList
*/
rear initList()
{
	rear r;
	r = (rear)malloc(sizeof(Node));
	if(!r)
	{
		printf("circular linked list initialization failed!\n");
		exit;
	}
	else
	{
		r->next = r;
		printf("new circular linked list initialized!\n");
		return r;
	}
}
/*
another way to create a circular linkList
*/
void initList2(rear * p)
{
	*p = (rear)malloc(sizeof(Node));
	if(!(*p))
	{
		printf("circular linked list initialization failed!\n");
		exit;
	}
	else
	{
		(*p)->next = (*p);
		printf("new circular linked list initialized!\n");
	}
}

/*
get the length of a certain linkList
*/
int listLength(rear r)
{
	int count = 1;
	Node * p = r->next->next;
	while(p != (r->next))
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
void showList(rear r)
{
	printf("start->%d", r->next->data);
	Node * p = r->next->next;
	while(p!=(r->next))
	{
		printf("->%d", p->data);
		p = p->next;
	}
	printf("->start\n");
} 

/*
get an element from a linkList
*/
// the index of the element is i-1
elemType getElem(rear r, int i)
{
	if(i <= 0)
	{
		printf("error: index should be positive!\n");
		exit;
	}
	else
	{	
		if (i == 1)
		{
			return r->next->data;
		}
		Node *p = r->next->next;
		int count = 2;
		while(p != r->next)
		{
			if(i == count)
				return p->data;
			count++;
			p = p->next;
		}
		printf("index out of range!\n");
		exit;
	}
}

/*
insert a node into a linkList from its head
*/
void headInsList(Node* n, rear r)
{
	n->next = r->next->next;
	r->next->next = n;
}

/*
insert a node into a linkList from its tail
*/
void tailInsList(Node *n, rear* r)
{
	n->next = (*r)->next;
	(*r)->next = n;
	*r = n;
}

/*
insert a node into a linkList
*/
// the node's index is i-1
void insList(rear * r, int i, Node *n)
{
	if(i == 1)
	{
		printf("data in first point can not be changed!\n");
	}
	else
	{
		Node *p = (*r)->next->next;
		int count = 2;
		while(p != (*r)->next)
		{
			if(count == i)
			{
				n->next = p->next;
				p->next = n;
				if(p == (*r))
					*r = n;
				break;
			}
			p = p->next;
			count ++;
		}
		if(p == (*r)->next)
			printf("index out of range!\n");
	}
}


/*
delete an element from a linkList
*/
// delete the node whose index is i-1
void delList(rear * r, int i)
{
	if(i == 1)
	{
		printf("cannot delete the start point! try another one!\n");
	}
	else
	{
		int count = 2;
		Node *p = (*r)->next->next, *pt = (*r)->next;
		while(p != (*r)->next)
		{
			if(count == i)
			{
				pt->next = p->next;
				if(p == (*r))
					*r = pt;
				break;
			}
			p = p->next;
			pt = pt->next;
			count++;
		}
		if(p == (*r)->next)
			printf("index out of range!\n");
	}
}

/*
get the location of an element in a linkList
*/
int locate(rear r, elemType e)
{
	if(r->next->data == e)
		return 1;
		
	int count = 2;
	Node *p = r->next->next;
	while(p != r->next)
	{
		if(p->data == e)
			return count;
		count ++;
		p = p->next;	
	}
	printf("element not found!\n");
	return -1;
}

/*
clear a linkList
*/
void clearList(rear *pr)
{
	(*pr)->next->next = (*pr)->next;
	printf("linkList cleared!\n");
}

/*
check if a linkList is empty 
*/ 
// empty means the linkList only has one start point 
void emptyList(rear r)
{
	if(r->next->next == r->next)
		printf("the linkList is empty!\n");
	else
		printf("the linkList is not empty!\n");
}

/*
merge two linkList in order
*/
rear mergeLists(rear ra, rear rb)
{
	Node * pa = ra->next->next, *pb = rb->next->next;
	
	Node * l = (Node*)malloc(sizeof(Node));
	l->data = 0;
	rear r = l;
	while((pa != ra->next) && (pb != rb->next))
	{
		Node *pt = (Node*)malloc(sizeof(Node));
		if(pa->data <= pb->data)
		{
			pt->data = pa->data;
			pa = pa->next;
		}
		else
		{
			pt->data = pb->data;
			pb = pb->next;
		}
		r->next = pt;
		r = pt;
	}
	if(pa == ra->next)
	{
		while(pb != rb->next)
		{
			Node *pt = (Node*)malloc(sizeof(Node));
			pt->data = pb->data;
			r->next = pt;
			r = pt;
			pb = pb->next;
		}
		r->next = l;
		return r;
	}
	else if(pb == rb->next)
	{
		while(pa != ra->next)
		{
			Node *pt = (Node*)malloc(sizeof(Node));
			pt->data = pa->data;
			r->next = pt;
			r = pt;
			pa = pa->next;
		}	
		r->next = l;
		return r;	
	}
	else
	{
		r->next = l;
		return r;
	}
} 


//test
int main()
{
	Node a,b,c,d;
	a.data = 1;
	b.data = 2;
	c.data = 3;
	d.data = 4;	
	
	Node * pa = &a, *pb = &b, *pc = &c, *pd = &d;
	
	// initialization
	rear r = initList();
	rear* r2 = (rear*)malloc(sizeof(rear));
	initList2(r2);
	rear * pr = &r;
	r->data = 0;
	(*r2)->data = 0;
	
	// add node by hand
	r->next = &a;
	a.next = r;
	r = &a;
	(*r2)->next = &a;
	a.next = (*r2);
	(*r2) = &a;	

	// add nodes
	// mind that no matter what kind of ways the data in start point will always 0, because l is not just a pointer but a node	
	headInsList(pb, r);
	tailInsList(pc, pr);
	insList(pr,3,pd); 
	showList(r); 
	printf("the length of this linkList is %d\n", listLength(r));
	printf("the 2nd number is %d\n", getElem(r,2));
	printf("number 3 is the No.%d data of this linkList\n", locate(r,3));
	
	// delete nodes and clear linkList
	delList(pr, 4);
	showList(r);
	printf("the 2nd number is %d\n", getElem(r,2));
	printf("number 3 is the No.%d data of this linkList\n", locate(r,3));
	clearList(pr);
	showList(r);
	emptyList(r);
	printf("the length of this linkList is %d\n", listLength(r));
 
 	
	// merge two linkLists
	rear ra = initList();
	rear rb = initList();
	ra->data = 0;
	rb->data = 0;
	rear * pra = &ra, *prb = &rb;
	/*
	be careful here!
	if a node has been used in a linked list it couldn't be used in another linked list or the first linked list will be changed!
	*/
	tailInsList(pa, pra);
	tailInsList(pb, pra);
	tailInsList(pc, prb);
	tailInsList(pd, prb);
	rear rab = mergeLists(ra, rb);
	printf("merge the following two linkLists:\n");
	showList(ra);
	showList(rb);
	puts("the result is:"); 
	showList(rab);
	
	return 0;
}
