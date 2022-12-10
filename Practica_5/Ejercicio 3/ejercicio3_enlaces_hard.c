#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *archivo = fopen("archivo.txt", "w"); // Creamos el archivo
    fprintf(archivo, "Hola mundo"); // Escribimos en el archivo
    fclose(archivo); // Cerramos el archivo

    symlink("archivo.txt", "enlace_hard1"); // Creamos el primer enlace hard
    symlink("archivo.txt", "enlace_hard2"); // Creamos el segundo enlace hard

    archivo = fopen("enlace_hard1", "a"); // Abrimos el archivo con el primer enlace hard
    fprintf(archivo, "\nAdiós mundo"); // Escribimos en el archivo usando el primer enlace hard
    fclose(archivo); // Cerramos el archivo

    archivo = fopen("enlace_hard2", "r"); // Abrimos el archivo con el segundo enlace hard
    char linea[100]; // Creamos un buffer para leer el contenido del archivo
    while (fgets(linea, 100, archivo) != NULL) { // Leemos el archivo línea a línea hasta que no queden más líneas
        printf("%s", linea); // Imprimimos la línea leída
    }
    fclose(archivo); // Cerramos el segundo enlace hard

    return 0;
}




