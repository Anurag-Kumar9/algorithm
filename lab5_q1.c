#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int par(int *arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

void quick(int *arr, int left, int right) {
    if (left < right) {
        int temp = par(arr, left, right);
        quick(arr, left, temp - 1);
        quick(arr, temp + 1, right);
    }
}

int main() {
    int n = 1;
    printf("Enter an Even Number to Input: ");
    while (1) {
        scanf("%d", &n);
        if (n % 2 != 0 || n <= 0)
            printf("You Entered a Wrong Number. Try Again!! Enter: ");
        else
            break;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    int temp;
    for (int i = 0; i < n; i++) {
        printf("Enter Your Number: ");
        scanf("%d", &temp);
        arr[i] = temp;
    }

    quick(arr, 0, n - 1);

    int maxi = 0;
    int **result = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        result[i] = (int *)malloc(2 * sizeof(int));
    }

    for (int i = 0; i < n / 2; i++) {
        result[i][0] = arr[i];
        result[i][1] = arr[n - i - 1];
        if (arr[i] + arr[n - i - 1] > maxi) {
            maxi = arr[i] + arr[n - i - 1];
        }
    }

    for (int i = 0; i < n / 2; i++) {
        printf("%d  %d\n", result[i][0], result[i][1]);
    }
    printf("Maximum Sum is: %d\n", maxi);

    for (int i = 0; i < n / 2; i++) {
        free(result[i]);
    }
    free(result);
    free(arr);

    return 0;
}