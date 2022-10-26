#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main()
{
    graphPT g = NULL;
    int command = -1;
    int undir;
    while(command!=0)
    {
        printf("\n");
        printf("MENU:\n");
        printf("0: Exit\n");
        printf("1: Create new graph.\n");
        printf("2: Add an edge.\n");
        printf("3: Remove an edge.\n");
        printf("4: Print neighbors of an edge.\n");
        printf("5: Print graph.\n");

        printf("\nEnter command (0-5): ");
        scanf("%d", &command);

        if (command == 0)
        {
            destroyGraph(g);
        }

        else if (command == 1)
        {
            int number = 0;
            while(number <= 0)
            {
                printf("Enter number of vertices and 1 for undirected graph: ");
                scanf("%d %d", &number,&undir);
            }

            destroyGraph(g);
            g = newGraph(number,undir);
        }

        else if (command == 2)
        {
            int v1, v2;
            printf("Enter vertices: ");
            scanf("%d %d", &v1, &v2);
            addEdge(g, v1, v2);
        }

        else if (command == 3)
        {
            int v1, v2;
            printf("Enter vertices: ");
            scanf("%d %d", &v1, &v2);
            removeEdge(g, v1, v2);
        }

        else if (command == 4)
        {
            int v1;
            printf("Enter vertex: ");
            scanf("%d", &v1);
            printNeighbors(g, v1);
        }

        else if (command == 5)
        {
            printGraph(g);
        }

        else
        {
            printf("Invalid command.\n");
        }
    }
    return 0;
}
