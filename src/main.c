#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>

// Функция сортировки нисходящим слиянием
/*void merge(char *a, char *a1, char *a2){

}
void sort(char *line, int len){
    int sz = len, hs = sz >> 1;
    if(sz < 2)
        return;
    char *l = new
}*/


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
    }
    int i, j;
    int n;
    fscanf(datafile, "%d\n", &n);
    printf("\n");
    char **line = (char**) malloc(n * sizeof(char*));
    char *temp = (char*) malloc(200 * sizeof(char));
    for(i = 0; i < n; i++){
        line[i] = (char*) malloc(200 * sizeof(char));
        fgets(line[i], 200, datafile);
        printf("%s", line[i]);
        if(feof(datafile)){break;}
    }
    //char line[n][200], temp[200];
    //int line_index = 0;
    /*for(i = 0; i < n; i++){
        fgets(line[i], 200, datafile);
        printf("%s", line[i]);
        if(feof(datafile)){break;}
    }*/
    //sort(line, n);
    printf("\n\n");
    for(i=0; i < n-1 ; i++){
        for(j=i+1; j< n; j++)
        {
            if(strcmp(line[i],line[j]) > 0)
            {
                strcpy(temp,line[i]);
                strcpy(line[i],line[j]);
                strcpy(line[j],temp);
            }
        }
    }
    for (i = 0; i < n; i++){
        printf("%s", line[i]);
    }
    for(i = 0; i < n; i++){
        free(line[i]);
    }
    free(line);
    free(temp);
}
