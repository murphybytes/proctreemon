#include "zenmon.hpp"


zenmon::zenmon() 
  :pid_( getpid() ), output_(stdout)  {

  char* env_value  = getenv( ZM_WORKINGDIR );
  if( env_value ) {
    timespec ts;
    clock_gettime( CLOCK_REALTIME, &ts );
    
    stringstream ss ;
    ss << env_value << "/" << ts.tv_sec << "." << ts.tv_nsec << "." << pid_; 

    output_ = fopen(  cstr( ss ), "w" );
  }
}

zenmon::~zenmon() {
}

void zenmon::check() {
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts );
  cpu cpu;
  process parent( pid_, cpu, true ) ;
  parent.write( ts, output_ );

  process_map_t process_map;

  glob_t globbuf;
  glob( "/proc/[0-9]*", GLOB_NOSORT, NULL, &globbuf );
  
  // get list of all processes that are candidates to be included
  // in our tree
  for( int i = 0; i < globbuf.gl_pathc; ++i ) {
    int pid = pid_from_path( globbuf.gl_pathv[i] );
    process candidate_process( pid, cpu ) ; 
    process_map[candidate_process.get_parent_pid()].push_back( candidate_process  );
  }

  globfree( &globbuf );

  print_children( pid_, ts, process_map );

}

void zenmon::print_children( int parent_pid, const timespec& ts, const process_map_t& processes ) {
  if( processes.count( parent_pid ) ) {
    process_map_t::const_iterator element  = processes.find( parent_pid );
    processes_t children = element->second;
    for( processes_t::iterator child = children.begin(); child != children.end(); ++child ) {
      print_children( child->get_pid(), ts, processes );
      child->write( ts, output_ );
    }
  }
}
