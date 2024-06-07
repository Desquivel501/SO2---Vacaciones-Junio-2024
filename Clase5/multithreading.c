#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <pthread.h>

void* myFunction(void* args){
    printf("Imprimimiendo desde: %s\n", (char*)args);
    sleep(5);
    printf("Finalizado %s\n", (char*)args);
}

int main(){

    pthread_t thread, thread2;

    pthread_create(&thread, NULL, myFunction, "Hilo 1");
    pthread_create(&thread2, NULL, myFunction, "Hilo 2");

    printf("Esperando a hilo...\n");
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    printf("Hilo terminado!\n");

    return 0;
}