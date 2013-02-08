#ifndef __common_hpp__
#define __common_hpp__

#include "constants.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <glob.h>
#include <assert.h>

using namespace std;

extern const int x_update_frequency;
extern const long x_clock_ticks;

const char * const cstr( const stringstream& ss ) ;
int pid_from_path( const char * const path );
int get_update_frequency();

#endif
