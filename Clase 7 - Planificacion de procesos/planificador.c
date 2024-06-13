#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int policy;
    struct sched_param param;

    sleep(2);

    // Get the current scheduling policy
    pthread_getschedparam(pthread_self(), &policy, &param);

    // Print the scheduling policy and priority
    if (policy == SCHED_FIFO)
        printf("SCHED_FIFO\n");
    else if (policy == SCHED_RR)
        printf("SCHED_RR\n");
    else if (policy == SCHED_OTHER)
        printf("SCHED_OTHER\n");

    printf("Priority: %d\n", param.sched_priority);

    return NULL;
}

int main() {
    pthread_t thread;
    struct sched_param param;
    int policy;

    // Create a thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // // Set the scheduling policy and priority
    policy = SCHED_FIFO;
    param.sched_priority = 10; // Priority range is system dependent, typically 1-99

    if (pthread_setschedparam(thread, policy, &param) != 0) {
        perror("pthread_setschedparam");
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    return 0;
}