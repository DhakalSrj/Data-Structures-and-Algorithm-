// DFS for directed graphs
// BPW, 4/2003

#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define TREE 0
#define BACK 1
#define CROSS 2
#define FORWARD 3

int n;  // number of nodes
int e;  // number of edges
struct edge {
  int tail,head,type; 
};
typedef struct edge edgeType;
edgeType *edgeTab;
int *firstEdge;  // Table indicating first in range of edges with a common tail

int *discovery,*finish,*predecessor,*vertexStatus;               

// Reading the input file and organize adjacency lists

int tailThenHead(const void* xin, const void* yin)
// Used in calls to qsort() and bsearch() for read_input_file()
{
int result;
edgeType *x,*y;

x=(edgeType*) xin;
y=(edgeType*) yin;
result=x->tail - y->tail;
if (result!=0)
  return result;
else
  return x->head - y->head;
}

void read_input_file()
{
int a,b,i,j;
edgeType work;
edgeType *ptr;

scanf("%d %d",&n,&e);
edgeTab=(edgeType*) malloc(e*sizeof(edgeType));
if (!edgeTab)
{
  printf("edgeTab malloc failed %d\n",__LINE__);
  exit(0);
}

for (i=0; i<e; i++)
{
  scanf("%d %d",&a,&b);
  if (a<0 || a>=n || b<0 || b>=n)
  {
    printf("Invalid input %d %d at %d\n",a,b,__LINE__);
    exit(0);
  }
  edgeTab[i].tail=a;
  edgeTab[i].head=b;
}

// sort edges
qsort(edgeTab,e,sizeof(edgeType),tailThenHead);

// Coalesce duplicates into a single edge
j=0;
for (i=1; i<e; i++)
  if (edgeTab[j].tail==edgeTab[i].tail
     && edgeTab[j].head==edgeTab[i].head)
    ; 
  else
  {
    j++;
    edgeTab[j].tail=edgeTab[i].tail;
    edgeTab[j].head=edgeTab[i].head;
  }
e=j+1;

// For each vertex as a tail, determine first in range of edgeTab entries
firstEdge=(int*) malloc((n+1)*sizeof(int));
if (!firstEdge)
{
  printf("malloc failed %d\n",__LINE__);
  exit(0);
}
j=0;
for (i=0; i<n; i++)
{
  firstEdge[i]=j;
  for ( ;
       j<e && edgeTab[j].tail==i;
       j++)
    ;
}
firstEdge[n]=e;
}

int time;  /*Keeps node numbering*/

void DFSvisit(int u)
{
int i,v;

vertexStatus[u]=GRAY;
time++;
discovery[u]=time;

for (i=firstEdge[u];i<firstEdge[u+1];i++)
{
  v=edgeTab[i].head;
  if (vertexStatus[v]==WHITE)
  {
    edgeTab[i].type=TREE;
    predecessor[v]=u;
    DFSvisit(v);
  }
  else if (vertexStatus[v]==GRAY)
    edgeTab[i].type=BACK;
  else if (discovery[u]<discovery[v])
    edgeTab[i].type=FORWARD;
  else
    edgeTab[i].type=CROSS;
}
vertexStatus[u]=BLACK;
time++;
finish[u]=time;
}

int main ()
{
int u,i,j,k,nextDFS;

read_input_file();
discovery=(int*) malloc(n*sizeof(int));
finish=(int*) malloc(n*sizeof(int));
predecessor=(int*) malloc(n*sizeof(int));
vertexStatus=(int*) malloc(n*sizeof(int));
if (!discovery || !finish || !predecessor ||!vertexStatus)
{
  printf("malloc failed\n");
  exit(0);
}
// DFS code
for (u=0;u<n;u++)
{
  vertexStatus[u]=WHITE;
  predecessor[u]=(-1);
}
time=0;
for (u=0;u<n;u++)
  if (vertexStatus[u]==WHITE)
    DFSvisit(u);

//Output code
printf("Vertex  discovery    finish     predecessor\n");
for (i=0;i<n;i++)
  printf(" %3d      %3d         %3d          %3d\n",i,
    discovery[i],finish[i],predecessor[i]);
printf("Edge Tail Head Type\n");
for (i=0;i<e;i++)
{
  printf(" %3d  %3d  %3d  ",i,edgeTab[i].tail,edgeTab[i].head);
  switch(edgeTab[i].type)
  {
    case TREE:    printf("tree\n"); break;
    case BACK:    printf("back\n"); break;
    case CROSS:   printf("cross\n"); break;
    case FORWARD: printf("forward\n"); break;
  }
}

free(edgeTab);
free(firstEdge);
free(discovery);
free(finish);
free(predecessor);
free(vertexStatus);
return 0;
}