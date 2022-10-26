/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 */

#ifndef CSE2320_GRAPHS_H
#define CSE2320_GRAPHS_H

#include "list.h"

typedef struct struct_graph * graphPT;

// creates a graph with the specified number of vertices
graphPT newGraph(int N, int undirected);

// deallocates the memory allocated to graph g.
void destroyGraph(graphPT g);

// returns the number of vertices in g.
int numVertices(graphPT g);

// connects vertices v1 and v2 in the graph.
// returns 1 if successful, 0 if errors occurred.
int addEdge(graphPT g, int v1, int v2);

// disconnects vertices v1 and v2 in the graph.
// returns 1 if successful, 0 if errors occurred.
int removeEdge(graphPT g, int v1, int v2);

// returns 1 if the specified edge exists, 0 otherwise.
int edgeExists(graphPT g, int v1, int v2);

// returns an array with the neighbors of vertex v in graph g. 
// Sets res_size to the size of the returned array
int* vertexNeighbors(graphPT g, int v, int* res_size);

// Prints the graph, namely the vertices, and the neighbors of each vertex.
void printGraph(graphPT g);

// Prints the neighbors of vertex v.
void printNeighbors(graphPT g, int v);


// returns the pointer to the adjacency matrix of g.
int** getAdjacencyMatrix(graphPT g);




#endif // CSE2320_GRAPHS_H
