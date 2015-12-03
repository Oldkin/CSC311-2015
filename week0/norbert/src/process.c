

// Leon Tabak
// CSC311 Systems Software
// 30 November 2015

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "process.h"

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

// Create a process whose mean service is drawn
// from a set of exponentially distributed random
// numbers with a mean of mst and whose interarrival 
// time is drawn from a set of exponentially distributed
// random numbers with a mean of mit. 
ProcessPointer createProcess( int mst, int mit ) {
  ProcessPointer pp = (ProcessPointer) malloc(sizeof(Process));
  pp->id = numberOfProcessesCreated++;
  pp->serviceTime = exponentialRandom( mst );
  pp->interarrivalTime = exponentialRandom( mit );

  // At the time of the process' creation,
  // the values of the arrivalTime, serviceStartTime,
  // and serviceCompleteTime are unknown.
  pp->arrivalTime = 0.0;
  pp->serviceStartTime = 0.0;
  pp->serviceCompleteTime = 0.0;
  return pp;
} // createProcess()

void printProcess( ProcessPointer pp ) {
  printf( "process #%3d: (%8.4f, %8.4f, %8.4f, %8.4f, %8.4f)\n",
	  pp->id,
          pp->serviceTime,
          pp->interarrivalTime,
	  pp->arrivalTime,
          pp->serviceStartTime,
          pp->serviceCompleteTime );
} // printProcess( ProcessPointer )
