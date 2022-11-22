#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

pthread_mutex_t lock; //función que bloquea algo

pthread_t thread_1; //pthread_t es el tipo de datos que se utiliza para identificar de forma única un subproceso
pthread_t thread_2;
pthread_t thread_main;

pthread_attr_t attr;

int pthread_mutex_lock(pthread_mutex_t *lock);

//Thread 1: Numeros Impares
void *impar(void *arg){	
    pthread_mutex_lock(&lock);
    int size = atoi((char*)arg); //'atoi()' convierte una cadena a un valor numero -int-
	double array[size]; //creamos un array cuyo tamaño es 'size'
    for(int i = 0; i < size; i++){
        if(i % 2 != 0){
            array[i] = i * i; 
            printf("%d: %.f \n", i, array[i]);
        }	
    }   
    pthread_mutex_unlock(&lock); //hace que uno de los subprocesos regrese de pthread_mutex_lock() con el objeto mutex adquirido
    pthread_exit(NULL);
}

//Thread 2: Numeros Pares
void *par(void *arg){	
    pthread_mutex_lock(&lock);
    int size = atoi((char*)arg);
	double array[size];
    for(int i = 0; i < size; i++){
        if(i % 2 == 0){
            array[i] = i * i;
            printf("%d: %.f \n", i, array[i]);
        }	
    }
    pthread_mutex_unlock(&lock); 
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    thread_main = pthread_self();
    pthread_attr_init(&attr); //función que inicializa el objeto de atributos de subproceso al que apunta attr
    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread_1, &attr, impar, (void*) argv[1]); //devuelve pthread_t y lo usa en llamadas a funciones que requieren un ID de subproceso
    pthread_create(&thread_2, &attr, par, (void*) argv[1]);  

    //funcion que espera la terminacion del thread y podemos comprobar si hay errores utilizando el valor de retorno
    pthread_join(thread_1, NULL); 
    pthread_join(thread_2, NULL);

	pthread_exit(NULL); //función que llama un thread para terminar su propia ejecución
}