#include <stdio.h>
#include <stdlib.h>

// the memory allocated by this function is initialized to 0
int ** alloc_2d(int rows, int columns)
{
   int row, col;
   // allocate space to keep a pointer for each row
   int ** table = (int**)calloc(rows , sizeof(int *));

   // VERY IMPORTANT: allocate the space for each row
   for (row = 0; row < rows; row++)
      table[row] = (int*)calloc(columns , sizeof(int));

   return table;
}


void free_2d(int ** array, int rows, int columns)
{
   int row;
   // VERY IMPORTANT: free the space for each row
   for (row = 0; row < rows; row++)
      free(array[row]);

   // free the space with the pointer to each row.
   free(array);
}


void printMatrix(int ** array, int rows, int columns)
{
   int row, col;
   for (row = 0; row < rows; row++)
   {
      for (col = 0; col < columns; col++)
      {
         printf("%5d", array[row][col]);
      }
      printf("\n");
   }
   printf("\n");
}


int ** randomMatrix(int rows, int columns, int limit)
{
   int ** result = alloc_2d(rows, columns);

   int row, col;
   for (row = 0; row < rows; row++)
   {
      for (col = 0; col < columns; col++)
      {
         int value = rand() % limit;
         result[row][col] = value;
      }
   }

   return result;
}


int ** addMatrices(int ** A, int ** B, int rows, int columns)
{
   int ** result = alloc_2d(rows, columns);

   int row, col;
   for (row = 0; row < rows; row++)
   {
      for (col = 0; col < columns; col++)
      {
         result[row][col] = A[row][col] + B[row][col];
      }
   }

   return result;
}


