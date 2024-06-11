#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
    char string[] = "Sistemas Operativos 2\n";
    char readbuffer[80]; //Buffer que se usara para leer el pip

    int fd[2]; //Descriptor del pipe
    pipe(fd); //Se inicia el pipe
    // fd[0] -> Se utiliza para leer el pipe
    // fd[1] -> Se utiliza para escribir en el pipe

    pid_t pid = fork(); //Se realiza el fork
    
    if(pid == -1){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        close(fd[1]); //Se cierra el lado de escritura, pues el hijo no lo utiliza

        /*Se lee el pipe*/
        read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Cadena leida: %s", readbuffer);

    } else {
		close(fd[0]); //Se cierra el lado de lectura, pues el padre no lo utiliza

        /*Se escribe la cadena en el pipe*/
        write(fd[1], string, (strlen(string)+1));
        exit(0);
    }
    
    return(0);
}