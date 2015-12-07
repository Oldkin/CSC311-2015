
// Akash Surti
// CSC311 Systems Software
// 30 November 2015

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// This is that start of a program to simulate the
// first-come/first-served scheduling of processes
// for uninterrupted execution in a CPU
// (or customers in a bank who line up in
// front of a teller's window).

// There are two principle parameters in this
// simulation: MEAN_SERVICE_TIME and MEAN_INTERARRIVAL_TIME.
// The relationship between these two parameters determines
// the performance of the system. If processes (customers)
// arrive faster than they can be served, the length of
// the queue (waiting line) will grow and grow.

#define MEAN_SERVICE_TIME  2.0
#define MEAN_INTERARRIVAL_TIME 3.0

// Create aliases for the 3 data structures
// that this program defines and uses.
// Also, create aliases for pointers to these
// data structures.
typedef struct process Process, *ProcessPointer;
typedef struct node Node, *NodePointer;
typedef struct queue Queue, *QueuePointer;
typedef struct priorityQueue PriorityQueue, *PriorityQueuePointer;

struct priorityQueue {
  int capacity;
  int size;
  double *data;
}; // priorityQueue

// A process is the basic unit of work in
// the system.
// It is a program to be executed or a customer
// in a bank who requires help from a teller.
struct process {
  // id is a unique integer identifier for the process
  int id;

  // serviceTime is a measure of the time required
  // from the CPU for this process if the process
  // is a program (or from the teller if the process
  // is a customer in a bank)
  double serviceTime;

  // interarrivalTime is a measure of the time that
  // elapses between the arrival of the previous
  // process and the arrival of this process
  double interarrivalTime;

  // arrivalTime is the time at which this process
  // enters the system---it is the sum of the interarrival
  // times of this process and all previous processes
  double arrivalTime;

  // serviceStartTime is the time at which this
  // process begins execution in the CPU (or receiving
  // service from the teller if the process is a customer
  // in a bank)
  double serviceStartTime;

  // serviceCompleteTime is the time at which the
  // execution of this process ends (or the time
  // at which the teller finishes whatever tasks
  // the customer has requested in the case that
  // the process is a customer in a bank)
  double serviceCompleteTime;

  // waitTime is the amount of time a process waits
  // after it arrives and before it is initiated.
  // This can be calulcated by measuring the
  // difference between arrivalTime and
  // serviceStartTime.
  double waitTime;
}; // process

// We can represent a queue with a doubly-linked
// list.
// A node is one element in the linked list.
// It contains a means of finding information
// about a single process and the means of finding
// what lies immediately ahead and immediately behin
// in the queue.
struct node {
  ProcessPointer processPointer;
  NodePointer pointerToPrevNode;
  NodePointer pointerToNextNode;
}; // node

// A queue is a waiting line.
// Processes (or customers) join the
// waiting line at one end and exit
// at the other end.
struct queue {
  int length;
  NodePointer pointerToHead;
  NodePointer pointerToTail;
}; // queue

PriorityQueuePointer createPriorityQueue( int maximumSize ) {
  PriorityQueuePointer pq = (PriorityQueuePointer) malloc(sizeof(PriorityQueue));
  pq->capacity = maximumSize;
  pq->size = 0;
  pq->data = (double *) malloc((1 + maximumSize) * sizeof(int));

  int i;
  for( i = 0; i < maximumSize; i++ ) {
    pq->data[i] = 0;
  } // for

  return pq;
} // createPriorityQueue( int )

bool isPriorityQueueEmpty( PriorityQueuePointer pq ) {
  return pq->size == 0;
} // isPriorityQueueEmpty( PriorityQueuePointer )

void rise( double data[], int i ) {
  int j = i/2;
  if( i > 1 && data[j] > data[i] ) {
    double temp = data[i];
    data[i] = data[j];
    data[j] = temp;

    rise( data, j );
  } // if
} // rise( int[], int )

void pqEnqueue( PriorityQueuePointer pq, double n ) {
  if( pq->size < pq->capacity ) {
    int index = 1 + pq->size;
    pq->data[index] = n;

    rise( pq->data, index );

    pq->size++;
  } // if
} // pqEnqueue( int )

void printPriorityQueue( PriorityQueuePointer pq ) {
  int i;
  for( i = 1; i <= pq->size; i++ ) {
    printf( "%4f ", pq->data[i] );
  } // for
  printf( "\n" );
} // printPriorityQueue( PriorityQueuePointer )

void fall( PriorityQueuePointer pq, int i ) {
  int j = 2 * i;
  int k = 2 * i + 1;
  if( k <= pq->size && pq->data[k] < pq->data[j] ) {
    j = k;
  } // if

  if( j <= pq->size && pq->data[i] > pq->data[j] ) {
    double temp = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = temp;

    fall( pq, j );
  } // if
} // fall( PriorityQueuePointer, int )

double pqDequeue( PriorityQueuePointer pq ) {
  if( pq->size > 0 ) {
    printPriorityQueue( pq );

    double result = pq->data[1];
    pq->data[1] = pq->data[pq->size];
    pq->data[pq->size] = 0;
    pq->size--;

    fall( pq, 1 );

    return result;
  } // if
  else {
    return -99;
  } // else
} // pqDequeue()

int peek( PriorityQueuePointer pq ) {
  return pq->data[1];
} // peek( PriorityQueuePointer )

void seedRandomNumberGenerator() {
  // Seed the random number generator
  // with the time measured in seconds.
  // "time_t" is a just another name for
  // a long (64 bit) integer.
  time_t t = time(NULL) ;
  srand( t ) ;
} // seedRandomNumberGenerator()

// Service times and interarrival times
// will be random numbers drawn from an
// exponential distribution.
// All values will be positive.
// Smaller values will be more likely than
// larger values.
// There is no upper bound on the values.
double exponentialRandom( double mean ) {
  return -mean * log(((double) rand())/RAND_MAX);
} // exponentialRandom()

int numberOfProcessesCreated = 0;

ProcessPointer createProcess() {
  ProcessPointer pp = (ProcessPointer) malloc(sizeof(Process));
  pp->id = numberOfProcessesCreated++;
  pp->serviceTime = exponentialRandom( MEAN_SERVICE_TIME );
  pp->interarrivalTime = exponentialRandom( MEAN_INTERARRIVAL_TIME );

  // At the time of the process' creation,
  // the values of the arrivalTime, serviceStartTime,
  // and serviceCompleteTime are unknown.
  pp->arrivalTime = 0.0;
  pp->serviceStartTime = 0.0;
  pp->serviceCompleteTime = 0.0;
  return pp;
} // createProcess()

void printProcess( ProcessPointer pp ) {
  printf( "| process #%3d |  %8.4f    |     %8.4f      |  %8.4f    |     %8.4f       |       %8.4f        |\n",
	  pp->id,
          pp->serviceTime,
          pp->interarrivalTime,
	  pp->arrivalTime,
          pp->serviceStartTime,
          pp->serviceCompleteTime);
} // printProcess( ProcessPointer )

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
  printf( "---------------------------------------------------------------------------------------------------------------\n");
  printf( "| process # id | Service Time | Interarrival Time | Arrival Time | Service Start Time | Service Complete Time |\n");
  printf( "---------------------------------------------------------------------------------------------------------------\n");
  while( np != NULL ) {
    printProcess( np->processPointer );
    np = np->pointerToPrevNode;
  } // while
  printf( "---------------------------------------------------------------------------------------------------------------\n");
} // printProcessInQueue( QueuePointer )

bool isQueueEmpty( QueuePointer qp ) {
  return (qp->pointerToHead == NULL) &&
    (qp->pointerToTail == NULL);
} // isQueueEmpty( QueuePointer )

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

// Create a queue and fill it with a specified
// number of processes.
QueuePointer buildQueue( int numberOfProcesses ) {
  seedRandomNumberGenerator();

  QueuePointer qp = createQueue();

  double elapsedTime = 0.0;
  int i;
  for( i = 0; i < numberOfProcesses; i++ ) {
    ProcessPointer pp = createProcess();
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;
    enqueue( qp, pp );
  } // for

  return qp;
} // buildQueue( int )

ProcessPointer sort(QueuePointer qp, double n){
  NodePointer np = qp->pointerToHead;
  ProcessPointer ppp = NULL;

  for(int i = 0; i < qp->length; i++){
    ProcessPointer pp = np->processPointer;
    double input = pp->serviceTime;

    if(input == n){
      ppp = pp;
      // printProcess(ppp);
      return ppp;
    }
    np = np->pointerToPrevNode;
  }// for

  return NULL;
}

QueuePointer test(QueuePointer qp){
  PriorityQueuePointer pq = createPriorityQueue(qp->length);
  QueuePointer qpp = createQueue();
  NodePointer np = qp->pointerToHead;

  for(int i = 0; i < qp->length; i++){
    ProcessPointer pp = np->processPointer;
    double input = pp->serviceTime;

    pqEnqueue(pq, input);
    np = np->pointerToPrevNode;
  }

  printf("\n");
  np = qp->pointerToHead;

  while( !isPriorityQueueEmpty(pq) ) {
    double n = pqDequeue(pq);
    printf( "highest priority item = %8.4f\n", n );

    ProcessPointer pp = sort(qp, n);
    pp->arrivalTime = 0.0;
    pp->serviceStartTime = 0.0;
    pp->serviceCompleteTime = 0.0;
    enqueue(qpp, pp);
  } // while

  printf("\n");

  return qpp;
}

int main( int argc, char** argv ) {

  seedRandomNumberGenerator();

  // Creates an empty queue
  QueuePointer qp = createQueue();

  // meanServiceTime is measure of the
  // amount of time needed to execute each process
  // (or take care of each customer).
  double meanServiceTime = 0.0;

  // meanInterarrivalTime is a measure of
  // the time that elapses between the arrival
  // in the system of successive processes
  // (or customers).
  double meanInterarrivalTime = 0.0;

  // meanWaitTime is the measure of
  // the average amount of time the
  // processes had to wait after arrival
  // before being implemented
  double meanWaitTime = 0.0;

  // maximumWaitTime measures the highest
  // amount of time a process had to wait
  double maximumWait = 0.0;

  // N number of processes to add to the queue
  int N = 10;

  double elapsedTime = 0.0;
  // Loop that adds N number of processes
  // to the queue
  for(int i = 0; i < N; i++ ) {
    ProcessPointer pp = createProcess();
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;

    meanServiceTime += pp->serviceTime;
    meanInterarrivalTime += pp->interarrivalTime;

    enqueue( qp, pp );
    // printQueue( qp );
  } // for

  // variables for caluclating the mean
  meanServiceTime = meanServiceTime/N;
  meanInterarrivalTime = meanInterarrivalTime/N;

  // variables for calulating the varience
  double varServiceTime = 0.0;
  double varInterarrivalTime = 0.0;

  NodePointer cnp = qp->pointerToHead;
  while(cnp != NULL){

        // cpp points to the current process
        ProcessPointer cpp = cnp->processPointer;

        // There is no node in front of the first node
        if(cnp->pointerToNextNode == NULL){
          cpp->serviceStartTime = cpp->arrivalTime;
        } // if
        else {

          // serviceCompleteTime of the process before
          double a = cnp->pointerToNextNode->processPointer->serviceCompleteTime;

          // arrivalTime
          double b = cpp->arrivalTime;

            // The process' serviceStartTime is
            // the larger of this process' arrivalTime
            // and the serviceCompleteTime of the process before
            if(a > b){
              cpp->serviceStartTime = a;
            } // if
            else{
              cpp->serviceStartTime = b;
            } // else
        } // else

        // Computes this process' serviceCompleteTime
        // by adding the process' serviceStartTime
        // and serviceTime
        cpp->serviceCompleteTime = cpp->serviceStartTime + cpp->serviceTime;
        cnp = cnp->pointerToPrevNode;

        // Calculate the deviation of each serviceTime
        // and then square the value
        varServiceTime += pow(cpp->serviceTime - meanServiceTime, 2);

        // Calculate the deviation of each interarrivalTime
        // and then square the value
        varInterarrivalTime += pow(cpp->interarrivalTime - meanInterarrivalTime, 2);

        // Caluclate the amount of time a process has to wait
        // before being initiated
        cpp->waitTime = cpp->serviceStartTime - cpp->arrivalTime;

        // Calculates the sum of all waitTimes
        meanWaitTime += cpp->waitTime;

        // Finding the maximumWait
        if(maximumWait < cpp->waitTime){
          maximumWait = cpp->waitTime;
        }
  }

  varServiceTime = varServiceTime/N;
  varInterarrivalTime = varInterarrivalTime/N;

  meanWaitTime = meanWaitTime/N;

  printf( "\n" );
  printProcessesInQueue(qp);

  printf("\n     Mean Service Time = %8.4f\n              Varience = %8.4f \n\nMean Interarrival Time = %8.4f\n              Varience = %8.4f",
        meanServiceTime, varServiceTime, meanInterarrivalTime, varInterarrivalTime);
  printf("\n\n        Mean Wait Time = %8.4f", meanWaitTime);
  printf("\n     Maximum Wait Time = %8.4f", maximumWait);
  printf( "\n" );
  // printf( "\nBegin removing elements from the queue.\n\n" );
  // printQueue( qp );

  QueuePointer qpp = test(qp);

  cnp = qpp->pointerToHead;

  elapsedTime = 0.0;
  // Loop that adds N number of processes
  // to the queue
  for(int i = 0; i < N; i++ ) {
    ProcessPointer pp = cnp->processPointer;
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;

    meanServiceTime += pp->serviceTime;
    meanInterarrivalTime += pp->interarrivalTime;
  } // for

  // variables for caluclating the mean
  meanServiceTime = meanServiceTime/N;
  meanInterarrivalTime = meanInterarrivalTime/N;

  while(cnp != NULL){

        // cpp points to the current process
        ProcessPointer cpp = cnp->processPointer;

        // There is no node in front of the first node
        if(cnp->pointerToNextNode == NULL){
          cpp->serviceStartTime = cpp->arrivalTime;
        } // if
        else {

          // serviceCompleteTime of the process before
          double a = cnp->pointerToNextNode->processPointer->serviceCompleteTime;

          // arrivalTime
          double b = cpp->arrivalTime;

            // The process' serviceStartTime is
            // the larger of this process' arrivalTime
            // and the serviceCompleteTime of the process before
            if(a > b){
              cpp->serviceStartTime = a;
            } // if
            else{
              cpp->serviceStartTime = b;
            } // else
        } // else

        // Computes this process' serviceCompleteTime
        // by adding the process' serviceStartTime
        // and serviceTime
        cpp->serviceCompleteTime = cpp->serviceStartTime + cpp->serviceTime;
        cnp = cnp->pointerToPrevNode;

        // Calculate the deviation of each serviceTime
        // and then square the value
        varServiceTime += pow(cpp->serviceTime - meanServiceTime, 2);

        // Calculate the deviation of each interarrivalTime
        // and then square the value
        varInterarrivalTime += pow(cpp->interarrivalTime - meanInterarrivalTime, 2);

        // Caluclate the amount of time a process has to wait
        // before being initiated
        cpp->waitTime = cpp->serviceStartTime - cpp->arrivalTime;

        // Calculates the sum of all waitTimes
        meanWaitTime += cpp->waitTime;

        // Finding the maximumWait
        if(maximumWait < cpp->waitTime){
          maximumWait = cpp->waitTime;
        }
  }

  varServiceTime = varServiceTime/N;
  varInterarrivalTime = varInterarrivalTime/N;

  meanWaitTime = meanWaitTime/N;

  printProcessesInQueue(qpp);

  printf("\n     Mean Service Time = %8.4f\n              Varience = %8.4f \n\nMean Interarrival Time = %8.4f\n              Varience = %8.4f",
        meanServiceTime, varServiceTime, meanInterarrivalTime, varInterarrivalTime);
  printf("\n\n        Mean Wait Time = %8.4f", meanWaitTime);
  printf("\n     Maximum Wait Time = %8.4f", maximumWait);
  printf( "\n" );

  exit(0);
} //  main( int, char** )
