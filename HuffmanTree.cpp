#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// define the number of leaf nodes and the number of all nodes
#define N 20 
#define M 2*N-1

/*
define a Huffman tree
*/
typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
} node, HuffmanTree[M+1];

//  select two nodes with the least weight from nodes whose parent is 0
void select(HuffmanTree ht, int n, int* p1, int* p2)
{
	int i;
	int j = 0;
	int indices[2*n-1];
	for(i=1;i<=2*n-1;i++)
		indices[i] = 0;
	for(i=1;i<=2*n-1;i++)
	{
		if(ht[i].parent == 0 && ht[i].weight != 0)
		{
			indices[j] = i;
			j++;	
		}
	}
	
	int min1 = 0, min2 = 1;
	j = 2;
	while(indices[j] != 0)
	{
		if(ht[indices[min2]].weight < ht[indices[min1]].weight) 
		{
			int tmp = min1;
			min1 = min2;
			min2 = tmp;
		}
		if(ht[indices[j]].weight < ht[indices[min2]].weight)
			min2 = j;
		j++;
	}
	*p1 = indices[min1];
	*p2 = indices[min2];
}

// create a Huffman tree
void createHT(HuffmanTree ht, int w[N], int n)
{
	// initialize the leaf nodes
	int i;
	for(i=1;i<=n;i++)
		ht[i] = {w[i-1], 0, 0, 0};
	// initialize other nodes
	for(;i<=2*n-1;i++)
		ht[i] = {0, 0, 0, 0};
	// create
	int s1=1, s2=1;
	for(i=n+1;i<=2*n-1;i++)
	{
		select(ht, n, &s1, &s2);// select two nodes with the least weight from nodes whose parent is 0
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		ht[s1].parent = i;
		ht[s2].parent = i;
		ht[i].lchild = s1;
		ht[i].rchild = s2;
	}
}

// show a Huffman tree
void showHT(HuffmanTree ht, int i, int layer)
{
	if(i == 0)
		return;
	showHT(ht, ht[i].rchild, layer+1);
	int j;
	for(j=0;j<layer;printf("      "),j++);
	printf("%d\n", ht[i].weight);
	showHT(ht, ht[i].lchild, layer+1);
}

// HuffmanCode
typedef char** HuffmanCode;
// the route from the root node to a leaf node 0 stands for going left and 1 stands for going right
void createHC(HuffmanTree ht, int n, HuffmanCode hCode)
{
	register int i,p,k;
	char* code = (char*)malloc(n*sizeof(char)); 
	if(!code)
	{
		puts("ERROR: memory run out!");
		return;
	}
	code[n-1] = '\0';
	for(i=1;i<=n;i++)
	{
		k = n-1;
		p = i;
		while(ht[p].parent != 0)
		{
			k--;
			if(p == ht[ht[p].parent].lchild)
				code[k] = '0';
			else
				code[k] = '1';
			p = ht[p].parent;	
		}
		hCode[i-1] = (char*)malloc((n-k)*sizeof(char));
		if(!hCode[i-1])
		{
			puts("ERROR: memory run out!");
			return;
		}
		strcpy(hCode[i-1], &code[k]);
	}
	free(code);
}

// show Huffman Codes
void showHC(HuffmanCode hCode, int n)
{
	register int k;
	for(k=0;k<n;k++)
	{
		printf("No.%d leaf node's Huffman Code is : %s\n", k+1, hCode[k]);
	}
}

// test
int main()
{
	HuffmanTree ht;
	ht[0] = {0, 0, 0, 0};
	int w[N];
	int i;
	puts("weights are as follows:");
	srand((unsigned)time(0));
	for(i=0;i<N;i++)
	{
		w[i] = rand()%10+1;
		printf(" %d", w[i]);
	}
	printf("\n");
	// create a huffman tree
	createHT(ht, w, N);
	puts("Huffman tree created!");
	puts("the leftmost node is the root node and the top node is the rightmost leaf node:");
	showHT(ht, M, 1);	
	
	// Huffman Code
	HuffmanCode hCode = (char**)malloc(N*sizeof(char*));
	createHC(ht, N, hCode);
	puts("\nHuffman Codes created!\n");
	showHC(hCode, N);
	
	return 0;	
} 
 

