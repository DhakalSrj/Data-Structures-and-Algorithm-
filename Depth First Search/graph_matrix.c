#include <stdlib.h>
#include <stdio.h>

#include "twoD_arrays.h"
#include "graph.h"

// a graph where edges are recorded as a matrix
struct struct_graph
{
   int undirected; // value 1 means it is undirected, value other than 1 means it is directed.
   int N;    // number of vertices
   int ** E;  // edges
};


// creates a graphPT with the specified number of vertices
graphPT newGraph(int N, int undirected)
{
   graphPT result = (graphPT)malloc(sizeof(*result));
   result->undirected = undirected;  
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

// deallocates the memory allocated to graph g.
void destroyGraph(graphPT g)
{
   if (g == NULL) return;
   free_2d(g->E, g->N, g->N);
   free(g);
}

// returns the number of vertices in g.
int numVertices(graphPT g)
{
   if (g == NULL) return 0;
   return g->N;
}

// Returns 1 if v is a valid number for a vertex of graph g.
// This function does not have a declaration in graphs.h because I am using it internally.
int isVertexValid(graphPT g, int v){
   if ((v < 0) || (v >= g->N))
   {
      return 0;   // invalid number for a vertex.
   }	
   
   return 1;
}

// returns 1 if the specified edge exists, 0 otherwise.
int edgeExists(graphPT g, int v1, int v2)
{
   if (g == NULL) return 0;
   if (isVertexValid(g, v1) == 0)
   {
      return 0;
   }
   if (isVertexValid(g, v2) == 0)
   {
      return 0;
   }

   return g->E[v1][v2];
}

// connects vertices v1 and v2 in the graph.
// returns 1 if successful, 0 if errors occurred.
int addEdge(graphPT g, int v1, int v2)
{
   if (g == NULL) return 0;
   if ( (isVertexValid(g, v1) == 0) || (isVertexValid(g, v2) == 0) )
   {
	  printf("Invalid vertex. No edge added.");
      return 0;
   }
   
   g->E[v1][v2] = 1;   // add edge from v1 to v2
   if (g->undirected ==1)    g->E[v2][v1] = 1;   // add edge from v2 to v1
   
   return 1;
}

// disconnects vertices v1 and v2 in the graph.
// returns 1 if successful, 0 if errors occurred.
int removeEdge(graphPT g, int v1, int v2)
{
   if (g == NULL) return 0;
   if (isVertexValid(g, v1) == 0)
   {
      return 0;
   }
   if (isVertexValid(g, v2) == 0)
   {
      return 0;
   }
   
   g->E[v1][v2] = 0;
   if (g->undirected ==1) g->E[v2][v1] = 0;
   
   return 1;
}


// returns an array with the neighbors of vertex v in graph g. 
// Sets res_size to the size of the returned array
int* vertexNeighbors(graphPT g, int v, int* res_size)  {
   if (g == NULL) return NULL;
   if (isVertexValid(g, v) == 0)   {
	   return NULL;
   }
   int count = 0;
   int i,n;
   for (n = 0; n < g->N; n++) {
      if (g->E[v][n] == 1)     count++;
   }
   (*res_size) = count;
   int* res = malloc(count * sizeof(int));
   i = 0;
   for (n = 0; n < g->N; n++) {
      if (g->E[v][n] == 1)     {
        res[i] = n;
        i++;
      }
   }
   
   return res;
}


// Prints the graph, namely the vertices, and the neighbors of each vertex.
void printGraph(graphPT g)
{
   if (g == NULL) 
   {
      printf("\nNULL graph\n\n");
      return;
   }
   printf("\n");
   int v, n;
   for (v = 0; v < g->N; v++)
   {
      printNeighbors(g, v);
   }
   printf("\n");
}


// Prints the neighbors of vertex v.
void printNeighbors(graphPT g, int v)
{
   if (g == NULL) 
   {
      printf("\nNULL graph\n\n");
      return;
   }
   if (isVertexValid(g, v) == 0)
   {
      printf("%d is not a vertex of the graph\n", v);
      return;
   }

   int i, neighbors_size;
   int* neighbors = vertexNeighbors(g, v, &neighbors_size);  // the returned result is malloc-ed
   printf("Vertex %d. Neighbors: ", v);
   
   for (i=0; i < neighbors_size; i++)
   {
      printf("%d ", neighbors[i]);
   }
   printf("\n");
   free(neighbors);
}

int** getAdjacencyMatrix(graphPT g)
{
	return g->E;
}

