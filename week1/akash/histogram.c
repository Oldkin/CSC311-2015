#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10.0
#define BINS 100
#define TRIALS 1000000

int main( int argc, char** argv ) {
  time_t t;
  srand( (unsigned) time(&t) );

  int histogram[BINS];

  int i;
  for( i = 0; i < BINS; i++ ) {
    histogram[i] = 0;
  } // for

  double mean = 1.0;
  for( i = 0; i < TRIALS; i++ ) {
    double x = -mean * log(((double) rand())/RAND_MAX );
    //printf( "%8.4f\n", x );
    if( x < 10.0 ) {
      histogram[(int) floor(x/MAX * BINS)]++;
    } // if
  } // for

  for( i = 0; i < BINS; i++ ) {
    printf( "Number of values between, %8.4f, and, %8.4f, is, %4d,\n",
	    (i * MAX/BINS), ((i + 1) * MAX/BINS), histogram[i] );
  } // for
} // main( int, char** )
