#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType char

#define maxSize 101

/*
use an array to show a binary tree
*/
// tree[0] will not be used 
// also tree defined to be a full binary tree 
// if there is a node that has nothing in it,  it will be filled with -999
elemType tree[maxSize];
 
/*
initialize a binary tree
*/
void init(elemType* tree)
{
	int k = 1;
	for(;k<maxSize;k++)
	{
		tree[k] = '.';
	}
} 

/*
check if a binary tree is an empty tree
*/
void empty(elemType* tree)
{
	if(tree[1] == '.')
		puts("this tree is empty!");
	else
		puts("this tree is not empty!");
}

/*
return the root of a binary tree
*/
elemType root(elemType* tree)
{
	return tree[1];	
}

/*
return the parent of a certain node of a binary tree
*/
// look up a tree upwards
elemType parent(elemType* tree, int i)
{
	if(tree[i] == '.')
	{
		puts("the No.i node of this tree is empty!");
		return tree[i];
	}
	else
	{
		return tree[i/2];
	}
}

/*
return the left child of a certain node of a binary tree
*/
// look up a tree downwards
elemType leftChild(elemType* tree, int i)
{
	if(tree[i] == '.')
	{
		puts("the No.i node of this tree is empty!");
		return tree[i];
	}
	else
	{
		return tree[i*2];
	}	
}

/*
return the right child of a certain node of a binary tree
*/
// look up a tree downwards
elemType rightChild(elemType* tree, int i)
{
	if(tree[i] == '.')
	{
		puts("the No.i node of this tree is empty!");
		return tree[i];
	}
	else
	{
		return tree[i*2+1];
	}	
}

/*
traverse a binary tree
*/
void traverse(elemType* tree, char mode, int k)
{
	if(tree[k] == '.')
	{
		return;
	}
	// traverse in DLR mode
	if(mode == 'h')
	{
		printf("%c", tree[k]);
		if(2*k < maxSize) 
			traverse(tree, mode, 2*k);
		if(2*k+1 < maxSize)
			traverse(tree, mode, 2*k+1);
	}
	// traverse in LDR mode
	else if(mode == 'c')
	{
		if(2*k < maxSize)
			traverse(tree, mode, 2*k);
		printf("%c", tree[k]);
		if(2*k+1 < maxSize)
			traverse(tree, mode, 2*k+1);		
	}
	// traverse in LRD mode
	else
	{
		if(2*k < maxSize)
			traverse(tree, mode, 2*k);
		if(2*k+1 < maxSize)
			traverse(tree, mode, 2*k+1);
		printf("%c", tree[k]);		
	}
}
// version2 use stack instead of recursion
void traverse2(elemType* tree, char mode, int k)
{
	if(tree[k] == '.')
		return;
	int stack[maxSize];
	int p = -1;
	int flag = 0;
	// DLR 
	if(mode == 'h')
	{
		while(k != -1)
		{
			printf("%c", tree[k]);
			if(2*k+1 < maxSize)
			{
				// if there is a right child tree save it firstly
				if(tree[2*k+1] != '.')
				{
					p++;
					stack[p] = 2*k+1;
				}
			}
				
			if(2*k < maxSize)
			{
				// if there is a left tree save it, too
				if(tree[2*k] != '.')
				{
					k = 2*k;
					flag = 1;
				}
			}
				
			if(flag == 0)
			{
				// pop
				if(p >= 0)
				{
					k = stack[p];
					p--;	
				}	
				else
					k = -1;
			}
			else 
				flag = 0;
		}
	}
	// LDR
	else if(mode == 'c')
	{
		int mark = 0;
		while(k != -1)
		{
			if(2*k+1 < maxSize && mark == 0)
			{
				if(tree[2*k+1] != '.')
				{
					p++;
					stack[p] = 2*k+1;
				}
			}
			if(2*k < maxSize && mark == 0)
			{
				if(tree[2*k] != '.')
				{
					p++;
					stack[p] = k;
					k = 2*k;
					flag = 1;
				}
			}
			if(flag == 0)
			{
				printf("%c", tree[k]);
				if(p >=0)
				{
					// if the node at the top of the stack is not the right child of the node being checked now, mark should be set
					// it means the child tree with the root node 'k' has already traversed  
					if(stack[p] != 2*k+1)
						mark = 1;
					else 
						mark = 0;
					k = stack[p];
					p--;					
				}
				else
					k = -1;
			}
			else
				flag = 0;
		}
	}
	// LRD
	else
	{
		int mark = 0;
		int right = 0;
		int left = 0;
		while(k != -1)
		{
			// check node has a right child
			if(2*k+1 < maxSize && mark == 0)
			{
				if(tree[2*k+1] != '.')
					right = 1;
			}
			// check if node has a left child
			if(2*k < maxSize && mark == 0)
			{
				if(tree[2*k] != '.')
					left = 1;
			}
			
			if(left == 1 || right == 1)
			{
				p++;
				stack[p] = k;
				if(right == 1 && left == 1)
				{
					p++;
					stack[p] = 2*k+1;	
					k = 2*k;	
				}	
				else if(right == 1)
					k = 2*k +1;
				else
					k = 2*k;
				
				right = 0;
				left = 0;
			}
			else
			{
				printf("%c", tree[k]);
				if(p >= 0)
				{
					if(k/2 == stack[p])
						mark = 1;
					else
						mark = 0;
					k = stack[p];
					p--;	
				}
				else
					k = -1;		
			}
		}
	}
}

/*
count the leaf nodes of a binary tree
*/
int leafNodes(elemType* tree, int k)
{
	if(tree[k] == '.')
		return 0;
	else
	{
		int left = 0;
		int right = 0;
		int flag = 0;
		if(2*k < maxSize)
		{
			if(tree[2*k] != '.')
			{
				left = leafNodes(tree, 2*k);
				flag = 1;	
			}
		}
		if(2*k+1 < maxSize)
		{
			if(tree[2*k+1] != '.')
			{
				right = leafNodes(tree, 2*k+1);
				flag = 1;				
			}
		}
		if(flag == 0)
			return 1;
		else
			return left+right;
	}
}

/*
calculate the depth of a binary tree
*/
int depth(elemType * tree, int k)
{
	if(tree[k] == '.')
		return 0;
	else
	{
		int left = 0;
		int right = 0;
		if(2*k < maxSize)
		{
			if(tree[2*k] != '.')
				left = depth(tree, 2*k);
		}
		if(2*k+1 < maxSize)
		{
			if(tree[2*k+1] != '.')
				right = depth(tree, 2*k+1);
		}
		return 1+(left>=right?left:right);
	}
}

/*
create a binary tree
*/
// create a binary tree in DLR sequence
void create(elemType* tree, int k)
{
	if(k < maxSize)
	{
		tree[k] = getchar();
		if(tree[k] != '.')
		{
			create(tree, 2*k);
			create(tree, 2*k+1);
		}	
	}
}

/*
empty a binary tree
*/
void clear(elemType* tree, int k)
{
	int root = k;
	for(;k<maxSize;k++)
	{
		tree[k] = '.';
	}
	printf("tree cleared the root node is tree[%d]!\n", root);
}

/*
show a tree
*/
// use RDL sequence to show a tree
void show(elemType* tree, int k, int layer)
{
	if(tree[k] == '.')
		return;
	// show right child tree
	if(2*k+1 < maxSize)
		show(tree, 2*k+1, layer+1);
	// show root node
	int i;
	for(i=1;i<layer;printf("   "),i++);
	printf("%c\n", tree[k]);
	// show left child tree
	if(2*k < maxSize)
		show(tree, 2*k, layer+1);
}

// test
int main()
{
	// initialize a binary tree
	init(tree);
	empty(tree);
	//printf("the root node of this tree is %c\n", root((*t)));
	
	// create a binary tree
	puts("\nplease input all the nodes of a binary tree");
	puts("if you input '.' it means this position is empty");
	puts("don't forget that the leaf nodes also have 'childs', which are '.'");
	puts("\nnow please input the nodes in sequence:"); 
	create(tree, 1);
	empty(tree);
	printf("the root node of this tree is %c\n", root(tree));
	int bias = 3;
	puts("the tree you have typed in is:");
	show(tree, 1, bias);
	printf("\n this tree has %d leaf nodes and its depth is %d\n", leafNodes(tree, 1), depth(tree, 1)); 
	
	// traverse a binary tree
	puts("traverse this tree in DLR sequence:");
	traverse(tree, 'h', 1);
	printf("\n");
	traverse2(tree, 'h', 1);
	printf("\n");
	puts("traverse this tree in LDR sequence:");
	traverse(tree, 'c', 1);
	printf("\n");
	traverse2(tree, 'c', 1);
	printf("\n");	
	puts("traverse this tree in LRD sequence:");
	traverse(tree, 't', 1);
	printf("\n");
	traverse2(tree, 't', 1);
	printf("\n");
	
	// clear this binary tree 
	clear(tree, 1);	

	system("pause");

	return 0;
}
