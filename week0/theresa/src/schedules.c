// schedules.c
// Theresa Dinh
// CSC311 Systems Software
// November 23, 2015

// features:
// -preprocessor directives #include and #define
// -header files stdio.h, time.h
// -typedefs
// -structs
// -library functions malloc(), srand()
// -casts
// -pointers

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MEAN_SERVICE_TIME 2.0
#define MEAN_INTERARRIVAL_TIME 3.0

typedef struct process ProcessRecord, *ProcessRecordPointer;

// define a node in a linked list that describes a process/task
// - time required to complete process
// - time until next process joins queue

struct process
{
int id ;
double timeToService;
double timeUntilNextProcess;
ProcessRecordPointer np;
};	

int main (int argc, char **argv)
{
// seed the rng with the time measured in seconds
// "time_t" is another 64bit integer
time_t t = time(NULL);
srand(t);

//  Null is a constant defined for us. It's zero
ProcessRecordPointer rootPointer = NULL;
ProcessRecordPointer pp = NULL;
ProcessRecordPointer cp = NULL;

// must declare counter before beginning loop
int i;
for (i = 0; i < 12; i++)
{

// malloc() is the function for memory allocation 
// sizeof is an operator that tells us how many bytes we 
// need to store an object of a given type
// malloc() returns a general kind of pointer (void *)
// so must cast it to remind compiler what kind of object
// we are pointing to
cp = (ProcessRecordPointer) malloc( sizeof(ProcessRecord) );
cp->id = i;

// draw a random number from an exponential distribution
// with a specified mean
double r = ((double) rand())/RAND_MAX;
cp->timeToService = -MEAN_SERVICE_TIME * log(r);

// draw a random number from an exponential distribution
// with a specified mean
r = ((double) rand())/RAND_MAX;
cp->timeUntilNextProcess = -MEAN_INTERARRIVAL_TIME * log(r);

// add this process to the list of processes 
// the linking part of the linked list
cp->np = pp;
pp = cp;
}
rootPointer = cp;

// traverse the list
// begin at last element added to list
// and end with the first element we added to the list
cp = rootPointer;
while(cp != NULL)
{
printf("process id = %d\n", cp->id);
printf("\t service time = %8.f\n", cp->timeToService);
printf("\t interarrival time = %8.4f\n", cp->timeUntilNextProcess);
cp = cp->np;
}
exit(0);
}





























































































































































































































































































 
