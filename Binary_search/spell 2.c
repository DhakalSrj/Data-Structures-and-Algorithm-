#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "spell.h"

#define MAX_LEN 101

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(D(MAX_LEN))


Worst case to do an unsuccessful binary search in a dictionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(log(D))
*/


/* You can write helper functions here */

void char_repetition(char c, int reps) {
	printf("\n");
	for (int i = 0; i < reps; i++){
		printf("%c", c);
	}
	printf("\n");
}

void print_Table(int rows, int cols, int table[rows][cols], char * first_string, char * second_string) {
	printf("   |   |");
	for (int i = 0; i < strlen(second_string); ++i) 
		printf("%3c|", second_string[i]); 

	char_repetition('-', 4 * (cols + 1));
	
	for (int i = 0; i < rows; ++i) {
		printf("%3c|", i ? first_string[i-1] : ' ');
		for (int j = 0; j < cols; ++j) {
			printf("%3d|", table[i][j]);
		}
		char_repetition('-', 4 * (cols + 1));
	}
}

int compare(const void *a, const void *b) {
  return strcmp((char *)a, (char *)b);
}

int find_string(char array[][MAX_LEN], int end, char *text, int printOn) {
	int counter = 0;
	int response = -1;
	int start = 0;
	int mid_point = 0;
	int check = 0;

	printf("Binary search for: %s\n", text);

	while (start <= end) {
		counter++;
		mid_point = (end + start) / 2;

		if (printOn){
			printf("dict[%d] = %s\n", mid_point, array[mid_point]);	
		} 
		
		check = strcmp(array[mid_point], text);
		if (check == 0) {
			response = mid_point;
			break;
		}
		if (check < 0) {
			start = mid_point + 1;
		}else {
			end = mid_point - 1;
		}
	}
	printf("%s\nSearch ran %d times\n", response == -1 ? "Not found" : "Found", counter);
    return response;
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
int edit_distance(char * first_string, char * second_string, int print_table){
	int len1 = strlen(first_string) + 1;
	int len2 = strlen(second_string) + 1;

	int table[len1][len2];

	for (int i = 0; i < len2; ++i) table[0][i] = i;
	for (int j = 0; j < len1; ++j) table[j][0] = j;	
	
	for (int i = 1; i < len1; ++i) {
		for (int j = 1; j < len2; ++j) {
			int minimum = table[i-1][j-1];

			if (first_string[i-1] != second_string[j-1]) {
				if (table[i][j-1] < minimum)
					minimum = table[i][j-1];
				if (table[i-1][j] < minimum)
					minimum = table[i-1][j];
				++minimum;
			}
			table[i][j] = minimum;
		}
	}	

	if (print_table == 1)
		print_Table(len1, len2, table, first_string, second_string);

	return table[len1 - 1][len2 - 1];
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
void spell_check(char * testname, char * dictname, int printOn){
	int pages = 0;
	FILE *dictionary = fopen(dictname, "r");
	FILE *test_file = fopen(testname, "r");
	char delimeters[7] = ", .!?";
	char word_format[32];
	char words[MAX_LEN];

	if((dictionary == NULL) || (test_file == NULL)){
		printf("File could not be opened\n");
		exit(0);
	}

	char out_file[strlen(testname) + 5]; 
	sprintf(out_file, "out_%s", testname);
	FILE *output = fopen(out_file, "w");

	fscanf(dictionary, "%d", &pages);

	printf("\nLoading the dictionary file: ");
	for (int i = 0; i < strlen(dictname); ++i){
		printf("%c", dictname[i]);
	}
	printf("\n");
	printf("\nDictionary has size: %d\n", pages);

	char dict[pages][MAX_LEN];
	for (int i = 0; i < pages; ++i) {
		fscanf(dictionary, "%s", dict[i]);
	}

	if (printOn) {
		printf("\nOriginal dictionary:\n");
		for (int i = 0; i < pages; ++i){
			printf("%d. %s\n",i, dict[i]);
		}
	}

	qsort(dict, pages, MAX_LEN * sizeof(char), compare);

	if (printOn) {
		printf("\nSorted Dictionary (alphabetical order) : \n");
		for (int i = 0; i < pages; ++i){
			printf("%d. %s\n",i, dict[i]);
		}
	}

	sprintf(word_format, "%%%ds", MAX_LEN-1);

	while(fscanf(test_file, word_format, words) == 1) {
		char delim;
		char *brk = words;

		while (brk != NULL){
            char *word = brk;
            brk = strpbrk(brk, delimeters);

			if (brk) {
                delim = *brk;
                *brk = 0;
            }            

            if (word != brk) {
    			printf("---> |%s|\n\n", word);

    			char lower[strlen(word) + 1];
    			strcpy(lower, word);
    			for (int i = 0; i < strlen(lower); ++i){
    				lower[i] = tolower(lower[i]);
    			}

    			if (find_string(dict, pages - 1, lower, printOn) == -1){
    				word = word;
    			}
    			else {
    				printf("\t - OK\n");
    			}
    			fprintf(output, "%s", word);
            }
			if (brk) {
                fprintf(output, "%c", delim);
                ++brk;
            }
		};
		fputs(" ", output);
	}

	fclose(dictionary);
	fclose(test_file);
	fclose(output);
}