

// Leon Tabak
// CSC311 Systems Software
// 30 November 2015

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "queue.h"

QueuePointer createQueue() {
  // Create an empty queue.
  // The number of elements in the
  // empty queue is 0.
  // The pointers to its (non-existant)
  // head and tail are NULL.
  QueuePointer qp = (QueuePointer) malloc(sizeof(Queue));
  qp->length = 0;
  qp->pointerToHead = NULL;
  qp->pointerToTail = NULL;
  return qp;
} // createQueue()

// Print the id numbers of the...
//   * process that is referenced in the node
//     that is behind the given node
//   * process that is referenced in the given node
//   * process that is referenced in the node
//     that is ahead of a the given node
void printNode( NodePointer np ) {
  int previous = -1;
  int current = -1;
  int next = -1;

  if( np != NULL )  {
    current = np->processPointer->id;
    if( np->pointerToPrevNode != NULL ) {
      previous = np->pointerToPrevNode->processPointer->id;
    } // if
    if( np->pointerToNextNode != NULL ) {
      next = np->pointerToNextNode->processPointer->id;
    } // if
  } // if

  printf( "(%3d:%3d:%3d)", previous, current, next );
} // printNode( NodePointer )

void printQueue( QueuePointer qp ) {
  printf( "[%3d  ", qp->length );
  NodePointer np = qp->pointerToTail;
  while( np != NULL ) {
    printNode( np );
    np = np->pointerToNextNode;
  } // while
  printf( "]\n" );
} // printQueue( QueuePointer )

// Print a complete description of the 
// process referenced in each element (node)
// of the queue.
// The complete description includes id, service time,
// interarrival time, arrival time, time at which
// service begins, and time at which service is completed.
void printProcessesInQueue( QueuePointer qp ) {
  NodePointer np = qp->pointerToHead;
  while( np != NULL ) {
    printProcess( np->processPointer );
    np = np->pointerToPrevNode;
  } // while
} // printProcessInQueue( QueuePointer )

bool isQueueEmpty( QueuePointer qp ) {
  return (qp->pointerToHead == NULL) &&
    (qp->pointerToTail == NULL);
} // isQueueEmpty( QueuePointer )

// Take a look at the process that is at
// the head of the line.
ProcessPointer peek( QueuePointer qp ) {
  ProcessPointer pp = NULL;

  if( qp->pointerToHead != NULL ) {
    pp = qp->pointerToHead->processPointer;
  } // if

  return pp;
} // peek( QueuePointer )

// Add a process at the end of the line.
void enqueue( QueuePointer qp, ProcessPointer pp ) {
  NodePointer np = (NodePointer) malloc(sizeof(Node));
  np->processPointer = pp;

  if( qp->pointerToTail != NULL ) {
    qp->pointerToTail->pointerToPrevNode = np;
  } // if

  np->pointerToNextNode = qp->pointerToTail;
  np->pointerToPrevNode = NULL;

  qp->pointerToTail = np;
  if( qp->pointerToHead == NULL ) {
    qp->pointerToHead = np;
  } // if

  // increment count of number of elements in queue
  qp->length++;
} // enqueue( QueuePointer, ProcessPointer )

// Remove a process from the front of the line.
ProcessPointer dequeue( QueuePointer qp ) {
  ProcessPointer pp = NULL;
  if( qp->pointerToHead != NULL ) {
    pp = qp->pointerToHead->processPointer;
    qp->pointerToHead = qp->pointerToHead->pointerToPrevNode;
    if( qp->pointerToHead == NULL ) {
      qp->pointerToTail = NULL;
    } // if
    else {
      free( qp->pointerToHead->pointerToNextNode );
      qp->pointerToHead->pointerToNextNode = NULL;
    } // else

    // decrement count of number of elements in queue
    qp->length--;
  } // if

  return pp;
} // dequeue( QueuePointer )

// Verify that the elements of the doubly-linked
// list are correctly linked.
void testQueue( int numberOfProcesses ) {
  seedRandomNumberGenerator();

  QueuePointer qp = createQueue();

  printf( "\n\nBegin adding elements to the queue.\n\n" );
  printQueue( qp );

  double elapsedTime = 0.0;
  int i;
  for( i = 0; i < numberOfProcesses; i++ ) {
    ProcessPointer pp = createProcess(MEAN_SERVICE_TIME, 
        MEAN_INTERARRIVAL_TIME);
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;

    enqueue( qp, pp );
    printQueue( qp );
  } // for

  // Begin at front of queue and work our
  // way back to the tail, computing the
  // times at which service begins and ends
  // for each of the processes that we encounter
  // along the way

  // cnp points to the current node in the linked list
  NodePointer cnp = qp->pointerToHead;
  while( cnp != NULL ) {

    // cpp points to the current process
    ProcessPointer cpp = cnp->processPointer;

    // Compute this process' serviceStartTime
    // This is the larger of this process' arrivalTime
    // and the serviceCompleteTime of the process that
    // entered the system immediately before this process
    // (Note! The first process is special, because there
    // is no process that entered the system before it did!)
    if( cnp->pointerToNextNode == NULL ) {
      // the first node is special---there is no node
      // in front of this node
      cpp->serviceStartTime = cpp->arrivalTime;
    } // if
    else {
      // a is time at which this process entered system
      double a = cpp->arrivalTime;
      // b is time at which service for the process that 
      // entered system just before this one completed
      double b = 
        cnp->pointerToNextNode->processPointer->serviceCompleteTime;

      // time at which service for this process is 
      // completed is the larger of the two numbers
      if( a > b ) {
	cpp->serviceStartTime = a;
      } // if
      else {
        cpp->serviceStartTime = b;
      } // else
    } // else

    // Compute this process' serviceCompleteTime
    // This is just the process' serviceStartTime + its
    // serviceTime
    cpp->serviceCompleteTime = cpp->serviceStartTime +
      cpp->serviceTime;

    cnp = cnp->pointerToPrevNode;
  } // while


  printf( "\n" );
  printProcessesInQueue( qp );

  printf( "\nBegin removing elements from the queue.\n\n" );
  printQueue( qp );

  while( !isQueueEmpty( qp ) ) {
    ProcessPointer pp = dequeue( qp );
    printQueue( qp );
    free( pp );
  } // while
} // testQueue( int )

// Create a queue and fill it with a specified
// number of processes.
QueuePointer buildQueue( int numberOfProcesses ) {
  seedRandomNumberGenerator();

  QueuePointer qp = createQueue();

  double elapsedTime = 0.0;
  int i;
  for( i = 0; i < numberOfProcesses; i++ ) {
    ProcessPointer pp = createProcess( MEAN_SERVICE_TIME,
        MEAN_INTERARRIVAL_TIME );
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;
    enqueue( qp, pp );
  } // for

  return qp;
} // buildQueue( int )

