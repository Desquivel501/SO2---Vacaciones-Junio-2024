#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* high_priority_thread(void* arg) {
    sleep(2);
    printf("High priority thread running\n");
    for (int i = 0; i < 5; ++i) {
        printf("High priority thread working %d\n", i);
        sleep(1);  // Simulate work
    }
    return NULL;
}

void* low_priority_thread(void* arg) {
    sleep(2);
    printf("Low priority thread running\n");
    for (int i = 0; i < 5; ++i) {
        printf("Low priority thread working %d\n", i);
        sleep(1);  // Simulate work
    }
    return NULL;
}

int main() {

    pthread_t high_thread, low_thread;
    struct sched_param high_param, low_param;

    // Create high priority thread
    pthread_create(&high_thread, NULL, high_priority_thread, NULL);
    high_param.sched_priority = 60;  // Higher priority
    pthread_setschedparam(high_thread, SCHED_FIFO, &high_param);

    // Create low priority thread
    pthread_create(&low_thread, NULL, low_priority_thread, NULL);
    low_param.sched_priority = 20;  // Lower priority
    pthread_setschedparam(low_thread, SCHED_FIFO, &low_param);

    // Wait for threads to finish
    pthread_join(high_thread, NULL);
    pthread_join(low_thread, NULL);

    return 0;
}