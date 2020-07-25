#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AtomType int 

typedef enum {
	ATOM=0, LIST=1
} elemTag;

/*
define a generalized list
*/
// an atom has a flag of 0 and an atom only has a value
// a list has a flag of 1 and a list has a head pointer and a tail pointer
typedef struct GLNode
{
	elemTag flag;
	union
	{
		AtomType atom;
		struct {
			GLNode* hp, *tp;	
		}htp;
	}atom_htp;
} GLNode, *gList;


/*
initialize a generalized list
*/
gList init()
{
	return NULL;
}

/*
check a generalized list to find if it is empty
*/
void empty(gList gl)
{
	if(!gl)
	{
		puts("this generalized list is empty!");
		return;	
	}
	else if(gl->flag == ATOM)
	{
		puts("this is not an atom!");
		return;		
	}
	else
		puts("this generalized list is not empty!");
}

/*
get the length of the generalized list
*/
int length(gList gl)
{
	if(!gl)
		return 0;
	if(gl->flag == ATOM)
	{
		return 0;		
	}
	else
	{
		int k = 0;
		GLNode* p = gl;
		while(p)
		{
			p = (p->atom_htp).htp.tp;
			k++;
		}
		return k;
	}
}

/*
get the depth of the generalized list
*/
int depth(gList gl)
{
	if(!gl)
		return 1;
	if(gl->flag == ATOM)
	{
		return 0;		
	}
	int d, result = 0;
	GLNode *p =gl;
	while(p)
	{
		d = depth(p->atom_htp.htp.hp);
		if(d > result)
			result = d;
		p = p->atom_htp.htp.tp;
	}
	return (result+1);
}

/*
get how many atoms there are in a generalizd list
*/
int atomNum(gList gl)
{
	if(!gl)
		return 0;
	if(gl->flag == ATOM)
	{
		return 1;		
	}
	else
	{
		GLNode* p = gl;
		return (atomNum(p->atom_htp.htp.hp)+(atomNum(p->atom_htp.htp.tp)));	
	}
}

// test
int main()
{
	// init
	gList gl = init();
	empty(gl);
	// get length
	printf("the length of this generalized list is %d\n", length(gl));
	// get depth
	printf("the depth of this generalized list is %d\n", depth(gl));
	// count atoms
	printf("there are %d atoms in this generalized list\n", atomNum(gl));
	
	// add elements into this generalized list
	gl = (gList)malloc(sizeof(GLNode));
	gl->flag = LIST; 
	gl->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gl->atom_htp.htp.hp->flag = ATOM;
	gl->atom_htp.htp.hp->atom_htp.atom = 1;
	gl->atom_htp.htp.tp = NULL;
	//(1)
	puts("\nchanged to (1)!\n");
	// get length
	printf("the length of this generalized list is %d\n", length(gl));
	// get depth
	printf("the depth of this generalized list is %d\n", depth(gl));
	// count atoms
	printf("there are %d atoms in this generalized list\n", atomNum(gl));	
	
	gl->atom_htp.htp.tp = (gList)malloc(sizeof(GLNode));
	GLNode* gln2 = gl->atom_htp.htp.tp;
	gln2->flag = LIST;
	gln2->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gln2->atom_htp.htp.tp = NULL;
	gln2->atom_htp.htp.hp->flag = LIST;
	gln2->atom_htp.htp.hp->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gln2->atom_htp.htp.hp->atom_htp.htp.hp->flag = ATOM;
	gln2->atom_htp.htp.hp->atom_htp.htp.hp->atom_htp.atom = 2;
	gln2->atom_htp.htp.hp->atom_htp.htp.tp = NULL;
	// (1,(2))
	puts("\nchanged to (1,(2))!\n");
	// get length
	printf("the length of this generalized list is %d\n", length(gl));
	// get depth
	printf("the depth of this generalized list is %d\n", depth(gl));
	// count atoms
	printf("there are %d atoms in this generalized list\n", atomNum(gl));
	
	gln2->atom_htp.htp.hp->atom_htp.htp.tp = (gList)malloc(sizeof(GLNode));
	GLNode* gln3 = gln2->atom_htp.htp.hp->atom_htp.htp.tp;
	gln3->flag = LIST;
	gln3->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gln3->atom_htp.htp.tp = NULL;
	gln3->atom_htp.htp.hp->flag = ATOM;
	gln3->atom_htp.htp.hp->atom_htp.atom = 3;
	// (1,(2,3))
	puts("\nchanged to (1,(2,3))!\n");
	// get length
	printf("the length of this generalized list is %d\n", length(gl));
	// get depth
	printf("the depth of this generalized list is %d\n", depth(gl));
	// count atoms
	printf("there are %d atoms in this generalized list\n", atomNum(gl));
	
	gln3->atom_htp.htp.tp = (gList)malloc(sizeof(GLNode));
	GLNode* gln4 = gln3->atom_htp.htp.tp;
	gln4->flag = LIST;
	gln4->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gln4->atom_htp.htp.tp = NULL;
	gln4->atom_htp.htp.hp->flag = LIST;
	gln4->atom_htp.htp.hp->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gln4->atom_htp.htp.hp->atom_htp.htp.tp = NULL;
	gln4->atom_htp.htp.hp->atom_htp.htp.hp->flag = ATOM;
	gln4->atom_htp.htp.hp->atom_htp.htp.hp->atom_htp.atom = 4;
	// (1,(2,3,(4)))
	puts("\nchanged to (1,(2,3,(4)))!\n");
	// get length
	printf("the length of this generalized list is %d\n", length(gl));
	// get depth
	printf("the depth of this generalized list is %d\n", depth(gl));
	// count atoms
	printf("there are %d atoms in this generalized list\n", atomNum(gl));
	
	gln2->atom_htp.htp.tp = (gList)malloc(sizeof(GLNode));
	GLNode* gln5 = gln2->atom_htp.htp.tp;
	gln5->flag = LIST;
	gln5->atom_htp.htp.tp = NULL;
	gln5->atom_htp.htp.hp = (gList)malloc(sizeof(GLNode));
	gln5->atom_htp.htp.hp->flag = ATOM;
	gln5->atom_htp.htp.hp->atom_htp.atom = 5;
	// (1,(2,3,(4)),5) 
	puts("\nchanged to (1,(2,3,(4)),5)!\n");
	// get length
	printf("the length of this generalized list is %d\n", length(gl));
	// get depth
	printf("the depth of this generalized list is %d\n", depth(gl));
	// count atoms
	printf("there are %d atoms in this generalized list\n", atomNum(gl));
	
	system("pause");
	
	return 0;
}
