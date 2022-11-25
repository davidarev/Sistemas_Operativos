#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h> 

int main(int argc, char *argv[]) {
    int pipes[2]; // 2 pipes, pipe de escritura y pipe de lectura
    if(fork() == 0) { // Creación del proceso 1
        pipe(pipes); // Creación del pipe
        if(fork() == 0) { // Creación del proceso 2
            dup2(pipes[1], STDOUT_FILENO); // Redirección de la salida estándar al pipe de escritura
            close(pipes[0]); // Cierre del pipe de lectura
            close(pipes[1]); // Cierre del pipe de escritura
            execlp("grep", "grep", argv[1], argv[2], NULL); // Ejecución del comando grep
        } else { 
            if(fork() == 0) { // Creación del proceso 3
                dup2(pipes[1], STDOUT_FILENO);
                close(pipes[0]); close(pipes[1]); 
                execlp("grep", "grep", argv[1], argv[3], NULL);
            } else {
                dup2(pipes[0], STDIN_FILENO);
                close(pipes[0]); close(pipes[1]); 
                int file_3 = creat(argv[4], 00644); // Creación del fichero 3
                dup2(file_3, STDOUT_FILENO); // Redirección de la salida estándar al fichero 3
                execlp("wc", "wc", "-l", NULL); // Ejecución del comando wc -l para contar las coincidencias de la búsqueda
                close(file_3); // Cierre del fichero 3
            }
        }
    }
    return 0;
}
