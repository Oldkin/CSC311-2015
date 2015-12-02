
typedef struct priorityQueue PriorityQueue, *PriorityQueuePointer;

struct priorityQueue {
  // capacity is the maximum number of elements
  // that can be stored in the priority queue
  int capacity;

  // size is the number of elements that are
  // currently stored in the priority queue
  int size;

  // data is an array that holds the elements
  // in the priority queue
  int *data;
}; // priorityQueue

PriorityQueuePointer createPriorityQueue( int maximumSize );
bool isPriorityQueueEmpty( PriorityQueuePointer pq );
void rise( PriorityQueuePointer pq, int i );
void pqEnqueue( PriorityQueuePointer pq, int n );
void printPriorityQueue( PriorityQueuePointer pq );
void fall( PriorityQueuePointer pq, int i );
int pqDequeue( PriorityQueuePointer pq );
int pqPeek( PriorityQueuePointer pq );
void testPriorityQueue();




