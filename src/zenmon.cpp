#include "zenmon.hpp"
#include <iostream>
#include <unistd.h>


using namespace std;



zenmon::zenmon() 
  :pid( getpid() ) {

   cout << "Loaded for " << getpid() << endl;
}

zenmon::~zenmon() {
   cout << "Unloaded for " << getpid() << endl;
}

void zenmon::check() {
  cout << "Tick for " << pid << endl;
}
