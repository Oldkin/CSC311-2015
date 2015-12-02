
// Leon Tabak
// CSC311 Systems Software
// 30 November 2015

#include <stdbool.h>
#include <stdlib.h>

#include "process.h"
#include "queue.h"

// This is that start of a program to simulate the 
// first-come/first-served scheduling of processes 
// for uninterrupted execution in a CPU 
// (or customers in a bank who line up in
// front of a teller's window).

int main( int argc, char** argv ) {

  testQueue( 6 );

  exit(0);
} //  main( int, char** )
