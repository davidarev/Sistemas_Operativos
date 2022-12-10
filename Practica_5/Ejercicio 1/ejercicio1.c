#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Cadena q se va a escribir
    const char *cadena = "Esto es una prueba";

    // Creaación y apertura del fichero
    int fichero = open("fichero.txt", O_RDONLY | O_CREAT, 0644);
    
    // Comprobación de errores
    if(fichero == -1) {
        perror("Error al abrir el fichero");
        exit(1);
    }

    // Lectura de los 50 primeros caracteres
    cadena = (char *) malloc(50 * sizeof(char));
    read(fichero, cadena, 50);
    printf("Los 50 primeros caracteres son: %s\n", cadena);

    // Lectura del resto del fichero
    int tamano = lseek(fichero, 0, SEEK_END);
    char *cadena2 = (char *) malloc(tamano * sizeof(char));
    lseek(fichero, 50, SEEK_SET);
    read(fichero, cadena2, tamano);
    printf("El resto del fichero es: %s\n", cadena2);

    // Escritura de la cadena en el fichero
    write(fichero, cadena, strlen(cadena));

    // Cierre del fichero
    close(fichero);
    return 0;
}