#ifndef __common_hpp__
#define __common_hpp__

#include "constants.hpp"
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <glob.h>

using namespace std;

const char * const cstr( const stringstream& ss ) ;
int pid_from_path( const char * const path ); 
#endif
