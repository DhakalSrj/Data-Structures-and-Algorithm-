//Suraj Dhakal
//1001765507

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <string.h>


int main()
{
	int i=0;
    int size=0;
	int num = 0;
	struct heap_struct heapS;
	printf("Enter the filename: ");
	char filename[50];
	scanf("%s", filename);
	//open file to read
	FILE *openfiletoRead = fopen(filename, "r");
	if(openfiletoRead == NULL)
	{
		printf("Unable to open file to read");
		printf("\n");
		return 0;
	}

	fscanf(openfiletoRead,"%d", &size);
	int *arr = (int*) malloc(sizeof(int)*size);
	while(i<size && fscanf(openfiletoRead,"%d", &num) == 1 )
	{
		arr[i] = num;
		i++;
	}

	heapS= make_heap(size,arr);
	print_heap(heapS);
	printf("\n");
	
	// read operation  length or series of opertaion length;
	int operationSize=0;
	fscanf(openfiletoRead,"%d", &operationSize);
	printf("Operation Size %d\n",operationSize);
    int sortedArraySize=0;
    int j=0;
	for(i=0;i<operationSize;i++)
	{
		char operation[10];
		fscanf(openfiletoRead,"%s", operation);
		printf("Operation number  %d, string: %s", i +1,operation);
		printf("\n");	

		if (operation[0]=='s'|| operation[0]=='S')
		{
			
			int * sortedArray = heap_sort(heapS,&sortedArraySize);
			printf("Sorted array: ");
			for (j=0;j<sortedArraySize;j++)
			{
				printf("%6d, ", sortedArray[j] );  
			}
			printf("\n");
			free(sortedArray);
			
		}
		else if (operation[0]=='*')
		{
			printf("removed:   %6d\n",poll(&heapS));
			print_heap(heapS);
			printf("\n");
		}

		else if (operation[0]=='p'|| operation[0]=='P' )
		{
			printf("peek:  %6d\n",peek(heapS));
			print_heap(heapS);
			printf("\n");
		}
		else 
		{
			int val = atoi(operation);
			printf("add:   %6d", val);
			add(&heapS,val);
			printf("\n");
		}
		print_heap(heapS);
		printf("\n");

	}

	destroy(&heapS);
	fclose(openfiletoRead);
	return 0;
}
