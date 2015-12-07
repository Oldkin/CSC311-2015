

// Leon Tabak
// CSC311 Systems Software
// 30 November 2015


// There are two principle parameters in this
// simulation: MEAN_SERVICE_TIME and MEAN_INTERARRIVAL_TIME.
// The relationship between these two parameters determines
// the performance of the system. If processes (customers)
// arrive faster than they can be served, the length of
// the queue (waiting line) will grow and grow.

// MEAN_SERVICE_TIME is measure of the
// amount of time needed to execute each process
// (or take care of each customer).
#define MEAN_SERVICE_TIME  2.0

// MEAN_INTERARRIVAL_TIME is a measure of 
// the time that elapses between the arrival
// in the system of successive processes
// (or customers).
#define MEAN_INTERARRIVAL_TIME 3.0

typedef struct node Node, *NodePointer;
typedef struct queue Queue, *QueuePointer;

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

QueuePointer createQueue();
void printNode( NodePointer np );
void printQueue( QueuePointer qp );
void printProcessesInQueue( QueuePointer qp );
bool isQueueEmpty( QueuePointer qp );
ProcessPointer peek( QueuePointer qp );
void enqueue( QueuePointer qp, ProcessPointer pp );
ProcessPointer dequeue( QueuePointer qp );
void testQueue( int numberOfProcesses );
QueuePointer buildQueue( int numberOfProcesses );






