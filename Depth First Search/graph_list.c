/*
Alexandra Stefan
Updated 4/27/2021
3:00pm
*/

#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "twoD_arrays.h"
#include "graph.h"


// a graph where edges are recorded as a linked list for each vertex.
struct struct_graph
{
   int undirected; // value 1 means it is undirected, value other than 1 means it is directed.	
   int N;
   nodePT * E;  //we will use E as an array of list
};


nodePT delete_by_data(nodePT L, int data){

   if (L==NULL) return NULL;
   
   nodePT curr = L->next;
   nodePT prev = L;
   
   // Special case when node to be removed is at the front
   if (prev->data == data) {
	   // it would be good to set: prev->next = NULL;
	   free(prev);
	   return curr;
   }
   
   // case when node to be removed is second or later (or none)
   while (curr != NULL) {
      if (curr->data == data)
      {
		prev->next = curr->next;
		free(curr);
        break;
      }
      else {
         prev = curr;
         curr=curr->next;
      }
   }
   return L;
}

// creates a graph with the specified number of vertices
graphPT newGraph(int N, int undirected)
{
   graphPT result = (graphPT)malloc(sizeof(*result));  // allocate space for a graph_struct
   result->undirected = undirected;  
   result->N = N;
   result->E = (nodePT*)malloc(N * sizeof(nodePT));  // allocate space for N objects of type nodePT (i.e memory adresses)
   // We did NOT allocate any space for any actual node yet.
   
   
   /* For each vertex:
   Use new_list to do the following. This description is for the case where lists are represenetd using dummy nodes:
     - allocate memory for a node struct  (this will be the dummy node)
	 - set the fields in that struct (to corerspond to teh conventions for dummy nodes).
	 - return the memory address of this node. 
   Update the result->E[i] to point to that memory.
   */
   int i;
   for (i = 0; i < N; i++)
   {
      result->E[i] = NULL;  
   }
   
   return result;
}

// deallocates the memory allocated to graph g.
void destroyGraph(graphPT g)
{
   if (g == NULL) return;
   
   int i;
   for (i = 0; i < g->N; i++)
   {
      destroy_list(g->E[i]); // free the actual list (including nodes) corresponding to node i
   }
   free(g->E);  // free the space used to keep the pointers to the lists.
   free(g);               // free the space allocated for graph_struct
}

// returns the number of vertices in g.
int numVertices(graphPT g)
{
   if (g == NULL) return 0;
   return g->N;
}

// returns an array with the neighbors of vertex v in graph g. 
// Sets res_size to the size of the returned array
int* vertexNeighbors(graphPT g, int v, int* res_size)
{
   if (g == NULL) return NULL;
   if ((v < 0) || (v >= g->N))
   {
      return NULL;
   }
   (*res_size) = compute_length(g->E[v]);
   int* result = malloc( (*res_size) * sizeof(int) );
   int i;
   nodePT curr = g->E[v];
   for(i=0; i<(*res_size); i++, curr = curr->next){
        result[i]=curr->data;
   }
   return result;
}

// returns 1 if the specified edge exists, 0 otherwise.
int edgeExists(graphPT g, int v1, int v2)
{
   if (g == NULL) return 0;
   if ((v1 < 0) || (v1 >= g->N))
   {
      return 0;
   }
   if ((v2 < 0) || (v2 >= g->N))
   {
      return 0;
   }

   nodePT n;
   for (n = g->E[v1]; n != NULL; n=n->next)
   {
      if (n->data == v2)
      {
         return 1;
      }
   }
   
   return 0;
}

// connects vertices v1 and v2 in the graph.
// returns 1 if successful, 0 if errors occurred.
int addEdge(graphPT g, int v1, int v2)
{
   if (g == NULL) return 0;
   if ((v1 < 0) || (v1 >= g->N))
   {
      return 0;
   }
   if ((v2 < 0) || (v2 >= g->N))
   {
      return 0;
   }
   
   if (edgeExists(g, v1, v2))
   {
      return 1;
   }
   
   g->E[v1] = insert_node(g->E[v1], NULL, new_node(v2));
   if ((v1 != v2) && (g->undirected == 1))
   {
      g->E[v2] =insert_node(g->E[v2], NULL, new_node(v1));
   }

   return 1;
}

// disconnects vertices v1 and v2 in the graph.
// returns 1 if successful, 0 if errors occurred.
int removeEdge(graphPT g, int v1, int v2)
{
   if (g == NULL) return 0;
   if ((v1 < 0) || (v1 >= g->N))
   {
      return 0;
   }
   if ((v2 < 0) || (v2 >= g->N))
   {
      return 0;
   }
   
   g->E[v1] = delete_by_data(g->E[v1], v2);
   if (g->undirected==1) g->E[v2] = delete_by_data(g->E[v2], v1);   
   return 1;
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
   if ((v < 0) || (v >= g->N))
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
	return NULL;
}

