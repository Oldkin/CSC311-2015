
// treesort.c
// Theresa Dinh
// CSC311 Systems Software
// November 23 2015

#include <stdio.h>
#include <stdlib.h>

// define a node in a binary search tree
struct node
{
int value;
struct node* lp;
struct node* rp;
};

// define aliases
typedef struct node Node;
typedef struct node* NodePointer;

// define a function that will create
// a new tree that contains only a single
// node
NodePointer createRoot(int n)
{
NodePointer np = (NodePointer)malloc(sizeof(Node));
np->value = n;
np->lp = NULL;
np->rp = NULL;
return np;
}

// define a function that will add a new
// node to an existing binary search tree
NodePointer addNode(NodePointer np, int n)
{
NodePointer rp = np;

if(np == NULL)
{
rp = createRoot(n);
}
else if(n < np->value)
{
if(np->lp == NULL)
{
np->lp = createRoot(n);
}
else
{
np->lp = addNode(np->lp, n);
}
}
else if(n > np->value)
{
if(np->rp == NULL)
{
np->rp = createRoot(n);
}
else
{
np->rp = addNode(np->rp, n);
}
}
else
{
    // if value to be added is already in tree, do nothing
    // (do not add duplicate values to tree)
}
return rp;
}

// traverse a binary search tree
// in order, printing the values
// found at each node
void printNodes(NodePointer np)
{
if(np != NULL)
{
printNodes(np->lp);
printf("value at node = %4d\n", np->value);
printNodes(np->rp);
}
}

int main( int argc, char** argv ) {

  // build a binary search tree that
  // contains integers found on the command line,
  // then print the integers in ascending order

  if(argc > 1)
  {
    NodePointer rp = createRoot(atoi(argv[1]));
    int i;
    for(i = 2; i < argc; i++)
    {
      rp = addNode(rp, atoi(argv[i]));
    }
    printNodes(rp);
  }

  exit(0);
} // main( int, char** )
