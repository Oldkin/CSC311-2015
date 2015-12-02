

// Leon Tabak
// CSC311 Systems Software
// 30 November 2015

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
}; // process

typedef struct process Process, *ProcessPointer;

void seedRandomNumberGenerator();
double exponentialRandom( double mean );
ProcessPointer createProcess( int mst, int mit );
void printProcess( ProcessPointer pp );


