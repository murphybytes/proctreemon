zenmon
======

Description
--------------------------
Zenmon is a process monitoring utility

Usage
------------------------------
Set the LD_PRELOAD environment variable before the call to the
process you want to monitor.  libzenmon.so will be loaded by
your process and start to record stats.  

LD_PRELOAD=/usr/lib/libzenmon.so ruby mycoolprogram.rb

Environment Variables
-------------------------------
### ZM_WORKING_DIR 
If defined stats on the process will be written to a file in the defined directory. Otherwise
output will be written to STDOUT
### ZM_POLL_FREQUENCY
Polling frequency in milliseconds.  Defaults to 1000 ms.

