#include <iostream>
#include <vector>
#include "domain.h"
#include "helper.h"
#include <omp.h>
#include <map>

void testIsEqual(vector<int> list1, vector<int> list2) {
    if (list1 == list2) {
        return;
    }
    cout << "Not equal";
}

int main()
{
    int N = 1000000;
    int MaxN = 6000000;
    const int maxThreadsCount = 8;
    int NStep = 1000000;
    
    map<string, function<void(vector<int>&, int)> > types = {
    {"parallel", sortParallel },
    };

    map<int, vector<int> > dataList; // collectionSize: {randomList, serialResult}

    for (int size = N; size < MaxN; size += NStep) {
        auto currentList = randomVector(size);
        cout << "serial 1 " << size << " ";
        checkSerialTime(sortSerial, currentList);
        dataList[size] = currentList;
    }

    for (int threadsCount = 1; threadsCount < maxThreadsCount; threadsCount++) {
        omp_set_num_threads(threadsCount);

        for (int size = N; size < MaxN; size += NStep) {
            auto currentList  = dataList[size];
            cout << "Parallel" << " " << threadsCount << " ";

            cout << size << " ";
            double elapsed = checkParallelTime(sortParallel, currentList, threadsCount);
            testIsEqual(currentList, dataList[size]);
        }
    }
    


}
