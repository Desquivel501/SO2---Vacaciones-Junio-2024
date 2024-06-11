#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){

    int fd[2]; // Descriptor del pipe
    pipe(fd);
    // fd[0] -> Se utiliza para leer el pipe
    // fd[1] -> Se utiliza para escribir en el pipe

    pid_t pid = fork();

    if(pid == -1){
        perror("Fork");
        exit(1);
    }

    if(pid == 0){
        // printf("Proceso hijo\n");
        close(fd[1]);

        char cadena[80];
        read(fd[0], cadena, sizeof(cadena));

        printf("Cadena leida: %s\n", cadena);

        close(fd[0]);
        exit(1); 

    } else {
        // printf("Proceso padre\n");
        close(fd[0]);

        char cadena[] = "Hola mundo!\n";
        write(fd[1], cadena, strlen(cadena) + 1);

        close(fd[1]);
        exit(0);

    }
}