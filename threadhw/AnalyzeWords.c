#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

FILE *fptr;


void *averageLength(void *param);
void *longestWord(void *param);
void *mostFrequent(void *param);

int main(int argc, char *argv[]) {

    pthread_t tid[3];
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);

    pthread_create(&tid[0],&attr,averageLength,argv[1]);
    pthread_create(&tid[1],&attr,longestWord,argv[1]);
    pthread_create(&tid[2],&attr,mostFrequent,argv[1]);
    
    for(int i = 0; i < 2; i++) 
        pthread_join(tid[i],NULL);

    fclose(fptr);

    return 0;
}

void *mostFrequent(void *param) {
    char letter;
    int letterCount[25];
    int max = 0;
    for(int i = 0; i < 25; i++) {
        letterCount[i] = 0;
    }
    int index;
    if((fptr = fopen(param,"r")) == NULL) {
        printf("Error reading file");
        exit(1);
    }
    while( (letter = getc(fptr)) != EOF) {
        index = (int) (toupper(letter) - 65);
        if(letter != '\n' && index >= 0 && index < 26) {
            letterCount[index] = letterCount[index] + 1;
        }
    }
    int res; 
    for(int i = 0; i < 25; i++) {
        if(letterCount[i] > max) {
            max = letterCount[i];
            res = i;
        }
    }
    res = res + 97*2;
    printf("The most frequent letter is: %c \n",res-'a');
    pthread_exit(0);
}

void *longestWord(void *param) {
    int max = 0;
    int length;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if((fptr = fopen(param,"r")) == NULL) {
        printf("Error reading file");
        exit(1);
    }

    while((read = getline(&line, &len, fptr)) != -1) {
        length = read - 1;
        if(length > max) {
            max = length;
        }
    }

    printf("Largest length = %d\n",max);
    pthread_exit(0);
}

void *averageLength(void *param) {
    int lengthSum = 0;
    int lengthCount = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if((fptr = fopen(param,"r")) == NULL) {
        printf("Error reading file");
        exit(1);
    }

    while((read = getline(&line, &len, fptr)) != -1) {
        lengthSum += (read - 1);
        lengthCount++;
    }
    double average = lengthSum/lengthCount;
    printf("Average Length = %f\n",average);
    pthread_exit(0);
}   
