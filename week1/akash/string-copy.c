

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv ) {
  char *a = "Digital Equipment Corporation" ;
  char *b = (char *) malloc( 80 * sizeof(char) ) ;

  printf( "Name of company = %s\n", a ) ;



  char *c = b ;
  while( *a != '\0' ) {
    //*(b++) = *(a++) ;

    *b = *a ;
    a++ ;
    b++ ;

    //a = (char *) (a + 1) ;
    //b = (char *) (b + 1) ;
  }

  //strcpy( b, a ) ;


  printf( "Name of company = %s\n", c ) ;


}
