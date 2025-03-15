#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate N random numbers
vector<int> generateRandomNumbers(int N) {
    vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 1000; // Random numbers between 0 and 999
    }
    return numbers;
}

// Binary Search
int binarySearch(const vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Interpolation Search
int interpolationSearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }
        int pos = low + ((double)(high - low) / (arr[high] - arr[low]) * (key - arr[low]));
        if (arr[pos] == key) return pos;
        if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to measure execution time
void measureExecutionTime() {
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;
    vector<int> numbers = generateRandomNumbers(N);
    vector<int> sortedNumbers = numbers;
    sort(sortedNumbers.begin(), sortedNumbers.end());

    int searchKey;
    cout << "Enter number to search: ";
    cin >> searchKey;

    // Measure Binary Search
    auto start = high_resolution_clock::now();
    binarySearch(sortedNumbers, searchKey);
    auto stop = high_resolution_clock::now();
    cout << "Binary Search Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    // Measure Interpolation Search
    start = high_resolution_clock::now();
    interpolationSearch(sortedNumbers, searchKey);
    stop = high_resolution_clock::now();
    cout << "Interpolation Search Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    // Measure Selection Sort
    vector<int> tempNumbers = numbers;
    start = high_resolution_clock::now();
    selectionSort(tempNumbers);
    stop = high_resolution_clock::now();
    cout << "Selection Sort Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    // Measure Merge Sort
    tempNumbers = numbers;
    start = high_resolution_clock::now();
    mergeSort(tempNumbers, 0, tempNumbers.size() - 1);
    stop = high_resolution_clock::now();
    cout << "Merge Sort Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";
}

int main() {
    measureExecutionTime();
    return 0;
}
