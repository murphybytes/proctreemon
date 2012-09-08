#ifndef __process_hpp__
#define __process_hpp__

#include "common.hpp"

class process {
  FILE* in_;
  char command_line_[MAXLINE];
  bool parent_;

  int pid_;
  char command_[MAXLINE];
  char state_;
  int parent_pid_;
  int group_id_;
  int session_id_;
  int tty_nr_;
  int tpgid_;
  unsigned int flags_;
  unsigned long minflt_;
  unsigned long cminflt_;
  unsigned long majflt_;
  unsigned long cmajflt_;
  unsigned long utime_;
  unsigned long stime_;
  long cutime_;
  long cstime_;
  long priority_;
  long nice_;
  long num_threads_;
  long itreal_value_;
  unsigned long long start_time_;
  unsigned long vsize_;
  long rss_;
  unsigned long rss_lim_;
  unsigned long start_code_;
  unsigned long end_code_;
  unsigned long start_stack_;
  unsigned long kstkesp_;
  unsigned long kstkeip_;
  unsigned long signal_;
  unsigned long blocked_;
  unsigned long sigignore_;
  unsigned long sigcatch_;
  unsigned long wchan_;
  unsigned long nswap_;
  unsigned long cnswap_;
  int exit_signal_;
  int processor_;
  unsigned int rt_priority_;
  unsigned int policy_;
  unsigned long long delayacct_blkio_ticks_;
  unsigned long guest_time_;
  long cguest_time_;
    


  void get_command_line() ;
  void get_stat_section() ;
public:
  process( int pid, bool parent = false ) ;
  ~process();
  void write( const timespec& ts, FILE* out ) ;
  bool is_parent( const process& potential_child ) const;
};

#endif
