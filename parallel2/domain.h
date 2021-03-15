#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include <unordered_map>
#include <mutex>

using namespace std;

template <typename T>
int getOnlyUniqueElements(unordered_map<T, int> dict) {
    int counter = 0;
    for (auto item : dict) {
        if (item.second == 1) {
            counter ++;
        }
    }
    return counter;
}

template <typename T>
int uniqueCounter(vector<int> list) {
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
            uniqueMaps[block][item] += 1;
        }
    });

    int counter = 0;
    parallelExec(threadsCount, [&](size_t block) {
        for (auto item : uniqueMaps[block]) {
            if (item.second == 1) {
                bool isUniqueElement = true;
                for (int j = 0; j < uniqueMaps.size(); j++) {
                    if (j != block && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { // хотя бы в одной мапе находим
                        std::lock_guard<std::mutex> guard(myMutex);
                        isUniqueElement = false;
                    }
                }
                if (isUniqueElement) {
                    std::lock_guard<std::mutex> guard(myMutex);
                    counter++;
                }
            }

        }
    });


    return counter;
}

template <typename T>
int uniqueCounterAtomic(vector<T> list, int threadsCount) {
    vector<unordered_map<T, int>> uniqueMaps(threadsCount);
    auto vectors = splitVector(list, threadsCount);

    parallelExec(threadsCount, [&](size_t block) {
        for (T item : vectors[block]) {
            uniqueMaps[block][item] += 1;
        }
        });

    atomic<int> counter = 0;
    parallelExec(threadsCount, [&](size_t block) {
        for (auto item : uniqueMaps[block]) {
            if (item.second == 1) {
                atomic<bool> isUniqueElement = true;
                for (int j = 0; j < uniqueMaps.size(); j++) {
                    if (j != block && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { // хотя бы в одной мапе находим
                        isUniqueElement = false;
                    }
                }
                if (isUniqueElement) {
                    counter++;
                }
            }
        }
     });


    return counter;
}



template <typename T>
int uniqueCounterSharedVariables(vector<T> list, int threadsCount) {
    vector<unordered_map<T, int>> uniqueMaps(threadsCount);
    auto vectors = splitVector(list, threadsCount);

    parallelExec(threadsCount, [&](size_t block) {
        for (T item : vectors[block]) {
            uniqueMaps[block][item] += 1;
        }
    });

    unordered_map<int, int> syncMap; // threadNumber: counter
    
    parallelExec(threadsCount, [&](size_t block) {
        for (auto item : uniqueMaps[block]) {
            if (item.second == 1) {
                bool isUniqueElement = true;
                for (int j = 0; j < uniqueMaps.size(); j++) {
                    if (j != block && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { // хотя бы в одной мапе находим
                        isUniqueElement = false;
                    }
                }
                if (isUniqueElement) {
                    syncMap[block] += 1;
                }
            }
        }
    });

    int counter = 0;
    for (auto item : syncMap) {
        counter += item.second;
    }

    return counter;
}

#endif // DOMAIN_H