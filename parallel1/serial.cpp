п»ї#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono> 
#include <mutex>
#include "timeHelper.cpp"
#include <unordered_map>
#include <string>

using namespace std;

bool findIn(vector<int> collection, int item) {
    return find(collection.begin(), collection.end(), item) != collection.end();
}

bool isEqual(vector<int> list1, vector<int> list2) {
    return list1 == list2;
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
vector<T> getOnlyUniqueElements(unordered_map<T, int> dict) {
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
    unordered_map<T, int> uniqueMap = {};
    for (T item : list) {
        uniqueMap[item] += 1;
    }
    return getOnlyUniqueElements(uniqueMap);
}


template <typename T>
int uniqueCounterMutex(vector<T> list, int threadsCount) {
    vector<unordered_map<T, int>> uniqueMaps(threadsCount);
    std::mutex myMutex;
    vector<T> uniqueElements;

    auto vectors = splitVector(list, threadsCount);

    parallelExec(threadsCount, [&](size_t block) {
        for (T item : vectors[block]) {
            std::lock_guard<std::mutex> guard(myMutex);
            uniqueMaps[block][item] += 1;
        }
        });

    int counter = 0;

    for (int i = 0; i < uniqueMaps.size(); i++) {
        for (auto item : uniqueMaps[i]) {
            if (item.second == 1) {
                bool isUniqueElement = true;
                for (int j = 0; j < uniqueMaps.size(); j++) {
                    if (j != i && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { //РЅР°С€Р»Рё С…РѕС‚СЏ Р±С‹ РІ РґСЂСѓРіРёС… РјР°РїР°С…
                        isUniqueElement = false;
                    }
                }
                if (isUniqueElement) {
                    counter++;
                }
            }

        }
    }

    return counter;
}



template <typename T>
int uniqueCounterAtomic(vector<T> list, int threadsCount) {
    vector<unordered_map<T, int>> uniqueMaps(threadsCount);
    atomic<int> counter = 0;
    auto vectors = splitVector(list, threadsCount);

    parallelExec(threadsCount, [&](size_t block) {
        for (T item : vectors[block]) {
            uniqueMaps[block][item] += 1;
        }
        });

    for (int i = 0; i < uniqueMaps.size(); i++) {
        for (auto item : uniqueMaps[i]) {
            if (item.second == 1) {
                bool isUniqueElement = true;
                for (int j = 0; j < uniqueMaps.size(); j++) {
                    if (j != i && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { //РЅР°С€Р»Рё РІ РґСЂСѓРіРёС… РјР°РїР°С…
                        isUniqueElement = false;
                    }
                }
                if (isUniqueElement) {
                    counter++;
                }
            }

        }
    }

    return counter;

}

void testIsEqualList(vector<int> list1, vector<int> list2) {
    auto res = isEqual(list1, list2) ? "Equal" : "Not equal";
    std::cout << res << endl;
}

void testIsEqualLength(int l1, int l2) {
    if (l1 == l2) {
        
    }
    else {
       cout << "Not equal len: " + to_string(l1) + " " + to_string(l2);
    }
}

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


    /*
    * serial 10.062 seconds
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
