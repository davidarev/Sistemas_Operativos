#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 0

pthread_t thread1, thread2, thread;
pthread_attr_t attr;
sem_t semaphore_productor, semaphore_consumidor;

int buffer[MAX];

// Función productor
void *semaphoreProductor(void *arg){
    for (int i = 0; i < MAX; i++){
        sem_wait(&semaphore_productor);
        if (buffer[i] == 0){
            buffer[i] = i + 1;
            int data = buffer[i];
            printf("Dato producido: %d\n", data);
            for (int i = 0; i < MAX; i++){
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semaphore_consumidor);
        sleep(random() % 10);
    }
    pthread_exit(NULL);
}

// Función consumidor
void *semaphoreConsumidor(void *arg){
    for (int i = MAX; i > 0; i--){
        sem_wait(&semaphore_consumidor);
        if (buffer[i] != 0){
            int data = buffer[i];
            buffer[i] = 0;
            printf("Dato consumido: %d\n", data);
            for (int i = 0; i < 10; i++){
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semaphore_productor);
        sleep(random() % 1);
    }
    pthread_exit(NULL);
}


int main(int argc, char **argv) {
    thread = pthread_self();

    pthread_attr_init(&attr);

    sem_init(&semaphore_productor, 0, MAX);
    sem_init(&semaphore_consumidor, 0, 0);

    pthread_create(&thread1, &attr, semaphoreProductor, NULL);
    pthread_create(&thread2, &attr, semaphoreConsumidor, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semaphore_productor);
    sem_destroy(&semaphore_consumidor);

    pthread_exit(NULL);
}