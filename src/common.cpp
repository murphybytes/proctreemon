#include "common.hpp"



const char* const cstr( const stringstream& ss ) {
  return ss.str().c_str();
}

int get_update_frequency() {
  int result = 1;
  char* buff = getenv( ZM_POLL_FREQUENCY );
  if( buff ) {
    unsigned int temp = atoi( buff );
    if( temp ) {
      result = temp;
    }
  } 

  return result;
}

int pid_from_path( const char * const path ) {
  char buffer[255];
  memset( buffer, 0, 255 );
  buffer[0] = '0'; // just in case
  char* p = &buffer[0];

  for( int i = 0; ; ++i ) {
    if( path[i] == 0 ) {
      break;
    } 
    if( path[i] >= '0' && path[i] <= '9' ) {
      *p = path[i];
      p++;
    }
  }

  return atoi( buffer );

}
