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
// traverse a tree using stack instead of recursion
void traverse2(tree t, char mode)
{
	if(!t)
	{
		puts("empty tree!");
		return;	
	}	
	node* np = t; // node pointer
	node* stack[100]; // the number of the elements in the stack should no less than the number of nodes in the tree
	int i; 
	for(i=0;i<100;i++)
	{
		stack[i] = NULL;
	}
	int p = -1; // top of the stack
	// traverse in DLR sequence
	if(mode == 'h')
	{
		while(np)
		{
			printf("%c", np->data);
			if(np->RChild)// push
			{
				p++;
				stack[p] = np->RChild;
			}
			if(np->LChild)
			{
				np = np->LChild;
			}
			else
			{
				if(p>=0)// pop
				{
					np = stack[p];
					p--;
				}
				else
					np = NULL;
			}
		}
	}
	// traverse in LDR sequence
	else if(mode == 'c')
	{
		int flag = 0;
		while(np)
		{
			// push
			// you can see a node as a child tree
			// a child tree can be seen as already distroyed when it has already been traversed once
			if(np->RChild && flag == 0)
			{
				p++;
				stack[p] = np->RChild;
			}
			if(np->LChild && flag == 0)
			{
				p++;
				stack[p] = np;
				np = np->LChild;
			}
			else
			{
				printf("%c", np->data);
				if(p >= 0)
				{
					// this is an important part
					// when you get a node from the stack, it means you go back to some node that you once passed
					// if you go back to the right child of a node,  it means you will reverse the right child tree now 
					/* if you go back to a node that is not the right child of the node that you are checking, 
					 it means you have traversed the child tree whose root node is the node that you are checking now */ 
					if(np->RChild != stack[p])
						flag = 1;
					else
						flag = 0;	
					// pop	
					np = stack[p];
					p--;					
				}
				else
					np = NULL;
			}
		}
	}
	// traverse in LRD sequence
	else
	{
		int flag = 0;
		while(np)
		{
			// push
			// you can see a node as a child tree
			// a child tree can be seen as already distroyed when it has already been traversed once
			if((np->RChild || np->LChild) && flag == 0)
			{
				p++;
				stack[p] = np;
				if(np->RChild && np->LChild)
				{
					p++;
					stack[p] = np->RChild;
					np = np->LChild;
				}
				else if(np->RChild)
					np = np->RChild;
				else
					np = np->LChild;
			}
			else
			{
				printf("%c", np->data); 
				if(p >= 0)
				{
					// this is an important part
					// when you get a node from the stack, it means you go back to some node that you once passed
					/*
					if the node you get in the stack is the parent node of the node you are checking now,
					it means you have already traversed the child tree whose root node is the node you are checking now */			
					if(np->parent == stack[p])
						flag = 1;
					else
						flag = 0;
					// pop
					np = stack[p];
					p--;					
				}
				else
					np = NULL;
			}
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
	else
	{
		int max = depth(t->LChild) > depth(t->RChild) ? depth(t->LChild):depth(t->RChild);
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
void create(tree* t, tree parent)
{
	char data = getchar();
    if(data == '.')
    	*t = NULL;
    else
    {
    	(*t) = (node*)malloc(sizeof(node));
    	(*t)->data = data;
    	(*t)->parent = parent;
    	create(&((*t)->LChild), *t);
    	create(&((*t)->RChild), *t);
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
	create(t, NULL);
	empty((*t));
	printf("the root node of this tree is %c\n", root((*t)));
	int bias = 3;
	puts("the tree you have typed in is:");
	show((*t), bias);
	leafNodes(*t);
	printf("\n this tree has %d le, af nodes\n", leafNum); 
	printf("\n this tree has %d leaf nodes and its depth is %d\n", leafNodes2(*t), depth(*t)); 
	
	// traverse a binary tree
	puts("traverse this tree in DLR sequence:");
	traverse((*t), 'h');
	printf("\n");
	traverse2((*t), 'h');
	printf("\n");
	puts("traverse this tree in LDR sequence:");
	traverse((*t), 'c');
	printf("\n");
	traverse2((*t), 'c');
	printf("\n");	
	puts("traverse this tree in LRD sequence:");
	traverse((*t), 't');
	printf("\n");
	traverse2((*t), 't');
	printf("\n");
	
	// clear this binary tree 
	clear(t);	
	
	system("pause");
	
	return 0;
}
