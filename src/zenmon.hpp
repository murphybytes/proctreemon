#ifndef __zenmon_hpp__
#define __zenmon_hpp__

#include "common.hpp"
#include "process.hpp"

typedef std::vector<process> processes_t;
typedef std::map< int, processes_t > process_map_t;


class zenmon {
  int pid_;

  FILE* output_;

  void print_children( int parent_pid, const timespec& ts,  const process_map_t& processes ) ;
  
public:
  zenmon() ;
  ~zenmon() ;
  void check() ;

};



#endif
