#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

int main(int argc, char **argv) {
    pid_t pid;
    int pipeA[2], pipeB[2], readbytes;
    char buffer[SIZE];

    pipe(pipeA);
    pipe(pipeB);

    if((pid = fork() == 0)) { // fork
        close(pipeA[1]); // Cerramos escritura de pipeA
        close(pipeB[0]); // Cerramos lectura de pipeB

        while((readbytes = read(pipeA[0], buffer, SIZE)) > 0) {
            write(1, buffer, readbytes);
        }
        close(pipeA[0]);

        strcpy(buffer, "Soy el hijo\n");
        write(pipeB[1], buffer, strlen(buffer));
        close(pipeB[1]); // Cerramos escritura de pipeB

    } else {
        close(pipeA[0]); // Cerramos lectura de pipeA
        close(pipeB[1]); // Cerramos escritura de pipeB

        strcpy(buffer, "Soy el padre\n");
        write(pipeA[1], buffer, strlen(buffer));
        close(pipeA[1]); // Cerramos escritura de pipeA

        while((readbytes = read(pipeB[0], buffer, SIZE)) > 0) {
            write(1, buffer, readbytes);
        }
        close(pipeB[0]); // Cerramos lectura de pipeB
    }

    waitpid(pid, NULL, 0);
    exit(0);
}