#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipes[2]; // 2 pipes, pipe de escritura y pipe de lectura

    if(fork() == 0) { // Creación del proceso 1
        pipe(pipes);
        if(fork() == 0) { // Creación del proceso 2
            dup2(pipes[1], STDOUT_FILENO);
            close(pipes[0]); // pipe de escritura
            close(pipes[1]); // pipe de lectura
            execlp("grep", "grep", argv[1], argv[2], NULL);
        } else {
            if(fork() == 0) { // Creación del proceso 3
                dup2(pipes[1], STDOUT_FILENO);
                close(pipes[0]); // pipe de escritura
                close(pipes[1]); // pipe de lectura
                execlp("grep", "grep", argv[1], argv[3], NULL);
            } else {
                
                dup2(pipes[0], STDIN_FILENO);
                
                close(pipes[0]); // pipe de escritura
                close(pipes[1]); // pipe de lectura
                int file_3 = creat(argv[4], 00644);
                dup2(file_3, STDOUT_FILENO);

                execlp("wc", "wc", "-l", NULL); // Cuenta el número de coincidencias entre el fichero1 y el fichero2
                close(file_3);
            }
        }
    }
        return 0;
    }