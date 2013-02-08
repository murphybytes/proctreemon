#include "process.hpp"


process::process( int pid, const cpu& cpu,  bool parent  )
  :exists_(false), pid_(pid), parent_(parent), cpu_(cpu) {

  get_command_line();
  get_stat_section();
}

process::~process() {

}

void process::get_stat_section() {
  stringstream ss;
  ss << "/proc/" << pid_ << "/stat" ;
  FILE* in = fopen( cstr( ss ), "r" );
  if( in ) {
    int pid;
    
    fscanf( in, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu"
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

    fclose( in );

    assert( pid == pid_ );

    exists_ = true; // indicate this process still exists
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
      strcpy( command_line_, "(?)" );
    }
  }
}


bool process::is_parent( const process& potential_child ) const {
  return pid_ == potential_child.parent_pid_;
}

void process::write( const timespec& ts, FILE* out ) {
  
  if( exists_ ) {


    // seconds.nsecs, parent_pid, pid, (command line), user%, nice%, system%, idle%, process user ticks, process system ticks 
    fprintf( out, "%ld.%ld,%d,%d,\"%s\",%3.2f,%3.2f,%3.2f,%3.2f,%lu,%lu\n", 
	     ts.tv_sec, 
	     ts.tv_nsec, 
	     parent_ ? 0 : parent_pid_,
	     pid_,
	     command_line_,
	     cpu_.get_user(),
	     cpu_.get_nice(),
	     cpu_.get_system(),
	     cpu_.get_idle(),
	     utime_,
	     stime_);
  }
}

 
