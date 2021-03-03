// parallel1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <map>

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
map<T, int> uniqueCounter(vector<T> list) {
    map<T, int> uniqueMap = {};
    for (T item : list) {
        if (exists(uniqueMap, item)) {
            int counter = uniqueMap.at(item) + 1;
            uniqueMap[item] = counter;
        }
        else {
            uniqueMap.insert(pair<T, int>(item, 1));
        }

    }
    return uniqueMap;
}

int main() {
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

    return 0;
}
