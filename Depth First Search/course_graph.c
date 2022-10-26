#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME_SIZE 31
#define MAX_FILE_SIZE 1001
#define WHITE 0
#define GRAY 1
#define BLACK 2

struct struct_graph
{
   int N;    // number of vertices
   int ** E;  // edges
};
typedef struct struct_graph *graphPT;

struct myStack
{
    int size;
    int *next;
    int top;
};

typedef struct myStack stack;

struct Color
{
    int size;
    int value;
    int *array;
};
typedef struct Color color; 


//function prototypes
int ** alloc_2d(int rows, int columns);
graphPT newGraph(int N);
void addEdge(graphPT *g, int v1, int v2);
int getVal(char **Nodes, char *current, int N);
void toGraph(char *name, graphPT *graph, char **nodes);
void getMatrix(graphPT graph);
void DFS(graphPT *graph, int *colors, stack *stk, int *E,int current, int *cycle);
void push(stack *stk, int N);
int pop(stack *stk);
void checkCycle(graphPT *graph,int *colors,int N, int *cycle, stack *stk);


int ** alloc_2d(int rows, int columns)
{
   int row, col;
   // allocate space to keep a pointer for each row
   int ** table = (int**)calloc(rows , sizeof(int *));

   // allocate the space for each row
   for (row = 0; row < rows; row++)
   {
      table[row] = (int*)calloc(columns , sizeof(int));
   }

   return table;
}

graphPT newGraph(int N)
{
   graphPT result = (graphPT)malloc(sizeof(*result));  
   result->N = N;
   result->E = alloc_2d(N,N);   
   
   // initialize adjacencies to signify that at present the
   // graph contains no edges.
   int i, j;
   for (i = 0; i < N; i++)
   {
      for (j = 0; j < N; j++)
      {
         result->E[i][j] = 0; // no edge from i to j
      }
   }
   
   return result;
}

void addEdge(graphPT *g, int v1, int v2)
{
   
   (*g)->E[v1][v2] = 1;   // add edge from v1 to v2
   
}
int getVal(char **Nodes, char *current, int N)
{
    int i = 0;
    for(i=0;i<N;i++)
	{
          if (strcmp(Nodes[i], current) == 0) 
		  {
			  return i;
		  }
	}
    
    return -1;
}

void toGraph(char *name, graphPT *graph, char **nodes)
{
    FILE *openFiletoRead = fopen(name, "r");
    int lineCount = MAX_FILE_SIZE;
    char line[lineCount];
    char *Token;
    int j,N = (*graph)->N;

	for( j =0 ;!feof(openFiletoRead);j++)
	{
        fgets(line, lineCount, openFiletoRead);
        Token = strtok(line, " \n");
        while (Token != NULL)
        {
            if (strcmp(nodes[j], Token) != 0)
            {
                addEdge(graph, getVal(nodes,Token, N), j);
            }
            Token = strtok(NULL, " \n");
        }
	}
    fclose(openFiletoRead);
}
void getMatrix(graphPT graph)
{
    int i;
    int j;
    printf("\n Adjacency matrix: \n");
    
    printf("   |");
    for (i = 0; i < graph->N; i++)
    {
        printf("  %d ", i);
    }
    printf("\n");

    for (i = 0; i < graph->N; i++)
    {
        printf("------");
    }
    printf("\n");

    for (i = 0; i < graph->N; i++)
    {
        printf("  %d| ", i);
        for (j = 0; j < graph->N; j++)
        {
            printf(" %d  ", (graph->E)[i][j]);
        }
        printf("\n");
    }
}

void DFS(graphPT *graph, int *colors, stack *stk, int *E,int current, int *cycle)
{
	colors[current] = GRAY;
	int neighbours[stk->size -1];
	int size =0 ;
	int num;
	for(num = 0 ; num < stk->size -1; num++)
	{
		if((*graph)->E[current][num] ==1)
		{
			neighbours[size]= num;
			size+=1;
		}
	}
	
	for( num =0 ; num < size ;num++)
	{
		int next = neighbours[num];
		//printf("I am Iteration: %d and next ittration wil be: %d\n", i,next);
		
		if(colors[next]==BLACK)
		{
			continue;
		}
		if(colors[next]==GRAY)
		{
			*cycle=1;
		}
		if (colors[next]==WHITE)
		{
			DFS(graph,colors,stk,(*graph)->E[next],next,cycle);
		}
		
		
	}
	colors[current] = BLACK;
	//push it into the stack
	//printf("Pushing %d to stack\n",i);
	push(stk,current);
}

void push(stack *stk, int N)
{
	
	if(stk->top == (stk->size-1))
	{
		printf("The stack is full");
		return;
	}
	
	stk->top+=1;
	stk->next[stk->top] = N;
	
}
		
int pop(stack *stk)
{
			
	int N;
	if(stk->top == -1)
	{
		printf("The Stack is Empty.\n");
		return -1;
	}
	else 
	{
		
		N = stk->next[stk->top];
		stk->top = stk->top - 1;
        return N;
	
	}
}
// N : Size
void checkCycle(graphPT *graph,int *colors,int N, int *cycle, stack *stk)
{
	for(int i=0;i<N;i++){
		colors[i]=0;
	}
	int iteration=0;
	for (int i = 0; i < N; i++)
	{
		if(colors[i] == 0)
		{
			DFS(graph,colors,stk,(*graph)->E[i],i,cycle);
		}
	}
}


int main()
{
	char fileName[MAX_FILENAME_SIZE];
	char fileLine[MAX_FILE_SIZE];
	int count = 0;
	int itr ;
	int N =0 ;
	int idx =0 ;
	int x,cycle = 0;
	char *token;
	char **nodes;
	graphPT graph;
	stack stk;
	color black, grey , white;
	
	printf("This program will read, from a file, a list of courses and their prerequisites and will print the list in which to take cousres.\n");
	printf("Enter filename: ");
	scanf("%s", fileName);
	
	FILE *openFiletoRead = fopen(fileName, "r");
	
	if(openFiletoRead == NULL )
	{
		printf("Could not open file: %s\n", fileName);
		printf("\nFailed to read from file. Program will terminate.\n\n");
		exit(0);
	}
	
	while(!feof(openFiletoRead))
	{
		fgets(fileLine, MAX_FILE_SIZE, openFiletoRead);
		count++;
	}
	
	fseek(openFiletoRead,0 ,SEEK_SET);
	nodes = (char **) malloc(sizeof(char *) * count);
	
	for(itr =0 ; itr<count ;itr++)
	{
		
		nodes[itr]= (char *)malloc (sizeof(char) * MAX_FILENAME_SIZE);
		
	}
	
	while(!feof(openFiletoRead))
	{
		fgets(fileLine,MAX_FILE_SIZE,openFiletoRead);
		token =strtok(fileLine," \n");
		strcpy(nodes[idx],token);
		idx++;
	}
	
	fclose(openFiletoRead);
	
	int num = count -1;
    if(num == 0 || num == -1)
	{
		printf("Invalid number");
		exit(0);
	}
	
	
	printf("Number of vertices in built graph: N = %d \n\n", num);
	printf("Vertex - coursename correspondance \n\n");
	
	for(itr=0;itr<num;itr++)
	{
		printf("  %d    -   %s\n",itr,nodes[itr]);
	}
	
	//graph generator function call
	graph = newGraph(num);
	
	//file to graph function call
	toGraph(fileName, &graph,nodes);
	
	//adjacency matrix function call
	getMatrix(graph);
	
	//create stack
	stk.size = num + 1;
	stk.next = (int *)malloc(sizeof(int) * stk.size);
	stk.top = -1;
	
	
	
	
	int * colors =(int *)malloc(sizeof(int) *num);
	
	checkCycle(&graph,colors,num,&cycle,&stk);
	
	
	if(cycle)
	{
		printf("There was at least one cycle. There is no possible ordering of the courses.\n");
		return 0;
	}
	else
	{
		printf("\n\nOrder in which to take courses: \n\n");
		for(itr =0 ; itr < num ;itr++)
		{
			int p = pop(&stk);
			printf("%d. - %s (corresponds to graph vertex %d)\n", itr+1, nodes[p], p);
		}
	}
	
	
	//deallocating allocated memories to avoid memory leaks 

	free(stk.next);
	
	for(itr =0 ; itr <graph ->N ;itr++)
	{
		free((graph->E)[itr]);
		free(nodes[itr]);
	}
	
	free(graph->E);
	free(graph);
	free(nodes);
	
	return 0;
}