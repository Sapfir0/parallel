#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono> 
#include <mutex>
#include "timeHelper.cpp"

using namespace std;

template <typename T>
bool exists(map<T, int> dict, T elem) {
    return dict.find(elem) != dict.end();
}

template <typename T>
vector<T> getOnlyUniqueElements(map<T, int> dict) {
    vector<T> uniqueElements;
    for (auto item : dict) {
        if (item.second == 1) {
            uniqueElements.push_back(item.first);
        }
    }
    return uniqueElements;
}

template <typename T>
vector<T> uniqueCounter(vector<T> list) {
    map<T, int> uniqueMap = {};
    for (T item : list) {
        if (exists(uniqueMap, item)) {
            uniqueMap[item] += 1;
        }
        else {
            uniqueMap.insert(pair<T, int>(item, 1));
        }

    }
    return getOnlyUniqueElements(uniqueMap);
}

template <typename T>
vector<T> uniqueCounterMutex(vector<T> list) {
    map<T, int> uniqueMap = {};
    std::mutex mutex;
     
    for (T item : list) {
        if (exists(uniqueMap, item)) {
            mutex.lock();
            uniqueMap[item] += 1;
            mutex.unlock();
        }
        else {
            uniqueMap.insert(pair<T, int>(item, 1));
        }

    }
    return getOnlyUniqueElements(uniqueMap);
}

vector<int> randomVector(size_t size)
{
    vector<int> v(size);
    random_device rd;
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0, size); // guaranteed unbiased
    generate(v.begin(), v.end(), [&] {return uni(rng); });
    return v;
}



int main() {
    int N = 10000;
    vector<int> list0(randomVector(N));
    
    cout << "serial ";
    auto serial = measureTime(uniqueCounter<int>)(list0);

    cout << "parallel ";
    auto parallel = measureTime( uniqueCounterMutex<int>)(list0);


    /*
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
