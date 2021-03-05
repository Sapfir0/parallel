#include <functional>
#include <chrono>
#include <iostream>

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
        std::cout << elasped.count() << " seconds" << std::endl;

        return result;
    }

private:
    std::function<R(Args ...)> f_;
};

template <class R, class... Args>
ExeTime<R(Args ...)> measureTime(R(*f)(Args ...)) {
    return ExeTime<R(Args...)>(std::function<R(Args...)>(f));
}