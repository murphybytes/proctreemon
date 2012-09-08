#include "zenmon.hpp"
#include "process.hpp"


zenmon::zenmon() 
  :pid_( getpid() ), output(stdout)  {

  char* env_value  = getenv( ZM_WORKINGDIR );
  if( env_value ) {
    timespec ts;
    clock_gettime( CLOCK_REALTIME, &ts );
    
    stringstream ss ;
    ss << env_value << "/" << ts.tv_sec << "." << ts.tv_nsec << "." << pid_; 

    output = fopen(  cstr( ss ), "w" );
  } 


}

zenmon::~zenmon() {
  fprintf( output, "Unloaded for %d\n",  getpid() );
}

void zenmon::check() {
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts );
  process parent( pid_, true ) ;
  parent.write( ts, output );

  glob_t globbuf;
  glob( "/proc/[0-9]*", GLOB_NOSORT, NULL, &globbuf );
  
  for( int i = 0; i < globbuf.gl_pathc; ++i ) {
    int pid = pid_from_path( globbuf.gl_pathv[i] );
    process process( pid );
    if( parent.is_parent( process ) ) {
      process.write( ts, output );
    }
  }

  globfree( &globbuf );
}
