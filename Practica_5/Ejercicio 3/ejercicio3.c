#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { // Si no se pasó ningún argumento
        printf("Error: debe ingresar el nombre de un directorio como parámetro.\n"); // Imprimimos un mensaje de error
        return 1;
    }

    DIR *directorio = opendir(argv[1]); // Abrimos el directorio pasado como parámetro
    if (directorio == NULL) { // Si no se pudo abrir el directorio
        printf("Error: no se puede abrir el directorio '%s'.\n", argv[1]); // Imprimimos un mensaje de error
        return 1;
    }

    long long suma_bytes = 0; // Creamos una variable para guardar la suma de los bytes de los archivos
    struct dirent *elemento; // Creamos una variable para guardar la información de cada elemento del directorio

    while ((elemento = readdir(directorio)) != NULL) { // Leemos el directorio elemento a elemento hasta que no queden más elementos
        struct stat info_elemento; // Creamos una variable para guardar la información del elemento
        stat(elemento->d_name, &info_elemento); // Obtenemos la información del elemento
        if (S_ISDIR(info_elemento.st_mode)) { // Si el elemento es un directorio
            suma_bytes += info_elemento.st_size; // Sumamos los bytes del directorio a la suma total
            printf("Directorio: %s\n", elemento->d_name);
            printf("Tamaño: %ld bytes\n", info_elemento.st_size); // Imprimimos el tamaño del directorio en bytes siendo de tipo long int
            printf("Número de enlaces: %d\n", info_elemento.st_nlink);
            printf("Inodo: %ld\n", info_elemento.st_ino); // Imprimimos el número de inodo del directorio siendo de tipo long int
            printf("Permisos: %o\n", info_elemento.st_mode);
            printf("Enlace simbólico: %s\n\n", S_ISLNK(info_elemento.st_mode) ? "sí" : "no"); // Si el elemento es un enlace simbólico imprimimos "sí", sino imprimimos "no"
        }
    }
    closedir(directorio); // Cerramos el directorio
    printf("Suma total de bytes ocupados: %lld bytes\n", suma_bytes); // Imprimimos la suma total de bytes

    return 0;
}
