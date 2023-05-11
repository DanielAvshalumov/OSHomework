#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

typedef uint32_t int32;
typedef uint64_t int64;

int replaceFIFO(char *string, int frames);
int replcaeLRU(char *string, int frames);

int main(int argc, char *argv[]) {
    // checks if input is within 32-bit range
    int32 max = UINT32_MAX;
    int64 input = strtoul(argv[1],NULL,10);
    if(input > max) {
        printf("ERROR: out of bounds\n");
        exit(1);
    }

    int largestPossiblePageNo = pow(2,20);
    int pageSize = pow(2,12);
    int pageNumber = input / pageSize;
    int pageOffset = input % pageSize;
    printf("Largest possible page number is: %d\n", largestPossiblePageNo);
    printf("The page table size is: %d bytes\n", 4 * largestPossiblePageNo);
    printf("Given the address of: %lu\n", input);
    printf("The page number is: %d\n", pageNumber);
    printf("The page offset is: %d\n", pageOffset);
    printf("With a 2-level page table, the outer page number is: ");
    printf("\nWith a 2-level page table, the inner page number is: ");

    char *string = "70120304230321201701";
    int faultsFIFO = replaceFIFO(string,3);
    printf("%d faults found with FIFO\n", faultsFIFO);
    int faultsLRU = replcaeLRU(string,3);
    printf("%d faults found with LRU\n", faultsLRU);

    return 0;
}

int replaceFIFO(char *string, int frames) {
    char queue[frames];
    int count = 0;
    int flag;

    for(int i = 0; i < frames; i++) {
        queue[i] = '\0';
    }
    printf("\n");

    for(int i = 0; i < strlen(string); i++) {
        if(queue[i % frames] == '\0') {
            queue[i] = string[i];
            printf("%c: ",string[i]);
            for(int k = 0; k < frames; k++) {
                printf("%c",queue[k]);
            }
            printf("\n");
            count++;
            continue;
        }
        // check if next page is in memory
        flag = 0;
        for(int j = 0; j < frames; j++) {
            if(queue[j] == string[i]) {
                flag = 1;
            }
        }
        // if there isn't then replace the first element that had been inserted into the queue
        if(!flag) {
            queue[count % frames] = string[i];
            count++;
            printf("%c: ",string[i]);
            for(int k = 0; k < frames; k++) {
                printf("%c",queue[k]);
            }
            printf("\n");
        }
    }
    return count;
}

int replcaeLRU(char *string, int frames) {
    char queue[frames];
    int count = 0;
    int flag;
    int ptr;
    int least;
    int leastIndex;
    for(int i = 0; i < frames; i++) {
        queue[i] = '\0';
    }
    printf("\n");
    
    for(int i = 0; i < strlen(string); i++) {
        // fill up the first n frames
        if(queue[i % frames] == '\0') {
            queue[i] = string[i];
            printf("%c: ",string[i]);
            for(int k = 0; k < frames; k++) {
                printf("%c",queue[k]);
            }
            printf("\n");
            count++;
            continue;
        }
        // make disposable model of queue
        char disposable[frames];
        for(int i = 0; i < frames; i++) {
            disposable[i] = queue[i];
        }

        // check if next page is in memory
        flag = 0;
        for(int j = 0; j < frames; j++) {
            if(queue[j] == string[i]) {
                flag = 1;
            }
        }
        // if there isn't then 
        if(!flag) {
            // traverse back to check for LRU
            for(ptr = i - 1; ptr >= 0; ptr--) {
                for(int j = 0; j < frames; j++) {
                    if(string[ptr] == disposable[j]) {
                        disposable[j] = '\0';
                        least = disposable[j];
                        leastIndex = j;
                        break;  
                    }
                }
            }
            // update memory array
            queue[leastIndex] = string[i];
            printf("%c: ",string[i]);
            for(int j = 0; j < frames; j++) {
                printf("%c", queue[j]);
            }
            printf("\n");
            count++;
        }       
    }
    return count;
}