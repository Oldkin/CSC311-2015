// eratoshenes.c
// Joseph Sterchele
// CSC311 System Software
// 23 Novemeber 2015

#include <stdio.h>
#include <stdlib.h>

// this program will identify all
// prime numbers that are < SIZE
#define size 1000000

int bitmap[SIZE] ;

// filter() executes the Sieve of Eratoshenes algorithm
void filter() {
  int i = 0;
  int j = 2;

  // initialize bitmap ( array of zero and ones ) 
  // 0 and 1 are not prime
  // begin by assuming that any integer >= 2 could be prime
  bitmap[0] = 1;
  bitmap[1] = 1;
  for( i = 2; i < SIZE; i++ ) {
    // bitmap[1] = 0 means i could be prime (next loops determines if i is really prime) 
    bitmap[i] = 0 ;
  }
  // 2 is the smallest prime number so start the search for prime numbers at 2
  i = 2;
  while( i < SIZE ) {
    if( bitmap[i] == 0 ){
      // if i is prime, then all of its multiples are composite (not prime)
      for( j = i + i; j < SIZE; j += i ) {
	bitmap[j] = 1;
      }
    }
    i++;
  }
}


int main( int argc, char** argv ) {
  //find all of the prime numbers < SIZE
  filter();

  //print our all of the prime numbers
  int i;
  for( i = 0; i < SIZE; i++){
    if( bitmap[i] == 0 ) {
      prinf( "%d_is_prime.\n", i );
    }
  }
  exit(0);
}

