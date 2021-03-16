#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono> 
#include <mutex>
#include "helper.h"
#include "timeHelper.h"
#include <unordered_map>
#include <string>
#include "domain.h"
#include <functional>

using namespace std;


int main() {
    int N = 1000000;
    int MaxN = 9000000;
    const int maxThreadsCount = 8;
    int NStep = 1000000;
    //vector<int> list0(randomVector(N));


    map<string, function<int(vector<int>, int)>> types = {
        {"parallelMutex", uniqueCounterMutex<int>},
        {"sharedVariables", uniqueCounterSharedVariables<int>},
        {"atomic", uniqueCounterAtomic<int>}
    };

    map<int, tuple<vector<int>, int> > dataList; // collectionSize: {randomList, serialResult}

    for (int size = N; size < MaxN; size += NStep) {
        auto currentList = randomVector(size);

        cout << "serial 1 " << size << " ";
        auto serial = measureTime(uniqueCounter<int>)(currentList);
        dataList[size] = { currentList, serial };
    }


    for (auto type : types) {
        for (int threadsCount = 2; threadsCount < maxThreadsCount; threadsCount++) {
            for (int size = N; size < MaxN; size += NStep) {
                vector<int> currentList;
                int serial = 0;
                tie(currentList, serial) = dataList[size];

                cout << type.first << " " << threadsCount << " ";
                int result = 0;
                double elapsed = 0;
                cout << size << " ";
                tie(result, elapsed) = checkTime(type.second, currentList, threadsCount);
                testIsEqualLength(serial, result);
            }
        }
    }




    return 0;
}
