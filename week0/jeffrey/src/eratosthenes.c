// eratosthenes.c
// Jeffrey Klow
// CSC311 Systems Software
// Nov. 23 2015

#include <stdio.h>
#include <stdlib.h>

// This program will identify all 
// prime numbers that are < SIZE
#define SIZE 1000000

int bitmap[SIZE];

// filter() executes the Sieve of Eratosthenes algorithm
void filter() {
  int i = 0;
  int j = 2;

  // Initialize bitmap as all zeroes
  // 0s are prime, 1s are not prime
  // Note that 0 and 1 are not prime
  // Assume that any value >1 can be prime
  bitmap[0] = 1;
  bitmap[1] = 1;

  for( i = 2; i < SIZE; i++ ) {
    bitmap[i] = 0;
  } // end bitmap init

  // Begin searching for primes
  // 2 is smallest prime, start there
  i = 2;
  while( i < SIZE ) {
    if( bitmap[i] == 0 ) {
      for( j = i + i; j < SIZE; j += i) {
        bitmap[j] = 1;
      } // end for
    } // end if

    i++;
  } // end while
} // end filter()

int main( int argc, char** argv ) {
  // Find all primes < SIZE
  filter();

  // Print results
  int i;
  for( i = 0; i < SIZE; i++ ) {
    if( bitmap[i] == 0) {
      printf( "%d is prime.\n", i);
    }
  }
  exit(0);
} // end main
