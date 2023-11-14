# Multithreading

Simple Thread Library
This is a simple thread library written in C that provides basic functionalities for thread management. 
The library supports creating, deleting, suspending, resuming, running, and sleeping threads. Additionally, it includes functions for yielding control, initializing statistics, and obtaining thread status.

Usage(Ubuntu)

Compile the Library:
gcc -c MyThread.c

Compile Your Program:
gcc -c Yourprogram.c

Link the Object Files:

gcc myThread.o myprogram.o -o executable
Run the Executable:
./executable

On Windows, you can use the Microsoft Visual C++ Compiler (cl) and the linker (link) to compile and run your program.
Here are the corresponding commands:

cl /c MyThread.c

cl /c Yourprogram.c

link MyThread.obj Yourprogram.obj -out:executable

executable

Library Functions:

int create(void (*f)(void)): Create a thread without function arguments.

int createWithArgs(void *(*f)(void *), void *arg): Create a thread with function arguments.

int getID(void): Get the ID of the current thread.

void dispatch(int signalID): Scheduler function.

void start(void): Start executing threads.

void run(int threadID): Set thread status to RUNNING.

void suspend(int threadID): Set thread status to SUSPENDED.

void resume(int threadID): Set thread status to READY.

void yield(void): Yield control to the scheduler.

void initStatistics(struct statistics* stat, int id): Initialize thread statistics.

void deleteThread(int threadID): Delete a thread.

void sleep1(int sec): Put the thread to sleep.

struct statistics* getStatus(int threadID): Get thread statistics.

void clean(void): Stop the master thread.

void JOIN(int threadID): Bonus: Join a thread.

void* GetThreadResult(int threadID): Bonus: Get thread result.

Dependencies:

This code assumes the use of the pthread library for thread management.

Include allstdlib.h for commonly used standard headers and macros.
