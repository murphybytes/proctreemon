#ifndef __zenmon_hpp__
#define __zenmon_hpp__

#include "common.hpp"



class zenmon {
  int pid_;

  FILE* output;
  
public:
  zenmon() ;
  ~zenmon() ;
  void check() ;

};



#endif
