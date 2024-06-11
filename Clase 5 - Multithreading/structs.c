#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <pthread.h>

#define THREAD_COUNT 5

struct args_struct {
    int id;
    char* mensaje;
};

void* myFunction(void* args){

    // int* id = (int*)args;

    struct args_struct* myArgs = (struct args_struct*) args;
    myArgs -> id = myArgs -> id + 2;

    printf("Id: %d\n", myArgs->id);
    printf("Mensaje: %s\n", myArgs->mensaje);
    sleep(5);
    printf("Finalizado\n");
}

int main(){

    pthread_t thread, thread2;

    char cadena[] = "Sistemas Operativos 2";
    char cadena2[] = "Seccion A";

    struct args_struct* myArgs = malloc(sizeof(struct args_struct));
    myArgs -> id = 64;
    myArgs -> mensaje = cadena;
    
    pthread_create(&thread, NULL, myFunction, myArgs);
    pthread_create(&thread2, NULL, myFunction, myArgs);
    
    printf("Esperando a hilo...\n");
    pthread_join(thread, NULL);
    printf("Hilo terminado!\n");

    return 0;
}