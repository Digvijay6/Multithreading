#include "MyThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "allstdlib.h"

struct ThreadControlBlock tcb[MAX_THREADS];
struct statistics stats[MAX_THREADS];

pthread_t masterThread;

void initThreadLibrary(void) {
    masterThread = pthread_self();
    // Initialize thread library data structures
    // You may need to add more initialization steps
}

int create(void (*f)(void)) {
    return createWithArgs((void *(*)(void *))f, NULL);
}

int createWithArgs(void *(*f)(void *), void *arg) {
    // Find an available thread control block (tcb) slot
    int i;
    for (i = 0; i < MAX_THREADS; i++) {
        if (tcb[i].status == FINISHED) {
            tcb[i].status = READY;
            tcb[i].function = f;
            tcb[i].arg = arg;
            tcb[i].result = NULL;
            pthread_create(&(tcb[i].tid), NULL, f, arg);
            initStatistics(&stats[i], i);
            return i;
        }
    }
    return -1; // No available tcb slot
}

int getID(void) {
    pthread_t self = pthread_self();
    for (int i = 0; i < MAX_THREADS; i++) {
        if (pthread_equal(self, tcb[i].tid)) {
            return i;
        }
    }
    return -1; // Not found
}

void dispatch(int signalID) {
    // Implement your scheduler logic here
    // This is a simple example, you may want to replace it with a more sophisticated scheduler
    if (signalID == SIGALRM) {
        yield();
    }
}

void start(void) {
    // Implement your master thread logic here
    // This function may need to be extended depending on your requirements
    signal(SIGALRM, dispatch);
    alarm(1); // Dispatch every 1 second
    while (1) {
        // Your master thread logic
    }
}

void run(int threadID) {
    tcb[threadID].status = RUNNING;
}

void suspend(int threadID) {
    tcb[threadID].status = SUSPENDED;
}

void resume(int threadID) {
    tcb[threadID].status = READY;
}

void yield(void) {
    pthread_kill(tcb[getID()].tid, SIGALRM);
}

void initStatistics(struct statistics *stat, int id) {
    stat->id = id;
    stat->runCount = 0;
    stat->sleepCount = 0;
    // Initialize other fields as needed
}

void deleteThread(int threadID) {
    pthread_cancel(tcb[threadID].tid);
    tcb[threadID].status = FINISHED;
}

void sleep1(int sec) {
    tcb[getID()].status = SLEEPING;
    stats[getID()].sleepCount++;
    sleep(sec);
    tcb[getID()].status = READY;
}

struct statistics *getStatus(int threadID) {
    return &stats[threadID];
}

void clean(void) {
    // Implement any necessary cleanup logic
}

void JOIN(int threadID) {
    pthread_join(tcb[threadID].tid, NULL);
}

void *GetThreadResult(int threadID) {
    return tcb[threadID].result;
}
