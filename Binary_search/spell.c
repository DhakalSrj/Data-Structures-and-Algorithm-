//Suraj Dhakal  - 1001765507

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "spell.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(D*T*(MAX_LEN*2))


Worst case to do an unsuccessful binary search in a dictionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(lg(D)*MAX_LEN)
*/

/*function prototypes */

int min(int a ,int b ,int c);
int edit_distance_helper(char * first_string, char * second_string);
void sort(char arr[][200], int *sz , int printVal);
char *length(char *Token, char arr[][200], int *sz, char *inputVal);
int binary_search(char *end ,char arr[][200], int printVal, int *sz);
void inFile(char *check, char arr[][200], int printVal, char *filename, int *sz);
int edit_distance(char * first_string, char * second_string, int print_table);
void spell_check(char * testname, char * dictname, int printOn);
void swap(char *a, char *b);

/*  helper functions */


void swap(char *a,char *b) {
	char temp[200];
	
	strcpy(temp, a);
	strcpy(a,b);
	strcpy(b,temp);
}
//returns the minimum
int min(int a ,int b ,int c)
{
	int val;
	
	val = (a< b)? a : b;
	
	if (val >=c)
	{
		val = c;
	}
	
	return val;
}
//similar function to edit_distance that just returns the table array 
int edit_distance_helper(char * first_string, char * second_string)
{
	int length_first = strlen(first_string);
	int length_second= strlen(second_string);
	int tableArray[length_second+ 1][length_first + 1];
	int i,j;
	
	for(i = 0; i <= length_first; i++)
	{
		tableArray[0][i]=i;
	}
	for(j = 0; j<= length_second; j++)
	{
		tableArray[j][0]=j;
	}
	
	for( j=0 ; j<=length_second; j++)
	{
		for(i=0; i<=length_first; i++)
		{
			if(second_string[j] != first_string[i])
			{
				tableArray[j+1][i+1] = 1 + min(tableArray[j][i+1],tableArray[j+1][i],tableArray[j][i]);
			}
			else
			{
				tableArray[j+1][i+1] = tableArray[j][i];
			}
		}
	}
	return tableArray[length_second][length_first];
}
//sort function to sort the dictionary words alphabetically
void sort(char arr[][200], int *sz , int printVal)
{
	char array[200];
	
	for(int p=0; p < *sz ; p++)
	{
		for(int q= p + 1 ;q< *sz; q++)
		{
			if(strcmp(arr[p],arr[q])>0)
			{
				swap(arr[p],arr[q]);
				 
			}
		}
	}
	
	if(printVal ==1)
	{
		 printf(" Sorted Dictionary (alphabetical order) : \n");
		 
		 for( int i=0; i < *sz ; i++)
		 {
			 printf("%d. %s\n", i , arr[i]);
		 }
	}

}

//the funcilon calculates the distance 

char *length(char *Token, char arr[][200], int *sz, char *inputVal)
{
	printf("-1 - type correction\n");
    printf(" 0 - leave word as is (do not fix spelling)\n");
	
	int inc=1, array[*sz], min, picked;
	int d;
	
	int value1= edit_distance_helper(Token,arr[0]);
	
	array[0] = value1;
	
	for (d = 1 ;d < *sz ; d++)
	{
		int value2= edit_distance_helper(Token,arr[d]);
		array[d] = value2;
		if(value1 < value2)
		{
			min = value1 ;
		}
		else
		{
			min =value2 ;
		}
		
		 value1 = min ;
	}
	printf("     Minimum distance: %2d (calculated edit distances: %2d)\n", min, *sz);
    printf("     Words giving minimum distance: \n");
	
	for (int i = 0; i < *sz; i++)
    {
        if (array[i] == min)
        {
            printf(" %d - %s\n", inc, arr[i]);
            array[inc- 1] = i;
            inc++;
        }
    }
   
    printf("Please enter your choice: ");
	do{
		 scanf("%d", &picked);
		 if(picked>= inc){
			 printf("Invalid Number. Please enter valid number: ");
		 }
	}
	while(picked>= inc);
   
    
    if (picked == -1)
    {
        printf("Please enter the correct word: ");
        scanf("%s", inputVal);
        return inputVal;
    }
    else if (picked == 0)
	{
        return Token;
	}
    else
	{
        return arr[array[picked - 1]];
	}
}
//to perform binary search
int binary_search(char *end ,char arr[][200], int printVal, int *sz)
{
		int size =*sz;
		int length = strlen(end);
		int val= 0 ;
		int initial= size-1,final=0, inBtwn;
		char array[length +1];
		
		if (printVal == 1)
		{
        printf("\nBinary search for: %s\n", end);
		}
		
		for (val= 0; val < length; val++)
		{
			array[val] = tolower(end[val]);
		}

		array[val] = '\0';
		val = 0;
		while (final <= initial)
		{
			inBtwn= (final + initial)/ 2;
			val++;

			if (printVal == 1)
			{
				printf("dict[%d]= %s\n", inBtwn, arr[inBtwn]);
			}

			if (strcmp(array, arr[inBtwn]) == 0)
			{
				printf("\n\n---->|%s|(words compared when searching): %d\n", end, val);
				
				if (printVal == 1)
				{
					printf("     Found!\n");
				}
				return 1;
			}

			else if (strcmp(array, arr[inBtwn]) > 0)
			{
				final = inBtwn + 1;
			}
			else if (strcmp(array, arr[inBtwn]) < 0)
			{
				initial = inBtwn - 1;
			}
		}

		if (printVal == 1 && final > initial)
		{
			printf("Not Found!");
		}

		printf("\n\n---->|%s|(words compared when searching): %d\n", end, val);

		return 0;
}

void inFile(char *check, char arr[][200], int printVal, char *filename, int *sz)
{
	int arraysize = 200;
	char array[arraysize];
	char val;
	int sum= 0 , start = 0; 
	
	FILE *openfiletoRead = fopen(check, "r");
	if(openfiletoRead == NULL)
	{
		printf("Unable to open file to read");
		return;
	}
	
	FILE *openfiletoWrite= fopen(filename ,"w");
	
	while(!feof(openfiletoRead))
	{
		fscanf(openfiletoRead, "%c",&val);
		if (feof(openfiletoRead) || val == ' ' || val == '.' || val == '?' || val == ',' || val == '!')
        {
            if (sum != 0)
            {
                array[sum] = '\0';
                start = binary_search(array, arr, printVal, sz);

                if (start)
                {
                    printf("     - OK\n\n");
                    fprintf(openfiletoWrite, "%s", array);
                }
                else
                {
                    char *new = (char *)malloc(sizeof(char) * 200);
                    char *find_length = length(array, arr, sz, new);
                    fprintf(openfiletoWrite, "%s", find_length);
                    free(new);
                }
            }
            sum = 0;
            if (!feof(openfiletoRead))
			{
                fprintf(openfiletoWrite, "%c", val);
			}
        }
        else
        {
            array[sum] = val;
            sum++;
        }
    }

    printf("\n");

    fclose(openfiletoWrite);
    fclose(openfiletoRead);
}
/*
Parameters:
first_string - pointer to the first string (displayed vertical in the table)
second_string - pointer to the second string (displayed horizontal in the table)
print_table - If 1, the table with the calculations for the edit distance will be printed.
              If 0 (or any value other than 1)it will not print the table
(See sample run)
Return:  the value of the edit distance (e.g. 3)
*/
int edit_distance(char * first_string, char * second_string, int print_table)
{
	int length_first = strlen(first_string);
	int length_second= strlen(second_string);
	int tableArray[length_second+ 1][length_first + 1];
	int i,j,x;
	
	for(j = 0; j<= length_second; j++)
	{
		tableArray[j][0]=j;
	}
	
	for(i = 0; i <= length_first; i++)
	{
		tableArray[0][i]=i;
	}
	
	for( j=0 ; j<=length_second; j++)
	{
		for(i=0; i<=length_first; i++)
		{
			if(second_string[j] != first_string[i])
			{
				tableArray[j+1][i+1] = 1 + min(tableArray[j][i+1],tableArray[j+1][i],tableArray[j][i]);
			}
			else
			{
				tableArray[j+1][i+1] = tableArray[j][i];
			}
		}
	}
	
	for (x = 0; x < length_second + 2; x++)
	{
		if(x == 0 || x == 1)
		{
			printf("   |");
		}
		else
		{
			printf("  %c|",second_string[x-2]);
		}
	}
	printf("\n");
	
	for (x = 0; x < length_second + 2; x++)
	{
		printf("----");
	}
	printf("\n");
	
	for( i=0; i<=length_first ;i++)
	{
		if(i==0)
		{
			printf("   |");
		}
		else
		{			
			printf("  %c|", first_string[i - 1]);
		}
		for(j=0; j<= length_second;j++)
		{
			printf("%3d|" ,tableArray[j][i]);
		}
		printf("\n");
		for(x=0 ;x< length_second+2;x++)
		{
			printf("----");
		}
		printf("\n");
	}
	
	return tableArray[length_second][length_first];
}

/*
Parameters:
testname - string containing the name of the file with the paragraph to spell check, includes .txt e.g. "text1.txt" 
dictname - name of file with dictionary words. Includes .txt, e.g. "dsmall.txt"
printOn - If 1 it will print EXTRA debugging/tracing information (in addition to what it prints when 0):
			 dictionary as read from the file	
			 dictionary AFTER sorting in lexicographical order
			 for every word searched in the dictionary using BINARY SEARCH shows all the "probe" words and their indices indices
			 See sample run.
	      If 0 (or anything other than 1) does not print the above information, but still prints the number of probes.
		     See sample run.
*/
void spell_check(char * testname, char * dictname, int printOn)
{
	
	char line[200];
	char *name;
	char *new="\n";
	int distance;
	char filename[200]="out_";
	strcat(filename,testname);
	
	printf("Corrected output filename: %s \n", filename);
    printf("\n");
    printf("Loading the dictionary file: %s \n", dictname);
    printf("\n");
	
	FILE *openfiletoRead= fopen(dictname, "r");
	
	if(openfiletoRead ==NULL)
	{
		printf("Invalid Filename.");
		return;
	}
	
	fgets(line, sizeof(line), openfiletoRead);
	distance = atoi(strtok(line, new));
	int value = 0;
	
	char array[distance][200];

	while (fgets(line, sizeof(line), openfiletoRead))
	{
		name= strtok(line, new);
		strcpy(array[value], name);
		value++;
	}

	printf("Dictionary has size: %5d \n", distance);

	if (printOn == 1)
	{
		printf(" Original dictionary: \n");
		for (int i = 0; i < value; i++)
		{
			printf("%d. %s\n", i, array[i]);
		}
	}
	printf("\n");
	fclose(openfiletoRead);

	sort(array, &distance, printOn);
	inFile(testname, array, printOn, filename, &distance);
}


