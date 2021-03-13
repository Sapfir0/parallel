#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
#include <unordered_map>
#include <mutex>

using namespace std;

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
                    if (j != i && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { // хотя бы в одной мапе находим
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
                    if (j != i && uniqueMaps[j].find(item.first) != uniqueMaps[j].end()) { // хотя бы в одной мапе находим
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

#endif // DOMAIN_H