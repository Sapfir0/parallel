#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <random>
#include <chrono>

using namespace std;

int* randomVector(size_t size) {
    vector<int> v(size);
    random_device rd;
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0, size); // guaranteed unbiased
    generate(v.begin(), v.end(), [&] {return uni(rng); });
    
    int* arr = &v[0];
    return arr;
}


double checkSerialTime(function<void(int[])> func, int list[]) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed;

    start = std::chrono::system_clock::now();
    func(list);
    end = std::chrono::system_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() << "" << std::endl;
    return elapsed.count();
}

double checkParallelTime(function<void(int[], int)> func, int list[], int threadsCount) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed;

    start = std::chrono::system_clock::now();
    func(list, threadsCount);
    end = std::chrono::system_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() << "" << std::endl;
    return elapsed.count();
}