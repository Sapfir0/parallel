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


int partition(int* arr, int low, int high) {
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

void quickSortSerial(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortSerial(arr, low, pi - 1);
        quickSortSerial(arr, pi + 1, high);

    }
}

void quickSortParallel(int* arr, int low, int high) {
    int magic = 100;
    if (low < high) {
        int pi = partition(arr, low, high);
        if (pi - low > magic) {
#pragma omp task
            {
                quickSortParallel(arr, low, pi - 1);
            }
        }
        else {
            quickSortSerial(arr, low, pi - 1);
        }

        if (high - pi > 100) {
            quickSortParallel(arr, pi + 1, high);
        }
        else {
            quickSortSerial(arr, pi + 1, high);
        }

    }
}

void sortParallel(vector<int>& arr, int threadCount) {
#pragma omp parallel
    {
#pragma omp single
        {
            quickSortParallel(arr.data(), 0, arr.size() - 1);

#pragma omp taskwait
        }
    }
}

void sortSerial(vector<int>& arr) {
    quickSortSerial(arr.data(), 0, arr.size() - 1);
}


#endif // DOMAIN_H