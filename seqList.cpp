#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
define a seqlist
*/
#define maxSize 100
typedef int elemType;
typedef struct
{
	elemType elem[maxSize];
	int lastNo;
} seqList;


/*
initialize a seqlist
*/
seqList* initList()
{
	seqList* l;
	l = (seqList*)malloc(sizeof(seqList));
	if(!l)
	{
		printf("seqList initialization failed!\n");
		exit;
	}
	else
	{
		l->lastNo = -1;
		printf("initialize seqList successfully!\n");
		return l;
	}
}

// initialize a seqList in another way
void initList2(seqList** l)
{
	*l = (seqList*)malloc(sizeof(seqList));
	if(!(*l))
	{
		printf("seqList initialization failed!\n");
		exit;
	}
	else
	{
		(*l)->lastNo = -1;
		printf("seqList initialized!\n");
	}
}

/*
get the length of a certain seqlist
*/
int listLength(seqList l)
{
	int len = l.lastNo+1;
	return len;	
} 

/*
get an element from a seqlist
*/
// the index of this element is i-1
elemType getElem(seqList l, int i)
{
	if((i>=1) && (i<= (l.lastNo+1)))
	{
		return l.elem[i-1];
	}
	else
	{
		printf("index error!\n");
		exit;
	}
}

/*
insert an element into a seqlist
*/
// insert element e into seqList and e has index i-1
void insList(seqList* l, int i, elemType e)
{
	if((l->lastNo + 1 < maxSize) && (i <= l->lastNo+2) && (i >= 1)) 
	{
		int k = l->lastNo;
		for (;k>=i-1;k--)
		{
			l->elem[k+1] = l->elem[k]; 
		}
		l->elem[i-1] = e;
		l->lastNo = l->lastNo+1;
		printf("new element inserted!\n");
	}
	else if((l->lastNo == -1) && (i == 1)) 
	{
		l->elem[0] = e;
		l->lastNo ++;
		printf("new element inserted!\n");
	}
	else
	{
		printf("element insert failed!\n");
	}
}

/*
delete an element 
*/
// the index of this element is i-1
void delList(seqList* l, int i)
{
	if((l->lastNo != -1) && (i >= 1) && (i <= (l->lastNo+1)))
	{
		int k = i;
		for(;k<=l->lastNo;k++)
		{
			l->elem[k-1] = l->elem[k];
		}
		l->elem[k-1] = l->elem[k];
		l->lastNo = l->lastNo - 1;
		printf("element deleted!\n");
	}
	else
	{
		printf("element delete failed!\n");
	}
}

/*
get the location of an element in a seqlist
*/
int locate(seqList l, elemType e)
{
	if(l.lastNo >= 0)
	{
		int k;
		for (k=0;k<= l.lastNo;k++)
		{
			if(l.elem[k] == e)
			{
				printf("the element is the No.%d element of this seqList", k+1);
				return k+1;
			}
		}
		printf("element not found!\n");
		return 0;
	}
	else
	{
		printf("this list is empty!\n");
		return 0;
	}
}

/*
clear a seqlist
*/
void clearList(seqList* l)
{
	if(l->lastNo == -1)
	{
		printf("this list is empty!\n");
	}	
	else
	{
		int k;
		for (k=0;k<=l->lastNo;k++)
		{
			l->elem[k] = l->elem[l->lastNo+1];
		}
		l->lastNo = -1;
		printf("list cleared!\n");
	} 
}


/*
check a seqlist to know if it is empty or not
*/
void emptyList(seqList l)
{
	if(l.lastNo == -1)
	{
		printf("this seqList is empty\n");
	}
	else
	{
		printf("this seqList is not empty\n");
	}
}

/*
show seqList 
*/
void showList(seqList* l)
{
	if(l->lastNo == -1)
	{
		printf("this seqList is empty!\n");
	}
	else
	{
		printf("start");
		int k;
		for(k=0;k<=l->lastNo;k++)
		{
			printf("->%d", l->elem[k]);
		}
		printf("\n");
	}
}

// test
int main() {
	// create a seqList 
	seqList* l = initList();
	seqList ** l2;
	l2 = (seqList**)malloc(sizeof(seqList*));
	initList2(l2);
	// check if it is empty
	emptyList(*l); 
	// insert 4 elements into it
	elemType a=1,b=2,c=3, d=4;
	insList(l,1,a);
	showList(l);
	insList(l,2,b);
	showList(l);
	insList(l,2,c);
	showList(l);
	insList(l,2,d);
	// 1->4->3->2
	showList(l);
	printf("\nthe location of 2 is %d\n", locate(*l,2));
	// show the length of this seqList
	printf("\nthe length of this seqList is %d\n",listLength(*l)); 
	// delete an element from seqList
	delList(l,2);
	printf("\nthe 2nd number has been deleted\n");
	showList(l);
	printf("\nthe 3rd, element of this seqList is %d\n",getElem(*l,3));
	printf("\nthe length of this seqList is %d\n",listLength(*l)); 
	// check if it is empty
	emptyList(*l);
	// clear this seqList
	clearList(l);
	emptyList(*l); 
	 
	return 0;
}
