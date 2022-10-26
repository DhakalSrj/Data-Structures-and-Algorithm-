/* 
 * Updated 2/17/2022 - Alexandra Stefan
 */
 //Suraj Dhakal
 //1001765507

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "list.h"


/* 
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library): 
gcc -g bucket_sort.c list.c -lm

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/

void print_array(int arr[], int N);

/* // recommended helper functions:
// function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP);
//  function to sort an array sing bucket sort
void bucket_sort(int arr[], int N)
*/

void print_array(int arr[], int N)
{
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

nodePT insert_sorted(nodePT L, nodePT newP)
 {
        if (L == NULL) 
        {
                L = newP;
        }
        else if (L->data > newP->data)
         {
                newP->next = L;
         }
        else 
        {
                nodePT tmp = L;
                while (tmp->next != NULL && tmp->next->data < newP->data)
                {
                        tmp = tmp->next;
                }
        	insert_node_after(tmp, newP);
        }
        return L;
}

void bucket_sort(int arr[], int N) 
{

        int minimum = arr[0], maximum = arr[0];   // initializing max and min values
        int i,a= 0;
        char array[50];
        int len =0;
        for (i = 0;i < N;++i)
        { 
                if (minimum > arr[i])
                {
                        minimum = arr[i];
                }
                if (maximum < arr[i])
                {
                        maximum = arr[i];
                 }
        }
        printf("Bucketsort: min = %d,max = %d,N = %d buckets\n", minimum,maximum,N);
        nodePT bucket[N+1];
        for(i=0;i<N;i++){
        	bucket[i] = NULL;
        }
        
        for (i=0;i<N;++i)
        {
        	int num= arr[i]-minimum;
               num *=N;
               int den= 1+maximum-minimum;
               int index = num/den;
               printf("\narr[%d]=             %d, idx=%d\n ",i, arr[i],index);
               nodePT newP = new_node(arr[i]);
               bucket[index] = insert_sorted(bucket[index], newP);
        }  
        int index = 0;
        i = 0;
        int sorted_arr[N];  //final array stored here
        nodePT j;
        for (i= 0;i < N;++i) 
        {
        
            for (j = bucket[i];j != NULL;j = j->next)
            {
                        sorted_arr[index] = j->data;
                        index++;
            }
        }
        for (a = 0;a < N;++a)
        {
		printf("\n-------List at index %d: \n List items :", a);
		len =0;
		for (i = 0;i < N;++i)
		{
		       int num= arr[i]-minimum;
		       num *=N;
		       int den= 1+maximum-minimum;
		       int index = num/den;
		       
		       if(index==a)
		       {
		       printf("%d    ",arr[i]);
		       len++;
		      	}
               
           }
            printf("\nLength  of the above list = %d", len);  
            
          }
              
       
        print_array(sorted_arr, N);
}



void run1()
{
	// Fill in your code here. You should not write everything in this function.  
	// Write some helper functions to separate the work.	
	printf("Enter the filename: ");
	char filename[50];
	scanf("%s", filename);
	FILE *openfiletoRead = fopen(filename, "r");
	if(openfiletoRead == NULL)
	{
		printf("Unable to open file to read");
		return;
	}
	int i=0;
    int size=0;
	int num = 0;
	fscanf(openfiletoRead,"%d", &size);
	int arrayNumber[size];
	while(fscanf(openfiletoRead,"%d", &num) == 1)
	{
		arrayNumber[i] = num;
		i++;
	}
        bucket_sort(arrayNumber,size);

	
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		char ch;
		scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer
 	} while (option == 1);

   return 0;
}
