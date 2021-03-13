#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <random>
#include <algorithm>
#include <mutex>

using namespace std;

bool findIn(vector<int> collection, int item) {
    return find(collection.begin(), collection.end(), item) != collection.end();
}

bool isEqual(vector<int> list1, vector<int> list2) {
    return list1 == list2;
}

void testIsEqualList(vector<int> list1, vector<int> list2) {
    auto res = isEqual(list1, list2) ? "Equal" : "Not equal";
    std::cout << res << endl;
}

void testIsEqualLength(int l1, int l2) {
    if (l1 != l2) {
        cout << "Not equal len: " + to_string(l1) + " " + to_string(l2);
    }
}

vector<int> randomVector(size_t size) {
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


#endif //COUNTER_SORT_HELPER_H