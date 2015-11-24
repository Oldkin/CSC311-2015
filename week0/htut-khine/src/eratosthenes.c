
// eratosthenes.c
// HTUT KHINE 
// CSC311 Systems Software
// 23 November 2015

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000000
// this program will identify all
// prime numbers that are < SIZE

// filter() executes the Sieve of Eratosthenes
// algorithm
  
  // initialize bitmap (array of zeroes and ones)
  // 0 and 1 are not prime
  // begin by assuming that any integer >= 2 could
  // be prime

    // bitmap[i] = 0 means i could be prime
    // (the next loop will determine if i is really prime)



  // 2 is the smallest prime number so
  // start the search for prime numbers
  // at 2

      // if i is prime, then all of its 
      // multiples are composite (not prime)

int bitmap[SIZE]; 
void filter(){
  int i = 0; 
  int j = 2; 
  bitmap[0] = 1; 
  bitmap[1] = 1; 
  for (i = 2; i < SIZE; i++){
    bitmap[i] = 0; 
  }

  i = 2; 
  while (i < SIZE){
    if (bitmap[i] == 0){
      for (j = i+1; j < SIZE; j += i){
        bitmap[j] = 1; 
      }
    }
    i++; 
  }
}
int main( int argc, char** argv ) {
  // find all of the prime numbers < SIZE

  // print all of the prime numbers < SIZE

  // printf( "Hello from eratosthenes!\n" );
  filter(); 
  int i; 
  for (i =0; i < SIZE; i++){
    if (bitmap[i] == 0){
      printf("%d is prime.\n", i); 
    }
  }
  exit(0);
} // main( int, char** )
