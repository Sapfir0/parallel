#include <iostream>
#include <vector>
#include "domain.h"
#include "helper.h"
#include <omp.h>
#include <map>

void testIsEqual(vector<int>  list1, vector<int>  list2) {
    if (list1 == list2) {
        return;
    }
    cout << "Not equal";
}

int main()
{
    int N = 10000;
    int MaxN = 60000;
    const int maxThreadsCount = 8;
    int NStep = 10000;
    
    map<string, function<vector<int>(vector<int>, int)> > types = {
    {"parallel", sortParallel },
    };

    map<int, tuple<vector<int>, double > > dataList; // collectionSize: {randomList, serialResult}

    for (int size = N; size < MaxN; size += NStep) {
        auto currentList = randomVector(size);
        cout << "serial 1 " << size << " ";
        auto serial = checkSerialTime(sortSerial, currentList);
        dataList[size] = serial;
    }

    for (int threadsCount = 1; threadsCount < maxThreadsCount; threadsCount++) {
        for (int size = N; size < MaxN; size += NStep) {
            vector<int> currentList;
            double serial;
            tie(currentList, serial) = dataList[size];
            cout << "Parallel" << " " << threadsCount << " ";

            vector<int> result;
            double elapsed = 0;
            cout << size << " ";
            tie(result, elapsed) = checkParallelTime(sortParallel, currentList, threadsCount);
            testIsEqual(currentList, result);
        }
    }
    


}
