#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <pthread.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS     1
#define FAIL    11

typedef struct thread_data{
    char **line;
    int start;
    int end;
} thread_data;


// Функция сортировки нисходящим слиянием
/*void mergeSort_out(char **a, int start, int end){
    printf("CATCHargs: %d, %d\n", start, end);
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
    mergeSort_out(a, start, start + (end-start)/2);
    mergeSort_out(a, start + (end-start)/2, end);
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
    printf("CATCH\n");
}*/

void *mergeSort(void *args){
    thread_data *data = (thread_data*) args;
    int start = data->start, end = data->end;
    printf("CATCHargs: %d, %d\n", start, end);
    int status, status_addr;
    if(end - start < 2)
        return (void *) SUCCESS;
    if(end - start == 2){
        char *temp;
        if(strcmp(data->line[start], data->line[start+1]) > 0){
            temp = data->line[start];
            data->line[start] = data->line[start + 1];
            data->line[start + 1] = temp;
        }
        return (void *) SUCCESS;
    }
    pthread_t thread_l, thread_r;
    thread_data *data_l, *data_r;

    data_l = data;
    data_l->start = start;
    data_l->end = start + (end-start)/2;
    status = pthread_create(&thread_l, NULL, mergeSort,(void *) data_l);
    if(status == 0){
        pthread_join(thread_l,(void **) &status_addr);
        if(status_addr!=SUCCESS){
            printf("ERROR");
            return (void *) FAIL;
        }
    }

    data_r = data;
    data_r->start = start + (end-start)/2;
    data_r->end = end;
    status = pthread_create(&thread_r, NULL, mergeSort,(void *) data_r);
    if (status == 0){
        pthread_join(thread_r,(void **) &status_addr);
        if(status_addr!=SUCCESS){
            printf("ERROR");
            return (void *) FAIL;
        }
    }
    char **b = (char**) malloc((end - start) * sizeof(char*));
    int b1 = start, e1 = start + (end - start)/2, b2 = e1;
    for(int i = 0; i < (end - start); i++){
        b[i] = (char*) malloc(200 * sizeof(char));
        if(b1 >= e1 || (b2 < end && (strcmp(data->line[b1],data->line[b2]) > 0 || strcmp(data->line[b1],data->line[b2]) == 0))){
            b[i] = data->line[b2];
            b2++;
        }
        else{
            b[i] = data->line[b1];
            b1++;
        }
    }
    for(int i = start; i < end; ++i){
        data->line[i] = b[i - start];
    }

    return (void *) SUCCESS;
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
    printf("\n\n");
    /////////////////////////////////////////////////////

    thread_data data = {line, 0, 10};
    pthread_t thread;
    int status, status_addr;
    
    status = pthread_create(&thread, NULL, mergeSort, (void *) &data);
    if(status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
        exit(ERROR_CREATE_THREAD);
    }
    else if(status == 0){
        status = pthread_join(thread, (void **) &status_addr);
        if(status_addr != SUCCESS){
            printf("ERROR\n");
            return 0;
        }
    }
    printf("Hello from main!\n");


    printf("\n\n");
    //mergeSort_out(line, 0, 10);
    printf("\n\n");
    for (i = 0; i < n; i++){
        printf("%d) %s", i, line[i]);
    }
    for(i = 0; i < n; i++){
        free(line[i]);
    }
    free(line);


}
