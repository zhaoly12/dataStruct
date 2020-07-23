#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
use an array to storage a symmetric matrix
*/
void  symMat()
{
	puts("please input the length of the symmetric matrix:");
	int n;
	scanf("%d", &n);
	if(n < 1)
	{
		puts("the length should no less than 1!");
		return;
	}
	// get members
	int i, j=1, k;
	int num[(n+1)*n/2];
	for(i=1;i<=(n+1)*n/2;)
	{
		for(;j<=n;j++)
		{
			for(k=1;k<=j;k++)
			{
				printf("please input a(%d,%d)\n", j,k);
				scanf("%d", &num[i-1]);
				i++;		
			}
		}
	}
	// display
	// the a(x,y) is the No.no of the array num[(n+1)*n/2], which no = x*(x-1)/2 + y-1 (y<=x)   y*(y-1)/2 + x-1 (x<y)
	puts("the symmetric matrix is:");
	int x, y, no;
	for(x=1;x<=n;x++)
	{
		for(y=1;y<=n;y++)
		{
			if(y <= x)
				no = x*(x-1)/2+y-1;
			else
				no = y*(y-1)/2+x-1;
			printf("%d ", num[no]);
		}
		printf("\n");
	}
}

/*
use a struct to storage a sparse matrix
*/
typedef struct
{
	int data;
	int row;
	int column;	
} elem;

typedef struct
{
	elem data[101];
	int row, column, num;
} matrix;

/*
transpose a matrix
*/
void tranMat(matrix A, matrix* B)
{
	B->num = A.num;
	B->column = A.row;
	B->row = A.column;
	int count=1, col, i;
	for(col=1;col<=A.column;col++)
	{
		for(i=1;i<=A.num;i++)
		{
			if(A.data[i].column == col)
			{
				B->data[count].data = A.data[i].data;
				B->data[count].column = A.data[i].row;
				B->data[count].row = A.data[i].column; 
				count++;	
			}
		}
	}
}

/*
display a matrix
*/
void display(matrix mat)
{
	puts("the sparse matrix is:");
	int x, y;
	int count = 1;
	for(x=1;x<=mat.row;x++)
	{
		for(y=1;y<=mat.column;y++)
		{
			if(count > mat.num)
			{
				printf("%d",0);
				continue;
			}
			if((mat.data[count].row == x) && (mat.data[count].column == y))
			{
				printf("%d", mat.data[count].data);
				count++;
			}
			else
			{
				printf("%d",0);
			}
		}
		printf("\n");	
	}
}


void sparMat()
{	
	matrix mat;
	puts("please input the number of the rows of the matrix:");
	scanf("%d", &(mat.row));
	if(mat.row < 1)
	{
		puts("the number of rows should no less than 1!");
		return;
	}
	puts("please input the number of the columns of the matrix:");
	scanf("%d", &(mat.column));
	if(mat.column < 1)
	{
		puts("the number of columns should no less than 1!");
		return;
	}
	puts("input how many elements that are not equal to 0");
	scanf("%d", &(mat.num));
	if(mat.num > 100)
	{
		puts("numbers of the elements that not equal to 0 should no more than 100");
		return;
	}
	// get all the elements of the sparse matrix
	int count = 1;
	while(count <= mat.num)
	{
		puts("please input the row index of the element");
		scanf("%d", &(mat.data[count].row));
		if(mat.data[count].row > mat.row)
		{
			puts("index error");
			return;
		}
		puts("please input the column index of the element");
		scanf("%d", &(mat.data[count].column));
		if(mat.data[count].column > mat.column)
		{
			puts("index error");
			return;
		}
		puts("please input the column index of the element");
		scanf("%d", &(mat.data[count].data));
		count++;
	}
	// display
	display(mat);
	// transpose matrix
	matrix * matT = (matrix*)malloc(sizeof(matrix));
	tranMat(mat, matT);
	display(*matT);
}


//test
int main()
{
	// symmetric matrix
	symMat();
	// sporse matrix
	sparMat();
	
	system("pause");
	
	return 0;
}

