#include <stdio.h>
#include <pthread.h>
#include<unistd.h>

pthread_mutex_t lock1, lock2;

void* thread1(void* arg) {
    pthread_mutex_lock(&lock1);
    printf("Thread 1 acquired lock 1\n");

    // Introduce a delay to create a potential deadlock situation
    sleep(1);

    pthread_mutex_lock(&lock2);
    printf("Thread 1 acquired lock 2\n");

    // Code execution will never reach this point due to deadlock

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&lock2);
    printf("Thread 2 acquired lock 2\n");

    pthread_mutex_lock(&lock1);
    printf("Thread 2 acquired lock 1\n");

    // Code execution will never reach this point due to deadlock

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}

