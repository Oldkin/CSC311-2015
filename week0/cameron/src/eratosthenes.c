
// eratosthenes.c
// Norbert Wiener
// CSC311 Systems Software
// 23 November 2015

#include <stdio.h>
#include <stdlib.h>

// this program will identify all
// prime numbers that are < SIZE
#define SIZE 1000000

int bitmap[SIZE];

// filter() executes the Sieve of Eratosthenes
// algorithm
void filter() {
  int i = 0;
  int j = 2;
  
  // initialize bitmap (array of zeroes and ones)
  // 0 and 1 are not prime
  // begin by assuming that any integer >= 2 could
  // be prime
  bitmap[0] = 1;
  bitmap[1] = 1;
  for( i = 2; i < SIZE; i++ ) {
    // bitmap[i] = 0 means i could be prime
    // (the next loop will determine if i is really prime)
    bitmap[i] = 0;
  }

  // 2 is the smallest prime number so
  // start the search for prime numbers
  // at 2
  i = 2;
  while( i < SIZE ) {
    if(bitmap[i] == 0){
      // if i is prime, then all of its 
      // multiples are composite (not prime)
      for(j = i + i; j < SIZE; j += i ) {
	bitmap[j] = i;
      }
    }

    i++;
  }
}

int main( int argc, char** argv ) {
  // find all of the prime numbers < SIZE
  filter();

  // print all of the prime numbers < SIZE
  int i;
  for(i = 0; i < SIZE; i++){
    if(bitmap[i] == 0){
      printf("%d is prime.\n", i);
    }
  }

  exit(0);
} // main( int, char** )
