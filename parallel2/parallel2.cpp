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

using namespace std;


int main() {
    int N = 10000000;
    const int maxThreadsCount = 6;
    vector<int> list0(randomVector(N));

    cout << "serial ";
    auto serial = measureTime(uniqueCounter<int>)(list0);

    for (int threadsCount = 1; threadsCount < maxThreadsCount; threadsCount++) {
        cout << "parallelMutex" << threadsCount << " ";
        auto parallel = measureTime(uniqueCounterMutex<int>)(list0, threadsCount);
        testIsEqualLength(serial.size(), parallel);

        cout << "atomic" << threadsCount << " ";
        auto atom = measureTime(uniqueCounterAtomic<int>)(list0, threadsCount);
        testIsEqualLength(serial.size(), atom);
    }


   
    /* serial 10.062 seconds
parallelMutex1 8.59098 seconds
atomic1 7.50061 seconds
parallelMutex2 9.21549 seconds
atomic2 7.46169 seconds
parallelMutex3 10.7417 seconds
atomic3 8.00863 seconds
parallelMutex4 12.7107 seconds
atomic4 9.49391 seconds
parallelMutex5 12.9359 seconds
atomic5 9.90633 seconds
   vector<int> list = {1, -1, 1, 0, 9, 12, 3, -3, 0, 12, -12};
    auto res = getOnlyUniqueElements(uniqueCounter(list));
    for (auto elem : res)
    {
        std::cout << elem << endl;
    }
    vector<string> list2 = { "a", "b", "a", "c", "d", "e", "c" };
    auto res2 = getOnlyUniqueElements(uniqueCounter(list2));
    for (auto elem : res2)
    {
        std::cout << elem << endl;
    }

    */
    return 0;
}
