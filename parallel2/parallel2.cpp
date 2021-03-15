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
    int N = 100000;
    int MaxN = 100000000;
    const int maxThreadsCount = 8;
    vector<int> list0(randomVector(N));

    cout << "serial ";
    auto serial = measureTime(uniqueCounter<int>)(list0);

    map<string, function<int(vector<int>, int)>> types = {
        {"parallelMutex", uniqueCounterMutex<int>},
        {"shared variables", uniqueCounterSharedVariables<int>},
        {"atomic", uniqueCounterAtomic<int>}
    };
    

    for (auto type : types) {
        for (int size = N; size < MaxN; size *= 10) {
            for (int threadsCount = 2; threadsCount < maxThreadsCount; threadsCount++) {
                cout << type.first << threadsCount << " ";
                int result = 0;
                double elapsed = 0;
                cout << size << " ";
                tie(result, elapsed) = checkTime(type.second, list0, threadsCount);
                testIsEqualLength(serial, result);
            }
        }
    }

    return 0;
}
