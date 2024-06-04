#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    // printf("Soy el proceso hijo\n");
    // printf("Mi PID es: %d\n", getpid());

    printf("Argumento 1: %s\n", argv[1]);
    printf("Argumento 2: %s\n", argv[2]);

    sleep(4);

    // Exit code
    exit(1);
}