#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

  
pthread_mutex_t lock;
  
void* thread(void* arg) 
{ 
    //wait 
    pthread_mutex_lock(&lock); 
    printf("Inicio - %s\n", (char*) arg); 
  
    sleep(4); 
      
    //signal 
    printf("Termino - %s\n", (char*) arg); 
    pthread_mutex_unlock(&lock); 
} 
  
  
int main() 
{ 
    pthread_mutex_init(&lock, NULL);  // Inicializamos nuestro mutex

    pthread_t t1,t2; 

    pthread_create(&t1, NULL, thread, "Hilo1"); 
    pthread_create(&t2, NULL, thread, "Hilo2"); 
    
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 

    pthread_mutex_destroy(&lock);  // Liberamos los recursos del semaforo

    return 0; 
} 