#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#include <functional>
#include <chrono>
#include <iostream>
#include <vector>

template <class> struct ExeTime;

// Execution time decorator
template <class R, class... Args>
struct ExeTime<R(Args ...)> {
public:
    ExeTime(std::function<R(Args...)> func) : f_(func) { }

    R operator ()(Args ... args) {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> elasped;

        start = std::chrono::system_clock::now();
        R result = f_(args...);
        end = std::chrono::system_clock::now();
        elasped = end - start;
        std::cout << elasped.count() << "" << std::endl;

        return result;
    }

private:
    std::function<R(Args ...)> f_;
};

template <class R, class... Args>
ExeTime<R(Args ...)> measureTime(R(*f)(Args ...)) {
    return ExeTime<R(Args...)>(std::function<R(Args...)>(f));
}

tuple<int, double> checkTime(function<int(vector<int>, int)> func, vector<int> list, int threadsCount) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed;

    start = std::chrono::system_clock::now();
    auto result = func(list, threadsCount);
    end = std::chrono::system_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() << "" << std::endl;
    return { result, elapsed.count() };
}

template<typename T>
std::vector<std::vector<T>> splitVector(const std::vector<T>& vec, size_t n)
{
    std::vector<std::vector<T>> outVec;

    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;

        outVec.push_back(std::vector<T>(vec.begin() + begin, vec.begin() + end));

        begin = end;
    }

    return outVec;
}

#endif //TIME_HELPER_H 