#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType char

/*
define a tree
*/
/* there are three kinds of ways to express a tree: 
1. using data and the parent pointer(node = {data, parent pointer}, tree = {node lists, number of nodes})
2. using data and children list(node = {data, first child pointer}, childnode = {child node position, next sibling pointer}, tree = {node list, root node position, number of nodes})
3. using data, first child pointer and next sibling pointer(node = {data, first child pointer, next sibling pointer}, tree = {root node pointer})
*/
// the No.3 method is recommended! because for a computer using the No.3 method to storage a tree is the same with the way to storage a binary tree! 
// if you use the No.3 method to express a tree, all kinds of problems of a tree can be changed to problems of a binary tree! 
/* if you want to express forest, just see the root node of the No.i tree as the next sibling of the root node of the No.(i-1) tree 
	and see the root node of the 1st tree as the root node of the forest. */
// so, all problems of a forest can be also changed to be problems of a binary tree, too!
/*
typedef struct node1
{
	elemType data;
	node1* parent;
}node1;
typedef struct
{
	node1 nodes[maxNum];
	int nodeNum;
}tree1;
*/
/*
typedef struct childNode
{
	int position;
	childNode* nextSibling;
}childNode;
typedef struct
{
	elemType data;
	childNode* firstChild;	
}node2;
typedef struct
{
	node2 nodes[maxNum];
	int root;
	int nodeNum;
}tree2;
*/

typedef struct node
{
	elemType data;
	node* firstChild, *nextSibling, *parent;
}node, *tree;

 
/*
initialize a tree(forest)
*/
void init(tree* t)
{
	(*t) = NULL;
} 

/*
check if a tree(forest) is empty
*/
void empty(tree t)
{
	if(!t)
		puts("empty tree or forest!");
	else
		puts("the tree or forest is not empty!");
}

/*
return the root of a tree(the first root of the first tree in a forest)
*/
elemType root(tree t)
{
	if(t)
		return t->data;
	else
	{
		puts("empty tree or forest!");
		exit(0);
	}
}

/*
return the parent node of a node of a tree(or a node of a tree in a forest)
*/
// look up a tree or forest upwards
// for a tree or forest the parent pointer of a node is different from that in a binary tree except for the first child node.
node* parent(node* n)
{
	if(n->parent)
		return n->parent;
	else
	{
		puts("this is a root node!");
		exit(0);
	}
}

/*
return the first child of a certain node of a tree(or the first child of a tree in a forest)
*/
// look up a tree or forest downwards
node* firstChild(node* n)
{
	if(n->firstChild)
		return n->firstChild;
	else
	{
		puts("this is a leaf node!");
		exit(0);
	}
}

/*
return the next sibling of a node of a tree(or the next sibling of a node of a tree in a forest)
mind that in a forest the root node of the No.i tree is seen as the next sibling or the root node of the No.(i-1) tree! 
*/
// look up a tree or forest horizontally
node* nextSibling(node* n)
{
	if(!n->nextSibling)
	{
		puts("this node is the last child of its parent node!");
		exit(0);
	}
	else
	{
		return n->nextSibling;
	}
}

/*
traversing a tree in parent->children mode is the same with traversing a binary tree in DLR mode
traversing a tree in children->parent mode is the same with traversing a binary tree in LDR mode
*/
void traverseTree(tree t, char mode)
{
	if(!t)
		return;
	// traverse a tree in parent->children mode
	if(mode == 'p')
	{
		printf("%c", t->data);
		traverseTree(t->firstChild, mode);
		traverseTree(t->nextSibling, mode);
	}
	// traverse a tree in children->parent mode
	else
	{
		traverseTree(t->firstChild, mode);
		printf("%c", t->data);
		traverseTree(t->nextSibling, mode);
	}	
} 

/*
traversing a forest in (No.i root->No.i tree->No.(i+1) root->...) mode is the same with traversing a binary tree in DLR mode
traversing a forest in (No.i tree->No.i root->No.(i+1) tree->...) mode is the same with traversing a binary tree in LDR mode
traversing a forest in (No.1 tree->No.2 tree->....->No.2 root->No.1 root) mode is the same with traversing a binary tree in LRD mode 
*/
void traverseForest(tree t, char mode)
{
	if(!t)
		return;
	// travserse in root->tree->next root&tree sequence
	if(mode == 'h')
	{
		printf("%c", t->data);
		traverseForest(t->firstChild, mode);
		traverseForest(t->nextSibling, mode);
	}
	// travserse in tree->root->next tree&root sequence
	else if(mode == 'c')
	{
		traverseForest(t->firstChild, mode);
		printf("%c", t->data);
		traverseForest(t->nextSibling, mode);
	}
	// travserse in tree->next tree->......->root->prior root sequence
	else
	{
		traverseForest(t->firstChild, mode);
		traverseForest(t->nextSibling, mode);
		printf("%c", t->data); 
	}
}

/*
count the leaf nodes of a tree(or a forest)
*/
int leafNodes(tree t)
{
	if(!t)
		return 0;
	else if(!t->firstChild)
		return 1+leafNodes(t->nextSibling);
	else
	{
		return leafNodes(t->firstChild)+leafNodes(t->nextSibling);
	}
}

/*
calculate the depth of a tree(or the depth of the deepest tree in a forest)
*/
int depth(tree t)
{
	if(!t)
		return 0;
	else
		return (depth(t->firstChild)+1)>depth(t->nextSibling)? depth(t->firstChild)+1 : depth(t->nextSibling);
}

// create a tree in parent->children sequence
void create(tree * t, node* parent)
{
	char data = getchar();
	if(data == '.')
		(*t) = NULL;
	else
	{
		(*t) = (node*)malloc(sizeof(node));
		if(!(*t))
		{
			puts("ERROR: memory run out!");
			exit(0);
		}
		(*t)->data = data;
		(*t)->parent = parent; 
		(*t)->firstChild = NULL;
		create(&((*t)->firstChild), *t);
		node*p = (*t)->firstChild;
		while(p)
		{
			p->nextSibling = NULL;
			create(&(p->nextSibling), *t);
			p = p->nextSibling;		
		}
	}
}
// create a forest (root->tree->next root&tree) sequence
void createForest(tree* t, node* parent)
{
	char data = getchar();
	if(data == '.')
		(*t) = NULL;
	else
	{
		(*t) = (node*)malloc(sizeof(node));
		if(!(*t))
		{
			puts("ERROR: memory run out!");
			exit(0);
		}
		(*t)->data = data;
		(*t)->parent = parent;
		(*t)->firstChild = NULL; 
		createForest(&((*t)->firstChild), *t);
		(*t)->nextSibling = NULL;
		createForest(&((*t)->nextSibling), parent);
	}
}

/*
show a tree
*/
// the leftmost node is the root node and the most top node is the leftmost leaf node
void showTree(tree t, int layer)
{
	if(!t)
		return;
	else
	{
		node* child = t->firstChild;
		showTree(child, layer+1);
		int k;
		for(k=1;k<=layer;printf("   "),k++);
		printf("%c\n", t->data);
		while(child)
		{
			showTree(child->nextSibling, layer+1);
			child = child->nextSibling;
		}
	}
}
// the leftmost nodes are root nodes and the most top node is the leftmost leaf node of the leftmost tree
void showForest(tree t, int layer)
{
	tree p = t;
	while(p)
	{
		showTree(p, layer);
		printf("\n");
		p = p->nextSibling;	
	}
}

/*
add a child tree into a certain node of a tree
*/
void add(node* n, tree child)
{
	if(!n->firstChild)
	{
		n->firstChild = child;
	}
	else
	{
		node* p = n->firstChild;
		while(p->nextSibling)
			p = p->nextSibling;
		p->nextSibling = child;
	}
	child->parent = n;
	child->nextSibling = NULL;	
}

/*
delete the NO.i child tree of the node p
*/
void del(node* p, int i)
{
	if(i < 1)
	{
		puts("index should no less than 1!");
		return;
	}
	if(i == 1)
		p->firstChild = p->firstChild->nextSibling;
	else
	{
		int k;
		node* child = p->firstChild;
		for(k=1;k<i-1;k++)
		{
			if(child->nextSibling)
				child = child->nextSibling;
			else
			{
				printf("index out of range, this node does not have No.%d child tree\n", i);
				return;
			}
		}
		if(child->nextSibling)
			child->nextSibling = child->nextSibling->nextSibling;
		else
			printf("index out of range, this node does not have the No.%d child tree\n", i);	
	}
}

/*
clear a tree or a forest
*/ 
int count = 0;
void clear(tree* t)
{
	if(*t == NULL)
		return;
	clear(&((*t)->firstChild));
	clear(&((*t)->nextSibling));
	free(*t);
	*t = NULL;
	count++;
}

// test
int main()
{
	puts("test tree input t, test forest input f:");
	char t = getchar();
	char buf;
	if(t == 't')
	{
		// clear buffer
		while((buf = getchar()) != '\n' && buf != EOF)
		{
			printf("%c", buf);
		}
		// tree
		tree* t = (tree*)malloc(sizeof(tree));
		//initialize a tree
		init(t);
		empty(*t);
		printf("the tree has %d leaf nodes and its depth is %d\n", leafNodes(*t), depth(*t));
		//create a tree
		puts("input a tree now, input in parent->children sequence");
		puts("if a node does not has a child input '.'");
		puts("if a node does not has a next sibling input '.' (except for the root node)");
		create(t, NULL);
		// clear buffer
		while((buf = getchar()) != '\n' && buf != EOF)
		{
			printf("%c", buf);
		}
		empty(*t);
		printf("the tree has %d leaf nodes and its depth is %d\n", leafNodes(*t), depth(*t));
		puts("\nthis is the tree you have created. the leftmost node is root node and the top node is the leftmost leaf node:\n");
		showTree(*t, 1);
		//traverse the tree
		puts("\ntraverse the tree in parent->children sequence");
		traverseTree(*t, 'p');
		puts("\ntraverse the tree in children->parent sequence");
		traverseTree(*t, 'c');
		//add a node into the tree
		tree* child = (tree*)malloc(sizeof(tree));
		puts("\ninput a child tree:");
		create(child, NULL);
		while((buf = getchar()) != '\n' && buf != EOF)
		{
			printf("%c", buf);
		}
		printf("the child tree has %d leaf nodes and its depth is %d\n", leafNodes(*child), depth(*child));
		puts("the child tree is:");
		showTree(*child, 1);
		add((*t)->firstChild, *child);
		puts("\nthe child tree has been added as the last child of the first child of the root node");
		puts("now the tree is:");
		showTree(*t, 1); 
		// delete a node
		del((*t)->firstChild, 1);
		puts("\nthe first child of the first child of the root node has been deleted!");
		showTree(*t, 1);
		// clear the tree
		count = 0;
		clear(t);
		printf("\ntree cleared! memory of %d nodes released!\n", count);
		empty(*t);		
	}
	else
	{
		// forest
		// clear buffer
		while((buf = getchar()) != '\n' && buf != EOF)
		{
			printf("%c", buf);
		}
		//initialize a forest
		tree* f = (tree*)malloc(sizeof(tree));
		init(f);
		empty(*f);
		printf("the forest has %d leaf nodes and its depth is %d\n", leafNodes(*f), depth(*f));
		//create a forest
		puts("input a forest now, input in root->tree->next root&tree sequence");
		puts("if a node does not has a child input '.'");
		puts("if a node does not has a next sibling input '.'");
		createForest(f, NULL);
		//clear buffer
		while((buf = getchar()) != '\n' && buf != EOF)
		{
			printf("%c", buf);
		}
		empty(*f);
		printf("the forest has %d leaf nodes and its depth is %d\n", leafNodes(*f), depth(*f));
		puts("\nthis is the forest you have created. the leftmost nodes are the root nodes and the top node of each tree is the leftmost leaf node of each tree:\n");
		showForest(*f, 1);
		//traverse the forest
		puts("\ntraverse the forest in root->tree->next root&tree sequence");
		traverseForest(*f, 'h');
		puts("\ntraverse the forest in tree->root->next tree&root sequence");
		traverseForest(*f, 'c');
		puts("\ntraverse the forest in tree->next tree->...->root->prior root sequence");
		traverseForest(*f, 't');
		//add a node into the forest
		tree* childt = (tree*)malloc(sizeof(tree));
		puts("\ninput a child tree. please input in parent->children sequence");
		puts("if a node does not has a child input '.'");
		puts("if a node does not has a next sibling input '.' (except for the root node)");
		create(childt, NULL);
		while((buf = getchar()) != '\n' && buf != EOF)
		{
			printf("%c", buf);
		}
		printf("the child tree has %d leaf nodes and its depth is %d\n", leafNodes(*childt), depth(*childt));
		puts("the child tree is:");
		showTree(*childt, 1);
		add((*f)->nextSibling, *childt);
		puts("\nthe child tree has been added as the last child of the second root node");
		puts("now the forest is:");
		showForest(*f, 1); 
		// delete a node
		del((*f)->nextSibling, 1);
		puts("\nthe first child of the second tree in this forest has been deleted!");
		showForest(*f, 1);
		// clear the forest
		count = 0;
		clear(f);
		printf("\ntree cleared! memory of %d nodes released!\n", count);
		empty(*f);		
	}

	return 0;
}
