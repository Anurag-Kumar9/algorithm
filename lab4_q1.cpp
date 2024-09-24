#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Global variables to count comparisons and exchanges
int comparisons = 0;
int exchanges = 0;

// Utility function to reset counters
void resetCounters() {
    comparisons = 0;
    exchanges = 0;
}

// Counting Sort
void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - minVal]++;
        exchanges++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
        exchanges++;
    }

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

// Radix Sort
void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
        exchanges++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        exchanges++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}

// Bucket Sort
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    vector<vector<float>> b(n);

    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        b[bi].push_back(arr[i]);
        exchanges++;
    }

    for (int i = 0; i < n; i++) {
        sort(b[i].begin(), b[i].end());
        comparisons += b[i].size() * log(b[i].size());
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            arr[index++] = b[i][j];
            exchanges++;
        }
    }
}

// Function to generate random integer array
vector<int> generateRandomIntArray(int size, int maxVal) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % maxVal;
    }
    return arr;
}

// Function to generate random float array
vector<float> generateRandomFloatArray(int size) {
    vector<float> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    return arr;
}

// Function to measure and print the performance of sorting algorithms
void measurePerformance() {
    vector<int> sizes = {100, 1000, 5000};
    int maxVal = 10000;

    for (int size : sizes) {
        cout << "Array Size: " << size << endl;

        // Counting Sort
        vector<int> arr = generateRandomIntArray(size, maxVal);
        resetCounters();
        auto start = high_resolution_clock::now();
        countingSort(arr);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        cout << "Counting Sort - Time: " << duration << " microseconds, Comparisons: " << comparisons << ", Exchanges: " << exchanges << endl;

        // Radix Sort
        arr = generateRandomIntArray(size, maxVal);
        resetCounters();
        start = high_resolution_clock::now();
        radixSort(arr);
        end = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end - start).count();
        cout << "Radix Sort - Time: " << duration << " microseconds, Comparisons: " << comparisons << ", Exchanges: " << exchanges << endl;

        // Bucket Sort
        vector<float> floatArr = generateRandomFloatArray(size);
        resetCounters();
        start = high_resolution_clock::now();
        bucketSort(floatArr);
        end = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end - start).count();
        cout << "Bucket Sort - Time: " << duration << " microseconds, Comparisons: " << comparisons << ", Exchanges: " << exchanges << endl;

        cout << endl;
    }
}

int main() {
    srand(time(0));
    measurePerformance();
    return 0;
}