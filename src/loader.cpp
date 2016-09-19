#include "proctreemon.hpp"
#include <errno.h>
#include <pthread.h>


pthread_t thread_id;
pthread_mutex_t lock;
pthread_cond_t shutdown_flag;
const int x_update_frequency = get_update_frequency();
const long x_clock_ticks = sysconf( _SC_CLK_TCK );

static void* thread_function( void* ) {
  proctreemon z;

  bool run = true;

  while( run ) {
    pthread_mutex_lock( &lock );
    timespec ts;
    clock_gettime( CLOCK_REALTIME, &ts );
    // TODO: make this configurable via environment or something
    ts.tv_sec += x_update_frequency;
    int rc = pthread_cond_timedwait( &shutdown_flag, &lock, &ts );
    if( ETIMEDOUT == rc ) {
      z.check();
    } else {
      // we got a shut down signal, exit loop
      run = false;
    }

    pthread_mutex_unlock( &lock );
  }


}

__attribute__((constructor)) void init( void ) {

  pthread_mutex_init( &lock, NULL ) ;
  pthread_cond_init( &shutdown_flag, NULL ) ;
  pthread_create( &thread_id, NULL, thread_function, NULL ) ;

}

__attribute__((destructor)) void term( void ) {
  pthread_mutex_lock( &lock ) ;
  pthread_cond_signal( &shutdown_flag );
  pthread_mutex_unlock( &lock );
  pthread_join( thread_id, NULL );

  pthread_mutex_destroy( &lock );
  pthread_cond_destroy( &shutdown_flag );

}
