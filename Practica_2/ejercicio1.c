#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t thread_padre, thread1, thread2; //Declaración de los tres threads
pthread_attr_t attribute; //Atributos de los threads

void *factorial(void *arg) {
    int fact = 1;
    int num = atoi((char *)arg);
	if(num < 0) printf("Negative number, no factorial");
    if(num == 0) fact = 0;
    else{
        for(int i = 1; i <= num; i++){	
		 fact = fact * i;        
	    }
    }
    
	printf("Factorial de %d = %d \n\n", num, fact);
}

int main(int argc, char *argv[]) {
    thread_padre = pthread_self();
    pthread_attr_init(&attribute); //Inicializa los parámetros de los threads por defecto

    //Creamos los dos threads necesarios
    pthread_create(&thread1, &attribute, factorial, (void *) argv[1]);
    pthread_create(&thread2, &attribute, factorial, (void *) argv[2]);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_exit(NULL); //Mata el thread
}