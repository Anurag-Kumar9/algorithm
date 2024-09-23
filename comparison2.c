#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);

void merge(int arr[], int l, int m, int r);
int partition(int arr[], int low, int high);

void generateRandomList(int arr[], int n);
double measureTime(void (*sortFunc)(int[], int), int arr[], int n);
double measureTimeMergeSort(void (*sortFunc)(int[], int, int), int arr[], int l, int r);
double measureTimeQuickSort(void (*sortFunc)(int[], int, int), int arr[], int low, int high);

int main() {
    int sizes[] = {100, 1000, 5000, 10000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        
        generateRandomList(arr, n);
        double timeTaken = measureTime(insertionSort, arr, n);
        printf("Insertion Sort - Size: %d, Time: %f seconds\n", n, timeTaken);
        
        generateRandomList(arr, n);
        timeTaken = measureTime(selectionSort, arr, n);
        printf("Selection Sort - Size: %d, Time: %f seconds\n", n, timeTaken);
        
        generateRandomList(arr, n);
        timeTaken = measureTimeMergeSort(mergeSort, arr, 0, n - 1);
        printf("Merge Sort - Size: %d, Time: %f seconds\n", n, timeTaken);
        
        generateRandomList(arr, n);
        timeTaken = measureTimeQuickSort(quickSort, arr, 0, n - 1);
        printf("Quick Sort - Size: %d, Time: %f seconds\n", n, timeTaken);
        
        free(arr);
    }
    
    return 0;
}

void generateRandomList(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

double measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    int *copy = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    
    clock_t start = clock();
    sortFunc(copy, n);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double measureTimeMergeSort(void (*sortFunc)(int[], int, int), int arr[], int l, int r) {
    int *copy = (int *)malloc((r - l + 1) * sizeof(int));
    for (int i = l; i <= r; i++) {
        copy[i] = arr[i];
    }
    
    clock_t start = clock();
    sortFunc(copy, l, r);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double measureTimeQuickSort(void (*sortFunc)(int[], int, int), int arr[], int low, int high) {
    int *copy = (int *)malloc((high - low + 1) * sizeof(int));
    for (int i = low; i <= high; i++) {
        copy[i] = arr[i];
    }
    
    clock_t start = clock();
    sortFunc(copy, low, high);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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