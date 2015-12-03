
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char** argv ) {

  pid_t id = fork();

  if( id == -1 ) {
    printf( "The call to fork() failed.\n" );
  } // if
  else if( id == 0 ) {
    printf( "I am a child process. My id is %4d and my parent's id is %4d.\n", getpid(), getppid() );
  } // if
  else {
    printf( "I am the parent process whose id is %4d and have a child whose process id = %4d\n", getpid(), id );
    int status;
    wait( &status );
  } // else

  exit(0);
} // main( int, char** )
