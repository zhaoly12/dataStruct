#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define elemType int

/*
define a orthogonal list
*/
typedef struct node
{
	int row, col;
	elemType value;
	node* right, * down;
} node, *oLink;

// use a orthogonal list to show a matrix
typedef struct
{
	oLink *rhead, *chead;
	int row, col, num;
} mat; 

// initialize a mat
void init(mat* m)
{
	int row, col, num;
	puts("input the number of rows:");
	scanf("%d", &row);
	if(row < 1)
	{
		puts("ERROR: number of rows should no less than 1!");
		return;
	}
	puts("input the number of columns:");
	scanf("%d", &col);
	if(col < 1)
	{
		puts("ERROR: number of columns should no less than 1!");
		return;
	}
	puts("input the number of elements that not equal to 0:");
	scanf("%d", &num);
	if(num < 0)
	{
		puts("ERROR: number of elements that not equal to 0 should no less than 0!");
		return;
	}

	m->rhead = (oLink*)malloc((row+1)*sizeof(oLink));
	if(! m->rhead)
	{
		puts("ERROR: memory not enough!");
		return;
	}
	int i;
	// mind that the start index is 1!
	for(i=1;i<=row;i++)
	{
		m->rhead[i] = NULL;
	}
	m->chead = (oLink*)malloc((col+1)*sizeof(oLink));
	if(! m->chead)
	{
		puts("ERROR: memory not enough!");
		return;
	}
	// mind that the start index is 1!
	for(i=1;i<=col;i++)
	{
		m->chead[i] = NULL;
	}
	
	m->col = col;
	m->num = num;
	m->row = row;
}

// get all values of a matrix
void getValue(mat* m)
{
	int count = 1;
	for(;count<=m->num;count++)
	{
		// get a node
		node *n = (node*)malloc(sizeof(node));
		n->right = NULL;
		n->down = NULL;
		if(!n)
		{
			puts("ERROR:memory run out!\n");
			return;
		}
		puts("input the row index:");
		scanf("%d", &(n->row));
		if((n->row > m->row)||(n->row < 1))
		{
			puts("ERROR: index error");
			return;
		}
		puts("input the column index:");
		scanf("%d", &(n->col));
		if((n->col > m->col)||(n->col < 1))
		{
			puts("ERROR: index error");
			return;
		}		
		puts("input the value:");
		scanf("%d",&(n->value));
		
		// insert the node into matrix
		if(!(m->rhead[n->row]))
		{
			// insert the first element of this row
			m->rhead[n->row] = n;	
		}
		else
		{
			node* pt = m->rhead[n->row];
			// if the row index of the node is smaller the row head pointer should be changed!
			if(m->rhead[n->row]->col > n->col)
			{
				node* nt = m->rhead[n->row];
				m->rhead[n->row] = n;
				n->right = nt;
			} 
			else
			{
				// find the row position
				while(pt->right)
				{
					if(pt->right->col < n->col)
						pt = pt->right;
					else
						break;
				}
				n->right = pt->right;
				pt->right = n;			
			}	
		}

		if(!(m->chead[n->col]))
		{
			// insert the first element of this column
			m->chead[n->col] = n;		
		}
		else
		{
			node* pt = m->chead[n->col];
			// if the row index of the node is smaller the row head pointer should be changed!
			if(m->chead[n->col]->row > n->row)
			{
				node* nt = m->chead[n->col];
				m->chead[n->col] = n;
				n->down = nt;
			}
			else
			{
				// find the column position
				while(pt->down)
				{
					if(pt->down->row < n->row)
						pt = pt->down;
					else
						break;
				}
				n->down = pt->down;
				pt->down = n;	
			} 
		}
	}
}

/*
display a matrix
*/
void display(mat* m)
{
	int i, start, empty;
	// display line by line
	for(i=1;i<=m->row;i++)
	{
		node* p = m->rhead[i];
		// p == NULL means that elements in this line are all zeros 
		if(!p)
		{
			int j;
			for(j=1;j<=m->col;j++)
			{
				printf("0 ");	
			}
			printf("\n");
			continue;
		}
		start = m->rhead[i]->col;
		while(p)
		{
			// zeros should be filled between two elements which not equal to 0 
			for(empty=1;empty<start;empty++)
			{
				printf("0 ");
			}			
			printf("%d ",p->value);
			if(p->right)
				start = p->right->col - p->col;
			else
			{
				// if the final element is not the last one of its line zeros should be filled after it
				start = m->col - p->col;
				for(empty=1;empty<=start;empty++)
				{
					printf("0 ");
				}			
			}			
			p = p->right;
		}
		// switch to the next line
		printf("\n");
	}
}

//test
int main()
{
	mat * m = (mat*)malloc(sizeof(mat));
	if(!m)
	{
		puts("ERROR: memory run out!");
		return -1;
	}
	// init
	init(m);
	// get values
	getValue(m);
	puts("the matrix you have typed in is:");
	//display
	display(m);
	
	system("pause");
	
	return 0;
}

