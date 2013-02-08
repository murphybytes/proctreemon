#include "cpu.hpp"

cpu::cpu() {
  FILE* fin = fopen( "/proc/stat", "r" );
  if( fin ) {
    char buffer[MAXLINE];
    fgets( buffer, MAXLINE, fin );

    fclose( fin );
    unsigned long nice, idle, total, unused0, unused1, unused2, unused3, unused4, unused5;
    char cpu[5];
    sscanf( buffer, 
	    "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", 
	    cpu,
	    &user_ticks_,
	    &nice, 
	    &system_ticks_,
	    &idle,
	    &unused0,
	    &unused1,
	    &unused2,
	    &unused3,
	    &unused4,
	    &unused5 );
    total = user_ticks_ + nice + system_ticks_ + idle;
    user_ = ((float)user_ticks_ / total ) * 100.0;
    nice_ = ((float)nice / total ) * 100.0;
    system_ = ((float)system_ticks_ / total ) * 100.0;
    idle_ = ((float)idle / total ) * 100.0;

	    
  }
}

cpu::~cpu() {
}
