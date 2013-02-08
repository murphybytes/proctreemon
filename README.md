zenmon
======

Description
--------------------------
Zenmon is a process monitor that is designed to analyze the load incurred
by processes and child processes. For example you have a ruby program that
forks and/or executes a bunch of child processes.  This tool is designed to 
assess the impact of the work done by the process and all its children. You don't
have to make any code changes to use zenmon.  Simply use LD_PRELOAD to force the
parent process to load the libzenmon.so library.  

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
Polling frequency in seconds.  Defaults to 1 second.


Output
----------------------------------
The utility emits a row of data for each active process.  The data is in CSV.

timestamp (sec.nsec), parent pid, pid, command line, %user, %nice, %system %idle, ticks user (process), ticks system (process)

You can build a tree of processes for a particular time slice by matching timestamps, finding the parent process
which has pid of zero, then matching the parent process pid to the parent pid in other rows.
For example, rows 1 through 4 are in the same time slice, row 1 is the parent process. Row 2
and row 4 are child processes of process 19691 (row 1) and 19701 (row 3) represents 
a child process of 19697 (row 4) 

1. 1360285611.401648512,0,19691,"(ruby runner.rb)",0.35,0.03,0.20,99.42,0,1
2. 1360285611.401648512,19691,19694,"(ruby runner.rb)",0.35,0.03,0.20,99.42,5,1
3. 1360285611.401648512,19697,19701,"(ruby childchild.rb)",0.35,0.03,0.20,99.42,0,0
4. 1360285611.401648512,19691,19697,"(ruby child.rb)",0.35,0.03,0.20,99.42,0,0
5. 1360285612.419688041,0,19691,"(ruby runner.rb)",0.35,0.03,0.20,99.42,0,2
6. 1360285612.419688041,19691,19694,"(ruby runner.rb)",0.35,0.03,0.20,99.42,5,1
7. 1360285612.419688041,19697,19701,"(ruby childchild.rb)",0.35,0.03,0.20,99.42,0,2
8. 1360285612.419688041,19691,19697,"(ruby child.rb)",0.35,0.03,0.20,99.42,0,2
