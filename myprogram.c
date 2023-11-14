#include "MyThread.h"
#include <stdio.h>

void *sampleFunction(void *arg) {
    int id = getID();
    printf("Thread %d is running\n", id);
    for (int i = 0; i < 5; i++) {
        printf("Thread %d: %d\n", id, i);
        sleep(1);
    }
    printf("Thread %d is finished\n", id);
    return NULL;
}

int main() {
    initThreadLibrary();

    int thread1 = create(sampleFunction);
    int thread2 = create(sampleFunction);

    start();

    return 0;
}
