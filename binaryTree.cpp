#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType char

/*
define a binary tree using linked list
*/
typedef struct node
{
	elemType data;
	node* LChild, *RChild, *parent;	
} node, *tree;
 
/*
initialize a binary tree
*/
void init(tree* t)
{
	(*t) = NULL;
} 

/*
check if a binary tree is an empty tree
*/
void empty(tree t)
{
	if(t)
		puts("the tree is not empty!");
	else
		puts("the tree is empty!");
}

/*
return the root of a binary tree
*/
elemType root(tree t)
{
	if(!t)
	{
		puts("empty tree!");
		exit(0);
	}
	return t->data;
}

/*
return the parent of a certain node of a binary tree
*/
// look up a tree upwards
node* parent(node* n)
{
	return n->parent;
}

/*
return the left child of a certain node of a binary tree
*/
// look up a tree downwards
node* leftChild(node* n)
{
	return n->LChild;
}

/*
return the right child of a certain node of a binary tree
*/
// look up a tree downwards
node* rightChild(node* n)
{
	return n->RChild;
}

/*
traverse a binary tree
*/
void traverse(tree t, char mode)
{
	if(!t)
	{
		return;
	}
	node* left = t->LChild, *right = t->RChild, *p = t;
	// traverse in DLR sequence
	if(mode == 'h')
	{
		if(!p)
			return;
		else
		{
			printf("%c", p->data);
			traverse(left, mode);
			traverse(right, mode);
		}	
	}
	// traverse in LDR sequence
	else if(mode == 'c')
	{
		if(!p)
			return;
		else
		{
			traverse(left, mode);
			printf("%c", p->data);
			traverse(right, mode);
		}
	}
	// traverse in LRD sequence
	else
	{
		if(!p)
			return;
		else
		{
			traverse(left, mode);
			traverse(right, mode);
			printf("%c", p->data);
		}
	}
	
}

int leafNum = 0;
/*
count the number of the leaf nodes of a tree
*/
void leafNodes(tree t)
{
	if(t)
	{
		leafNodes(t->LChild);
		leafNodes(t->RChild);
		if((t->LChild == NULL)&&(t->RChild == NULL))
			leafNum++; 
	}
}
// count leaf nodes version 2
int leafNodes2(tree t)
{
	if(!t)
		return 0;
	if((t->LChild == NULL)&&(t->RChild == NULL))
		return 1;
	return leafNodes2(t->LChild)+leafNodes2(t->RChild);
}

/*
return the depth of a binary tree
*/
int depth(tree t)
{
	if(!t)
		return 0;
	if(t->LChild == NULL)
		return depth(t->RChild)+1;
	else if(t->RChild == NULL)
		return depth(t->LChild)+1;
	else
		return  1+ (depth(t->LChild) > depth(t->RChild) ? depth(t->LChild):depth(t->RChild));
}
// version2
int depth2(tree t)
{
	if(!t)
		return 0;
	else
	{
		int max = depth2(t->LChild) > depth2(t->RChild) ? depth2(t->LChild):depth2(t->RChild);
		return max+1;
	}
}

/*
show a binary tree 
*/ 
// using RDL sequence 
void show(tree t, int layer)
{
	if(!t)
		return;
	show(t->RChild, layer+1);
	int i;
	for(i=1;i<layer;printf("   "),i++);
	printf("%c\n", t->data);
	show(t->LChild, layer+1);
}

/*
create a binary tree using a list
*/
// this list is a string and '.'means nothing 
void create(tree * t)
{
	char data = getchar();
    if(data == '.')
    	*t = NULL;
    else
    {
    	(*t) = (node*)malloc(sizeof(node));
    	(*t)->data = data;
    	create(&((*t)->LChild));
    	create(&((*t)->RChild));
	}
}

/*
empty a binary tree
*/
void clear(tree* t)
{
	(*t) = NULL;
	puts("tree cleared!");
}


// test
int main()
{
	tree * t = (tree*)malloc(sizeof(tree));
	// initialize a binary tree
	init(t);
	empty((*t));
	//printf("the root node of this tree is %c\n", root((*t)));
	
	// create a binary tree
	puts("\nplease input all the nodes of a binary tree");
	puts("if you input '.' it means this position is empty");
	puts("don't forget that the leaf nodes also have 'childs', which are '.'");
	puts("\nnow please input the nodes in sequence:"); 
	create(t);
	empty((*t));
	printf("the root node of this tree is %c\n", root((*t)));
	int bias = 3;
	puts("the tree you have typed in is:");
	show((*t), bias);
	leafNodes(*t);
	printf("\n this tree has %d leaf nodes and its depth is %d\n", leafNum, depth(*t)); 
	printf("\n this tree has %d leaf nodes and its depth is %d\n", leafNodes2(*t), depth2(*t)); 
	
	// traverse a binary tree
	puts("traverse this tree in DLR sequence:");
	traverse((*t), 'h');
	printf("\n");
	puts("traverse this tree in LDR sequence:");
	traverse((*t), 'c');
	printf("\n");	
	puts("traverse this tree in LRD sequence:");
	traverse((*t), 't');
	printf("\n");
	
	// clear this binary tree 
	clear(t);	
	
	system("pause");
	
	return 0;
}
