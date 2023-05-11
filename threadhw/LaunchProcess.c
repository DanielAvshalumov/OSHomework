#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    double elapsedTime;
    pid_t pid;
    int exitStatus;
    clock_t start = clock();
    pid = fork();
    if(pid < 0) {
        fprintf(stderr,"Fork Failed");
        return 1;
    } else if(pid == 0) {
        execv("AnalyzeWords",argv);
    } else {
        exitStatus = wait(NULL);
        clock_t end = clock();
        elapsedTime += (double)(end - start)/CLOCKS_PER_SEC * 1000;
        printf("Exit Status: %d\n",exitStatus);
        printf("Time Elapsed: %f ms\n", elapsedTime);
    }
}