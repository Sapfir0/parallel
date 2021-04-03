#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <omp.h>
using namespace std;

vector<int> standartSortArray(vector<int> list) {
	sort(list.begin(), list.end());
	return list;
}


int partition(vector<int> arr, int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


int partitionParallel(vector<int>  arr, int low, int high, int threadsCount) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); 

    omp_set_num_threads(threadsCount);
    #pragma omp parallel for
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

vector<int> quickSortSerial(vector<int> arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortSerial(arr, low, pi - 1);
        quickSortSerial(arr, pi + 1, high);
    }
    return arr;
}

vector<int> quickSortParallel(vector<int> arr, int low, int high, int threadsCount) {
    if (low < high) {
        int pi = partitionParallel(arr, low, high, threadsCount);

        quickSortParallel(arr, low, pi - 1, threadsCount);
        quickSortParallel(arr, pi + 1, high, threadsCount);
    }
    return arr;
}

vector<int> sortParallel(vector<int> arr, int threadCount) {
    return quickSortParallel(arr, 0, arr.size() - 1, threadCount);
}

vector<int> sortSerial(vector<int> arr) {
    return quickSortSerial(arr, 0, arr.size() - 1);
}


#endif // DOMAIN_H