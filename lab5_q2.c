#include <stdio.h>
#include <stdlib.h>

struct data{
    int value;
    char color;
};

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
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

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

    

int main() {
    //taking user data
    int n;
    printf("Enter the number of pairs: ");
    scanf("%d", &n);
    struct data *arr = (struct data *)malloc(n * sizeof(struct data));
    int i = 0;
    do {
        printf("Enter the value and color of the pair(in (value color) format): ");
        scanf("%d %c", &arr[i].value, &arr[i].color);
        i++;
    } while (i < n);

    int *red = (int *)malloc(n * sizeof(int));
    int *blue = (int *)malloc(n * sizeof(int));
    int *yellow  = (int *)malloc(n * sizeof(int));

    //separating the arr into red, blue and yellow arrays

    int red_index = 0, blue_index = 0, yellow_index = 0;
    for (i = 0; i < n; i++) {
        if (arr[i].color == 'R') {
            red[red_index] = arr[i].value;
            red_index++;
        } else if (arr[i].color == 'B') {
            blue[blue_index] = arr[i].value;
            blue_index++;
        } else if (arr[i].color == 'Y') {
            yellow[yellow_index] = arr[i].value;
            yellow_index++;
        }
    }

    //sorting all three color array based on their values
    mergeSort(red, 0, red_index - 1);
    mergeSort(blue, 0, blue_index - 1);
    mergeSort(yellow, 0, yellow_index - 1);

    //merging all three arrays into first arr
    int j = 0;
    for (i = 0; i < red_index; i++) {
        arr[j].value = red[i];
        arr[j].color = 'R';
        j++;
    }
    for (i = 0; i < blue_index; i++) {
        arr[j].value = blue[i];
        arr[j].color = 'B';
        j++;
    }
    for (i = 0; i < yellow_index; i++) {
        arr[j].value = yellow[i];
        arr[j].color = 'Y';
        j++;
    }

    //printing the sorted array
    for (i = 0; i < n; i++) {
        printf("%d %c\n", arr[i].value, arr[i].color);
    }
}