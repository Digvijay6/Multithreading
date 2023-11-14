#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "allstdlib.h"
#include <pthread.h>

#define MAX_THREADS 10

typedef enum {
    READY,
    RUNNING,
    SUSPENDED,
    SLEEPING,
    FINISHED
} ThreadStatus;

struct ThreadControlBlock {
    pthread_t tid;         // Thread ID
    int threadID;          // Thread number
    ThreadStatus status;    // Thread status
    void *(*function)(void *);  // Thread function
    void *arg;             // Function argument
    void *result;          // Thread result
};

struct statistics {
    int id;
    int runCount;
    int sleepCount;
    // Add more fields as needed
};

void initThreadLibrary(void);
int create(void (*f)(void));
int createWithArgs(void *(*f)(void *), void *arg);
int getID(void);
void dispatch(int signalID);
void start(void);
void run(int threadID);
void suspend(int threadID);
void resume(int threadID);
void yield(void);
void initStatistics(struct statistics *stat, int id);
void deleteThread(int threadID);
void sleep1(int sec);
struct statistics *getStatus(int threadID);
int createWithArgs(void *(*f)(void *), void *arg);
void clean(void);
void JOIN(int threadID);
void *GetThreadResult(int threadID);

#endif // MYTHREAD_H
