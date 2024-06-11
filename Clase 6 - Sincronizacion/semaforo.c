#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

typedef struct{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
} semaforo;

semaforo sem;

void semaforo_init(semaforo* sem, int initial_value){
    pthread_mutex_init(&(sem->mutex), NULL);
    pthread_cond_init(&(sem->condition), NULL);
    sem->value = initial_value;
}

void semaforo_wait(semaforo* sem){
    pthread_mutex_lock(&(sem->mutex));
    while (sem->value <= 0){
        pthread_cond_wait(&(sem->condition), &(sem->mutex));
    }
    sem->value--;
    pthread_mutex_unlock(&(sem->mutex));
}

void semaforo_signal(semaforo* sem){
    pthread_mutex_lock(&(sem->mutex));
    sem->value++;
    pthread_cond_signal(&(sem->condition));
    pthread_mutex_unlock(&(sem->mutex));
}

void* thread(void* args){
    // printf("%s\n", (char*) args);

    printf("%s en espera...\n", (char*) args);
    semaforo_wait(&sem);

    printf("%s obtuvo recursos\n",(char*) args);
    sleep(3);
    printf("%s liberando recursos\n",(char*) args);

    semaforo_signal(&sem);

}

int main(){

    semaforo_init(&sem, 3);
    pthread_t threads[4];

    for(int i = 0; i < 4; i++){
        char *thread_name = (char*) malloc(12*sizeof(char));
        sprintf(thread_name, "Hilo %d", i);
        pthread_create(&threads[i], NULL, thread, thread_name);
    }

    for(int i = 0; i < 4; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}