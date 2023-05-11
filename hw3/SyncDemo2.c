#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

void *threadOne(void *param);
void *threadTwo(void *param);
void *threadThree(void *param);
void *threadFour(void *param);
void *threadFive(void *param);

sem_t sem;
int grandTotal;

int main() {
    const int SIZE = 1000;
    int arrayList[SIZE];
    sem_init(&sem, 0, 1);
    for(int i = 1; i <= SIZE; i++) {
        arrayList[i-1] = i;
    }

    pthread_t tid[5];
    pthread_attr_t attr;

    pthread_create(&tid[0],&attr,threadOne,arrayList);
    pthread_create(&tid[1],&attr,threadTwo,arrayList);
    pthread_create(&tid[2],&attr,threadThree,arrayList);
    pthread_create(&tid[3],&attr,threadFour,arrayList);
    pthread_create(&tid[4],&attr,threadFive,arrayList);

    for(int i = 0; i < 5; i++) {
        pthread_join(tid[i],NULL);
    }

    printf("%d\n", grandTotal);

    return 0;
}

void *threadOne(void *param) {
    int subTotal = 0;
    int *arr = param;
    for(int i = 0; i < 200; i++) {
        subTotal += arr[i];
    }
    int temp = grandTotal + subTotal;
    sleep(1);
    sem_wait(&sem);
    grandTotal = temp;
    sem_post(&sem);
    pthread_exit(0);
}

void *threadTwo(void *param) {
    int subTotal = 0;
    int *arr = param;
    for(int i = 200; i < 400; i++) {
        subTotal += arr[i];
    }
    int temp = grandTotal + subTotal;
    sleep(4);
    sem_wait(&sem);
    grandTotal += temp;
    sem_post(&sem);
    pthread_exit(0);
}

void *threadThree(void *param) {
    int subTotal = 0;
    int *arr = param;
    for(int i = 400; i < 600; i++) {
        subTotal += arr[i];
    }
    int temp = grandTotal + subTotal;
    sleep(3);
    sem_wait(&sem);
    grandTotal += temp;
    sem_post(&sem);
    pthread_exit(0);
}

void *threadFour(void *param) {
    int subTotal = 0;
    int *arr = param;
    for(int i = 600; i < 800; i++) {
        subTotal += arr[i];
    }
    int temp = grandTotal + subTotal;
    sleep(2);
    sem_wait(&sem);
    grandTotal += temp;
    sem_post(&sem);
    pthread_exit(0);
}

void *threadFive(void *param) {
    int subTotal = 0;
    int *arr = param;
    for(int i = 800; i < 1000; i++) {
        subTotal += arr[i];
    }
    int temp = grandTotal + subTotal;
    sleep(5);
    sem_wait(&sem);
    grandTotal += temp;
    sem_post(&sem);
    pthread_exit(0);
}