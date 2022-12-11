#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *origen = fopen("origen.txt", "r"); // Abrimos el archivo origen en modo lectura
    FILE *destino = fopen("destino.txt", "w"); // Creamos y abrimos el archivo destino en modo escritura

    char linea[100]; // Creamos un buffer para leer el contenido del archivo
    while (fgets(linea, 100, origen) != NULL) { // Leemos el archivo línea a línea hasta que no queden más líneas
        fprintf(destino, "%s", linea); // Escribimos la línea leída en el archivo destino
    }

    fclose(origen); // Cerramos el archivo origen
    fclose(destino); // Cerramos el archivo destino

    destino = fopen("destino.txt", "r"); // Abrimos el archivo destino en modo lectura
    while (fgets(linea, 100, destino) != NULL) {
        printf("%s", linea); // Imprimimos la línea leída del archivo destino
    }
    printf("\n");
    fclose(destino); // Cerramos el archivo destino

    return 0;
}
