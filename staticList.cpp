#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 100
#define elemType int

/*
define a static list 
for a static list the start point has the index 0 and the cursor of the final point is -1
*/
typedef struct
{
	elemType data;
	int cursor;	
} Component, staticList[MaxSize]; 


/*
initialize a static list
*/
void initList(staticList l, int *bkp)
{
	l[0].cursor = -1;
	l[0].data = 0;
	int i;
	for(i=1;i<MaxSize-1;i++)
	{
		l[i].cursor = i+1;
	}
	l[MaxSize-1].cursor = -1;
	*bkp = 1;
}

/*
get the length of a certain static list
*/
int listLength(staticList l)
{
	int k;
	Component e = l[0];
	for(k=0;k<MaxSize;k++)
	{
		if (e.cursor == -1)
		{
			return k+1;
		}
		e = l[e.cursor];
	}
}

/*
show static list
*/
void showList(staticList l)
{
	printf("start->");
	int k;
	Component e = l[0];
	for(k=0;k<MaxSize;k++)
	{
		printf("%d->",e.data);
		if(e.cursor == -1)
			break;
		e = l[e.cursor];
	}
	printf("end\n");
} 

/*
select a node that have not been used yet from a static list
*/
int makeNode(staticList l, int * bkp)
{
	int index = *bkp;
	if(l[index].cursor== -1)
	{
		puts("ERROR:make node failed!no space for new nodes!\n");
		return -1;
	}
	*bkp = l[index].cursor;
	return index;
}

/*
free a node
*/
void freeNode(staticList l, int *bkp, int index)
{
	l[index].cursor = *bkp;
	*bkp = index;
}

/*
get an element from a staic list
*/
// the index of the element is i-1
elemType getElem(staticList l, int i)
{
	int k;
	Component e = l[0];
	for (k=1;k<=i;k++)
	{
		if(k == i)
			return e.data;
		if (e.cursor == -1) 
			break;
		e = l[e.cursor];
	}
	printf("index out of range!\n");
	exit;
}

/*
insert a node into a list from its head
*/
void headInsList(staticList l, int * bkp, elemType data)
{
	int index = makeNode(l, bkp);
	l[index].data = data;
	l[index].cursor = l[0].cursor;
	l[0].cursor = index;
}

/*
insert a node into a list from its tail
*/
void tailInsList(staticList l, int *bkp, elemType data)
{
	int k = 0;
	while(l[k].cursor != -1)
	{
		k = l[k].cursor;
	}
	int index = makeNode(l, bkp);
	l[index].data = data;
	l[k].cursor = index;
	l[index].cursor = -1;
}

/*
insert a node into a list
*/
// the node's index is i-1
void insList(staticList l, int* bkp, int i, elemType data)
{
	if(i <= 1)
	{
		printf("the index of the position you can insert starts from 2!\n");
		exit;
	}
	else
	{
		int k = 2;
		int index = 0;
		int flag = 0; 
		while(1)
		{
			if (k == i)
				break;
			if(l[index].cursor == -1)
			{
				if(k == i)
				{
					break;
				}
				else
				{
					puts("index out of range!\n");
					flag = 1;
					break;
				} 
			}	
			index = l[index].cursor;
			k++;
		}
		if(flag != 1)
		{
			int index1 = makeNode(l, bkp);
			l[index1].data = data;
			l[index1].cursor = l[index].cursor;
			l[index].cursor = index1;	
		}	
	}
}


/*
delete an element from a list
*/
// delete the node whose index is i-1
void delList(staticList l, int *bkp, int i)
{
	if(i <= 1)
	{
		printf("the index of the nodes that you can delete starts from 2!\n");
		exit;
	}
	else
	{
		int k = 2;
		int index = 0;
		while(1)
		{
			if(l[index].cursor == -1)
			{
				printf("index out of range!\n");
				exit;
			}
			if(k == i)
			{
				int insFree = l[index].cursor;
				l[index].cursor = l[l[index].cursor].cursor;
				freeNode(l, bkp, insFree);
				printf("node deleted!\n");
				break;
			}
			index = l[index].cursor;
			k++;			
		}
	}
}

/*
get the location of an element in a list
*/
int locate(staticList l, elemType e)
{
	int i, index = 0;
	for(i=1;i<=MaxSize;i++)
	{
		if(l[index].data == e)
			return i;
		else if (l[index].cursor == -1)
			break;
		else
			index = l[index].cursor;
	}
	printf("element not found!\n");
	return -1;
}

/*
clear a list
*/
void clearList(staticList l, int* bkp)
{
	if(l[0].cursor == -1)
		exit;
	int index1 = 0, index;
	while(index1 != -1)
	{
		index = l[index1].cursor;
		freeNode(l, bkp, index1);
		index1 = index;
	}
	puts("\nstatic list cleared!\n");
}

/*
check if a list is empty 
*/ 
// empty means the linkList only has one start point 
void emptyList(staticList l)
{
	if(l[0].cursor == -1)
		printf("this static list is empty!\n");
	else
		printf("this static list is not empty!\n");
}


// test
int main()
{
	// initialize a static list
	staticList l;
	int *bkp = (int*)malloc(sizeof(int));
	initList(l, bkp);
	showList(l);
	emptyList(l); 
	printf("the length of this static list is %d\n", listLength(l)); 
	
	// insert data into the static list	
	headInsList(l, bkp, 1);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	tailInsList(l, bkp, 2);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	tailInsList(l, bkp, 3);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	headInsList(l, bkp, 4);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	printf("4 is the No.%d element of the static list\n", locate(l, 4));
	printf("the No.3 element of this static list is %d\n", getElem(l, 3));
	insList(l, bkp, 6, 2);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	
	// clear the list
	clearList(l,bkp);
	// create list again;
	initList(l, bkp);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	// reinsert data into the static list	
	headInsList(l, bkp, 1);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	tailInsList(l, bkp, 2);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	tailInsList(l, bkp, 3);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	headInsList(l, bkp, 4);
	showList(l);
	printf("the length of this static list is %d\n", listLength(l));
	printf("4 is the No.%d element of the static list\n", locate(l, 4));
	printf("the No.3 element of this static list is %d\n", getElem(l, 3));
	// delete node 
	delList(l,bkp, 5);
	showList(l);

	return 0;	
} 
