#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <pthread.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0

typedef struct thread_data{
    char **line;
    int start;
    int end;
} thread_data;


// Функция сортировки нисходящим слиянием
void mergeSort(char **a, int start, int end){
    if(end - start < 2)
        return;
    if(end - start == 2){
        char *temp;
        if(strcmp(a[start], a[start+1]) > 0){
            temp = a[start];
            a[start] = a[start+1];
            a[start+1] = temp;
        }
        return;
    }
    mergeSort(a, start, start + (end-start)/2);
    mergeSort(a, start + (end-start)/2, end);
    char **b = (char**) malloc((end - start) * sizeof(char*));
    int b1 = start, e1 = start + (end-start)/2, b2 = e1;
    for(int i = 0; i < (end - start); i++){
        b[i] = (char*) malloc(200 * sizeof(char));
        if(b1 >= e1 || (b2 < end && (strcmp(a[b1],a[b2]) > 0 || strcmp(a[b1],a[b2]) == 0))){
            b[i] = a[b2];
            b2++;
        }
        else{
            b[i] = a[b1];
            b1++;
        }
    }
    for(int i = start; i < end; ++i){
        a[i] = b[i - start];
    }
}

void* helloWorld(void *args) {
    printf("Hello from thread!\n");
    return SUCCESS;
}



int main(int argc, char *argv[]){
    FILE *datafile;
    if(argc == 2){
        printf("Using given file '%s'\n", argv[1]);
        if(!(datafile = fopen(argv[1], "r"))){
            printf("Couldn't use file '%s'\nExit...\n", argv[1]);
            return 0;
        }
    }
    else if(argc == 1){
        printf("Using standart file 'data.txt'\n");
        if(!(datafile = fopen("data.txt", "r"))){
            printf("Couldn't use file 'data.txt'\nExit...\n");
            return 0;
        }
    }
    else{
        printf("Error: you must give only 1 file!\n");
        return 0;
    }
    pthread_t thread;
    int i, j;
    int n;
    fscanf(datafile, "%d\n", &n);
    printf("\n");
    char **line = (char**) malloc(n * sizeof(char*));
    for(i = 0; i < n; i++){
        line[i] = (char*) malloc(200 * sizeof(char));
        fgets(line[i], 200, datafile);
        printf("%d) %s", i, line[i]);
        if(feof(datafile)){break;}
    }
    /////////////////////////////////////////////////////

    /*thread_data data;
    int status, status_addr;
    
    status = pthread_create(&thread, NULL, helloWorld, NULL);
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
        exit(ERROR_CREATE_THREAD);
    } printf("Hello from main!\n");*/



    mergeSort(line, 0, 10);
    printf("\n\n");
    for (i = 0; i < n; i++){
        printf("%d) %s", i, line[i]);
    }
    for(i = 0; i < n; i++){
        free(line[i]);
    }
    free(line);
}
