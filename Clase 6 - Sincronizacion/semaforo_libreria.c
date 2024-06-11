#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

// Incluimos la libreria de C para semaforo
#include<semaphore.h>

// Inicializamos la variable del semaforo s
sem_t s; 
  
void* thread(void* arg) 
{ 
    //wait 
    sem_wait(&s); 
    printf("Inicio - %s\n", (char*) arg); 
  
    sleep(4); 
      
    //signal 
    printf("Termino - %s\n", (char*) arg); 
    sem_post(&s); 
} 
  
int main() 
{ 
    sem_init(&s, 0, 2);  // Inicializamos nuestro semaforo
    // Puntero del semaforo, si este semaforo podra ser accediro por otro proceso (0,1), la cantidad de recursos

    pthread_t threads[4];

    for(int i = 0; i < 4; i++){
        char *thread_name = (char*) malloc(12*sizeof(char));
        sprintf(thread_name, "Hilo %d", i);
        pthread_create(&threads[i], NULL, thread, thread_name);
    }

    for(int i = 0; i < 4; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&s);  // Liberamos los recursos del semaforo

    return 0; 
} 