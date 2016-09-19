#ifndef __proctreemon_hpp__
#define __proctreemon_hpp__

#include "common.hpp"
#include "process.hpp"

typedef std::vector<process> processes_t;
typedef std::map< int, processes_t > process_map_t;


class proctreemon {
  int pid_;

  FILE* output_;

  void print_children( int parent_pid, const timespec& ts,  const process_map_t& processes ) ;

public:
  proctreemon() ;
  ~proctreemon() ;
  void check() ;

};



#endif
