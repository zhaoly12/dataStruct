#include <stdio.h>
#include <stdlib.h>
#include "linkedStack.h"

// an example of the usage of the stack 
// using stack to convert a decimal number into another count system
void example(int number, int countSys)
{
	linkStack l = (linkStack)malloc(sizeof(node));
	l->next = NULL;
	int no = number, re;
	int* e = (int*)malloc(sizeof(int));
	
	while(no != 0) 
	{
		re = no%countSys;
		no = no/countSys;
		push(l, re);
	}

	int result = 0, time = 1, flag = 1;
	while(flag == 1)
	{
		flag = pop(l, e);
		if(flag == 1)
		{
			printf("%d", *e);			
		}
	}
}

int main()
{
	puts("input a decimal number:");
	int number, countSys;
	scanf("%d", &number);
	puts("what kind of count system do you want to convert it into:");
	scanf("%d", &countSys);
	puts("the result is:");
	example(number, countSys);
	
	return 0;
}
