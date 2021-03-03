// parallel1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <map>

using namespace std;

bool exists(map<int, int> dict, int elem) {
    return dict.find(elem) != dict.end();
}

map<int, int> uniqueCounter(vector<int> list) {
    map<int, int> uniqueMap = {};
    for (int item : list) {
        if (exists(uniqueMap, item)) {
            int counter = uniqueMap.at(item) + 1;
            uniqueMap[item] = counter;
        }
        else {
            uniqueMap.insert(pair<int, int>(item, 1));
        }

    }
    return uniqueMap;
}

int main() {
    vector<int> list = {1, -1, 1, 0, 9, 12, 3, -3, 0, 12, -12};

    auto res = uniqueCounter(list);
    for (auto elem : res)
    {
        std::cout << elem.first << " " << elem.second << "\n";
    }

    return 0;
}
