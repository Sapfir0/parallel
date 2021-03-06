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
#include "helper.cpp"

using namespace std;


bool isEqual(vector<int> list1, vector<int> list2) {
    if (list1.size() != list2.size())
        return false;

    for (int i = 0; i < list1.size(); i++)
        if (list1[i] != list2[i])
            return false;

    return true;
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

template<typename Function>
void parallelExec(size_t threadCount, Function f) {
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(f, i);
    }

    for (auto& t : threads) {
        t.join();
    }
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
        uniqueMap[item] += 1;
    }
    return getOnlyUniqueElements(uniqueMap);
}




template <typename T>
vector<T> uniqueCounterMutex(vector<T> list, int threadsCount) {
    map<T, int> uniqueMap = {};
    std::mutex myMutex;

    auto vectors = splitVector(list, threadsCount);

    parallelExec(threadsCount, [&](size_t block) {
        for (T item : vectors[block]) {
            std::lock_guard<std::mutex> guard(myMutex);
            uniqueMap[item] += 1;
        }
    });


    return getOnlyUniqueElements(uniqueMap);
}



int main() {
    int N = 1000000;
    int threadsCount = 3;
    vector<int> list0(randomVector(N));
    
    cout << "serial ";
    auto serial = measureTime(uniqueCounter<int>)(list0);

    cout << "parallelMutex ";
    auto parallel = measureTime(uniqueCounterMutex<int>)(list0, threadsCount);
    string res = isEqual(serial, parallel) ? "Equal" : "Not equal";

    std::cout << res << endl;

    cout << serial.size() << " " << parallel.size();

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
