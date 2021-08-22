#include "reserving_allocator.h"
#include<iostream>
#include<map>

int main() {
    // Fill standart map
    auto standartMap = std::map<int, int>{};

    standartMap[0] = 1;
    for (auto i = 1; i < 10; ++i)
        standartMap[i] = i * standartMap[i - 1];

    for (const auto& v : standartMap) {
        std::cout << v.first << " " << v.second << std::endl;
    }

    return 0;
}
