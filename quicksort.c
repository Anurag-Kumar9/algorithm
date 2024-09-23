//Make a sorting program that implement quick sort make three data file all of which contain 1000 integer one of data file is in random order second in order and third 
//in reverse order. Run the sort program against these data file to determine how long it takes to sort list of different length. The program should also display a table 
//of time vs number of elements. You should be able to determine each algorithms order of complexity offline.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

int randomInt(int min, int max) {
    return min + rand() % (max + 1 - min);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int arr[1000];
int main () {

    FILE* file;
    //file to generate integer in sorted order
    file = fopen("initialSortedFile.txt", "w");
    if(file == NULL){
        printf("Error getting into the initioalSortedfile");
        return 0;
    }
    for(int i = 0; i < 1000; i++){
        fprintf(file, "%d\n", i + 1);
    }
    fclose(file);

    //taking input from sorted file
    file = fopen("initialSortedFile.txt", "r");
    if(file == NULL){
        printf("Error getting into theinitial Sorted  file");
        return 0;
    }
    int i = 0;
    while(fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }

    start = clock();

    quickSort(arr, 0, i-1);//sorting the sorted file

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time used to sort the sorted file is %f\n", cpu_time_used);

    fclose(file);

    //keeping the sorted integer in sortingsortedfile
    file = fopen("sortingSortedFile.txt", "w");
     if(file == NULL) {
        printf("Error getting to the sortingSorted file");
        return 0;
    }
    int j = 0;
    while(j < i){
        fprintf(file, "%d\n", arr[j++]);
    }
    fclose(file);

    //file to generate integer in random order
    file = fopen("randomFile.txt", "w");
    if(file == NULL) {
        printf("Error getting into the random int file");
        return 0;
    }
    for(int i = 0; i < 1000; i++){
        fprintf(file, "%d\n", randomInt(0, 1000));
    }
    fclose(file);

    //taking input from randomFile
    file = fopen("randomFile.txt", "r");
    if(file == NULL){
        printf("Error getting into the random in file");
        return 0;
    }
    i = 0;
    while(fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }
    start = clock();

    quickSort(arr, 0, i-1);//sorting the random file

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time used to sort the random file is %f\n", cpu_time_used);
    fclose(file);

    //sorting the random integer file to keep in sortedFileRandom.txt
    file = fopen("sortedFileRandom.txt", "w");
    if(file == NULL) {
        printf("Error getting to the soted file random");
        return 0;
    }
    j = 0;
    while(j < i){
        fprintf(file, "%d\n", arr[j++]);
    }
    fclose(file);


    //reverse

    //file to generate integer in random order
    file = fopen("reverseFile.txt", "w");
    if(file == NULL) {
        printf("Error getting into the reverse int file");
        return 0;
    }
    for(int i = 0; i < 1000; i++){
        fprintf(file, "%d\n", 1000 - i);
    }
    fclose(file);

    //taking input from randomFile
    file = fopen("reverseFile.txt", "r");
    if(file == NULL){
        printf("Error getting into the reverse in file");
        return 0;
    }
    i = 0;
    while(fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }
    start = clock();

    quickSort(arr, 0, i-1);//sorting the reversed file

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time used to sort the reverse file is %f\n", cpu_time_used);
    fclose(file);

    //sorting the random integer file to keep in sortedFileRandom.txt
    file = fopen("sortedReverseFile.txt", "w");
    if(file == NULL) {
        printf("Error getting to the reverse sorted file random");
        return 0;
    }
    j = 0;
    while(j < i){
        fprintf(file, "%d\n", arr[j++]);
    }
    fclose(file);
}