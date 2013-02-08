#ifndef __cpu_hpp__
#define __cpu_hpp__

#include "common.hpp"

class cpu {
  float user_;
  float nice_;
  float system_;
  float idle_;
  unsigned long user_ticks_;
  unsigned long system_ticks_;
public:
  cpu();
  ~cpu();
  float get_user() const { return user_; }
  float get_nice() const { return nice_; }
  float get_system() const { return system_; }
  float get_idle() const { return idle_; }
  unsigned long get_user_ticks() const { return user_ticks_; }
  unsigned long get_system_ticks() const { return system_ticks_; }
  
};


#endif
