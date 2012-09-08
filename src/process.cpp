#include "process.hpp"


process::process( int pid, bool parent  )
  :in_(NULL), pid_(pid), parent_(parent) {

  get_command_line();
  get_stat_section();
}

process::~process() {
  if( in_ ) {
    fclose( in_ );
  }
}

void process::get_stat_section() {
  stringstream ss;
  ss << "/proc/" << pid_ << "/stat" ;
  in_ = fopen( cstr( ss ), "r" );
  if( in_ ) {
    int pid;
    
    fscanf( in_, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu"
	    " %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld", 
	    &pid, 
	    command_, 
	    &state_, 
	    &parent_pid_, 
	    &group_id_, 
	    &session_id_,
	    &tty_nr_,
	    &tpgid_,
	    &flags_,
	    &minflt_,
	    &cminflt_,
	    &majflt_,
	    &cmajflt_,
	    &utime_,
	    &stime_,
	    &cutime_,
	    &cstime_,
	    &priority_,
	    &nice_,
	    &num_threads_,
	    &itreal_value_,
	    &start_time_,
	    &vsize_,
	    &rss_,
	    &rss_lim_,
	    &start_code_,
	    &end_code_,
	    &start_stack_,
	    &kstkesp_,
	    &kstkeip_,
	    &signal_,
	    &blocked_,
	    &sigignore_,
	    &sigcatch_,
	    &wchan_,
	    &nswap_,
	    &cnswap_,
	    &exit_signal_,
	    &processor_,
	    &rt_priority_,
	    &policy_,
	    &delayacct_blkio_ticks_,
	    &guest_time_,
	    &cguest_time_ );
  }
}

void process::get_command_line() {

  // first grab the command line
  stringstream ss ;
  ss << "/proc/" << pid_ << "/cmdline";
  
  FILE* in = fopen( cstr( ss ), "r" ) ;
  if( in ) {
    // this is to format the command line that comes back from proc
    // The value read from proc has '0' in place of whitespace, we find these
    // and put the spaces back, also we surround the value with parens
    int read = fread(  &command_line_[1], sizeof(char), MAXLINE - 2, in );
    fclose( in );      

    if( read > 0 ) {
      command_line_[read] = ')';
      command_line_[0] = '(';
      command_line_[read + 1] = 0;
      for( int i = 0; i < read; ++i ) {
	if( !command_line_[i] ) {
	  command_line_[i] = ' ';
	} 
      }
    } else {
      command_line_[0] = 0;
    }

  }

}


bool process::is_parent( const process& potential_child ) const {
  return pid_ == potential_child.parent_pid_;
}

void process::write( const timespec& ts, FILE* out ) {
  
  if( in_ ) {

    fprintf( out, "%ld.%ld %d %d %s\n", 
	     ts.tv_sec, 
	     ts.tv_nsec, 
	     parent_ ? 0 : parent_pid_,
	     pid_,
	     command_line_  );
  }
}

 
