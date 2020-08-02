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
	int LTag, RTag;	
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
    	(*t)->LTag = 0;
    	(*t)->RTag = 0;
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
	puts("\ntree cleared!");
}

/*
thread a binary tree
*/
// if a node does not have a left child LTag will be set to 1 and its left child pointer will point at its prior node
// if a node does not have a right child RTag will be set to 1 and its right child pointer will point at its next node
void thread(tree t, node** pre, char mode)
{
	// thread a tree in DLR sequence
	if(mode == 'h')
	{
		if(t)
		{
			if(t->LChild == NULL && (*pre) != NULL)
			{
				t->LTag = 1;
				t->LChild = (*pre);
			}
			if(*pre)
			{
				if(!(*pre)->RChild)
				{
					(*pre)->RTag = 1;
					(*pre)->RChild = t;
				}
			}
			*pre = t;
			printf("->%c", (*pre)->data);
			
			// thread the left child tree
			if(t->LTag != 1)
				thread(t->LChild, pre, 'h');
			// thread the right child tree
			if(t->RTag != 1)
				thread(t->RChild, pre, 'h');
		}
	}
	// thread a tree in LDR sequence
	else if (mode == 'c')
	{
		if(t)
		{
			// thread the left child tree
			thread(t->LChild, pre, 'c');
			
			if(!t->LChild && (*pre) != NULL)
			{
				t->LTag = 1;
				t->LChild = *pre;
			}	
			if(*pre)
			{
				if(!(*pre)->RChild)	
				{
					(*pre)->RTag = 1;
					(*pre)->RChild = t;	
				}	
			}
			*pre = t;
			printf("->%c", (*pre)->data);
			
			// thread the right child tree
			thread(t->RChild, pre, 'c');
		}
	}
	// thread a tree in LRD sequence
	else
	{
		if(t)
		{
			// thread the left child tree
			thread(t->LChild, pre, 't');
			// thread the right child tree
			thread(t->RChild, pre, 't');
			
			if(t->LChild == NULL && (*pre) != NULL && t->LTag != 1)
			{
				t->LTag = 1;
				t->LChild = *pre;
			}	
			if(*pre)
			{
				if((*pre)->RChild == NULL && (*pre)->RTag != 1)	
				{
					(*pre)->RTag = 1;
					(*pre)->RChild = t;	
				}	
			}
			*pre = t;
			printf("->%c", (*pre)->data);
		}
	}	
}

/*
find the prior node of a node in a threaded binary tree
*/
node* prior(node* n, char mode)
{
	node* pre = NULL;
	if(n->LTag == 1)
		pre = n->LChild;
	else
	{
		// DLR 
		// the right chid of the rightmost leaf node is NULL in DLR mode
		// the left child of the root node is NULL in DLR mode when there is no left child tree
		if(mode == 'h')
		{
			node* p = n->parent;
			if(p)
			{
				if(n == p->LChild || (p->LChild == NULL))
					 pre = p;
				else
				{
					// this node is the right child and its parent node has a left child
					// in this case the prior node is the last node of the left child tree in DLR mode(the rightmost leaf node of the left child tree)
					pre = p->LChild;
					while((pre->LTag == 0 && pre->LChild) || (pre->RTag == 0 && pre->RChild))
					{
						if(pre->RChild)
							pre = pre->RChild;
						else
							pre = pre->LChild;
					}		
				}
			}
			else
				pre = NULL;
		}
		// LDR
		// the right chid of the rightmost leaf node is NULL in LDR mode
		// the left child of the leftmost leaf node is NULL in LDR mode
		else if(mode == 'c')
		{
			node* p = NULL;
			// the most right node of the left child tree is the prior node(here is different from LRD and DLR. the node does not have to be a leaf node!)
			if(n->LChild)
				for(p=n->LChild;(p->RTag==0 && p->RChild);p=p->RChild);
			pre = p;
		}
		// LRD
		// the left child of the leftmost leaf node is NULL in LRD mode
		// the right child of the root node is NULL in LRD mode when there is no right child tree
		else
		{
			if(n->RTag == 0 && n->RChild)
				pre = n->RChild;
			else
				pre = n->LChild;
		}	
	}

	return pre;
}

/*
find the next node of a node in a threaded binary tree
*/
node* next(node* n, char mode)
{
	node* next = NULL;
	if(n->RTag == 1)
		next = n->RChild;
	else
	{
		// DLR 
		if(mode == 'h')
		{
			if(n->LTag == 0 && n->LChild)
				next = n->LChild;
			else
				next = n->RChild;
		}
		// LDR
		else if(mode == 'c')
		{
			node* p = NULL;
			// the most left node of the right child tree is the next node(here is different from LRD and DLR. the node does not have to be a leaf node!)
			if(n->RChild)
				for(p=n->RChild;(p->LTag==0 && p->LChild);p=p->LChild);
			next = p;
		}
		// LRD
		else
		{
			node* p = n->parent;
			if(p)
			{
				if(n == p->RChild || (p->RChild == NULL))
				{
					next = p;		
				}
				else
				{
					// the node is the left child and its parent node has a right child
					// the next node is the first node of the right child tree(the leftmost leaf node of the right child tree)
					next = p->RChild;
					while((next->LChild && next->LTag == 0) || (next->RTag == 0 && next->RChild))
					{
						if(next->LChild)
							next = next->LChild;
						else
							next = next->RChild;
					}
				}
			}
			else
				next = NULL;
		}			
	} 
	
	return next;
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
	fflush(stdin);
	empty((*t));
	printf("the root node of this tree is %c\n", root((*t)));
	int bias = 3;
	puts("the tree you have typed in is:");
	show((*t), bias);
	leafNodes(*t);
	printf("\n this tree has %d leaf nodes\n", leafNum); 
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
	
	// thread a binary tree
	node** pt = (node**)malloc(sizeof(node*));
	*pt = NULL;
	node* p = *t;
/*
	puts("\nthread the tree in LDR sequence");
	printf("LDR");
	thread((*t), pt, 'c');	
	
	puts("\nfind the next node");
	while(next(p,'c'))
	{
		printf("->%c", p->data);
		p = next(p,'c');
	}	
	printf("->%c\n", p->data);
	
	puts("\nfind the prior node");
	while(prior(p,'c'))
	{
		printf("->%c", p->data);
		p = prior(p,'c');
	}
	printf("->%c\n", p->data);
*/
/*	
	puts("\nthread the tree in DLR sequence");
	printf("DLR");
	thread((*t), pt, 'h');
		
	puts("\nfind the next node");
	while(next(p,'h'))
	{
		printf("->%c", p->data);
		p = next(p,'h');
	}	
	printf("->%c\n", p->data);
	
	puts("\nfind the prior node");
	while(prior(p,'h'))
	{
		printf("->%c", p->data);
		p = prior(p,'h');
	}
	printf("->%c\n", p->data);
*/	
	
	puts("\nthread the tree in LRD sequence");
	printf("LRD");
	thread((*t), pt, 't');	
	
	puts("\nfind the prior node");
	while(prior(p,'t'))
	{
		printf("<-%c", p->data);
		p = prior(p,'t');
	}
	printf("<-%c\n", p->data);	
	
	puts("\nfind the next node");
	while(next(p,'t'))
	{
		printf("->%c", p->data);
		p = next(p,'t');
	}	
	printf("->%c\n", p->data);	


	// clear this binary tree 
	clear(t);	
	
	system("pause");
	
	return 0;
}
