
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "priorityQueue.h"

// compare 2 elements that are in the priority queue
// return -1 if element i < element j
// return +1 if element i > element j
// return  0 if element i == element j
int compareElements( PriorityQueuePointer pq, int i, int j ) {
  if( pq->data[i]->serviceTime < pq->data[j]->serviceTime ) {
    return -1;
  } // if
  else if( pq->data[i]->serviceTime > pq->data[j]->serviceTime ) {
    return +1;
  } // else if
  else {
    return 0;
  } // else
} // compareElements( PriorityQueuePointer, int, int )

void swap( PriorityQueuePointer pq, int i, int j ) {
    ProcessPointer temp = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = temp;
} // swap( PriorityQueuePointer, int, int )

// Create a priority queue with a specified capacity
PriorityQueuePointer createPriorityQueue( int maximumSize ) {
  PriorityQueuePointer pq = 
    (PriorityQueuePointer) malloc(sizeof(PriorityQueue));
  pq->capacity = maximumSize;
  pq->size = 0;
  // create array that will hold elements in
  // priority queue
  pq->data = (ProcessPointer *) 
      malloc((1 + maximumSize) * sizeof(ProcessPointer));

  // set values of all elements of array to zero
  int i;
  for( i = 0; i < maximumSize; i++ ) {
    pq->data[i] = NULL;
  } // for

  return pq;
} // createPriorityQueue( int )

bool isPriorityQueueEmpty( PriorityQueuePointer pq ) {
  return pq->size == 0;
} // isPriorityQueueEmpty( PriorityQueuePointer )

// move element i up in the tree until
// the heap condition (all nodes have values
// less than the values of their children)
// is restored
void rise( PriorityQueuePointer pq, int i ) {
  int j = i/2;
  if( i > 1 && compareElements(pq, i, j) < 0 ) {
    swap( pq, i, j );
    //int temp = pq->data[i];
    //pq->data[i] = pq->data[j];
    //pq->data[j] = temp;

    rise( pq, j );
  } // if
} // rise( int[], int )

// add an element to the priority queue
// (nothing happens and no error is reported
// if there is no room for another element)
void pqEnqueue( PriorityQueuePointer pq, ProcessPointer pp ) {
  if( pq->size < pq->capacity ) {
    int index = 1 + pq->size;
    pq->data[index] = pp;

    rise( pq, index );

    pq->size++;
  } // if
} // pqEnqueue( int )

// print the contents of the array that
// holds the elements of the priority queue
// (this function is to help in debugging)
void printPriorityQueue( PriorityQueuePointer pq ) {
  int i;
  for( i = 1; i <= pq->size; i++ ) {
    printf( "%4d ", i );
    printProcess(pq->data[i]);
    printf( "\n" );
  } // for
  printf( "\n" );
} // printPriorityQueue( PriorityQueuePointer )

// move an element down in the tree
// until the heap condition (value of each
// node is less than the value of its children)
// is restored
void fall( PriorityQueuePointer pq, int i ) {
  // i is the index of a parent node in the heap
  // j and k are the indices of its children
  // choose the smaller of the children
  int j = 2 * i;
  int k = 2 * i + 1;
  if( k <= pq->size && compareElements( pq, k, j) < 0 ) {
    j = k;
  } // if

  // do not fall too far!
  // stop falling when heap condition has 
  // been stored
  if( j <= pq->size && compareElements(pq, j, i) < 0 ) {
    swap( pq, i, j );
    //int temp = pq->data[i];
    //pq->data[i] = pq->data[j];
    //pq->data[j] = temp;

    fall( pq, j );
  } // if
} // fall( PriorityQueuePointer, int )

// remove the element that has the highest
// priority from the priority queue
// (highest priority might mean smallest value)
ProcessPointer pqDequeue( PriorityQueuePointer pq ) {
  printPriorityQueue( pq );

  ProcessPointer result = pq->data[1];
  pq->data[1] = pq->data[pq->size];
  pq->data[pq->size] = NULL;
  pq->size--;

  fall( pq, 1 );

  return result;
} // pqEnqueue()

ProcessPointer pqPeek( PriorityQueuePointer pq ) {
  return pq->data[1];
} // peek( PriorityQueuePointer )

void testPriorityQueue() {
  PriorityQueuePointer pq = createPriorityQueue( 12 );
  printf( "Is newly created income empty? %d\n\n", 
    isPriorityQueueEmpty(pq) );


  pqEnqueue( pq, createProcess(2,3) );
  pqEnqueue( pq, createProcess(2,3) );
  pqEnqueue( pq, createProcess(2,3) );
  pqEnqueue( pq, createProcess(2,3) );
  pqEnqueue( pq, createProcess(2,3) );

  printPriorityQueue( pq );

  printf( "\n" );

  while( !isPriorityQueueEmpty(pq) ) {
    ProcessPointer pp = pqDequeue( pq );
    printf( "highest priority item = %8.4f\n", pp->serviceTime );
  } // while

} // testPriorityQueue()


