#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <pthread.h>

#define THREAD_COUNT 5

void* myFunction(void* args){

    int* id = (int*)args;

    printf("Imprimimiendo desde: %d\n", *id);
    sleep(5);
    printf("Finalizado %d\n",  *id);
}

int main(){

    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++){

        int* a = malloc(sizeof(int));
        *a = i;

        pthread_create(&threads[i], NULL, myFunction, a);
    }

    for (int i = 0; i < THREAD_COUNT; i++){
        pthread_join(threads[i], NULL);
    }


    // pthread_create(&thread, NULL, myFunction, "Hilo 1");
    // pthread_create(&thread2, NULL, myFunction, "Hilo 2");

    // printf("Esperando a hilo...\n");
    // pthread_join(thread, NULL);
    // pthread_join(thread2, NULL);
    // printf("Hilo terminado!\n");

    return 0;
}