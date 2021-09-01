#include "reserving_allocator.h"
#include<iostream>
#include<map>

int main() {
    // Fill standart map
    const auto MaxElements = 10;
    auto standartMap = std::map<int, int>{};
    standartMap[0] = 1;
    for (auto i = 1; i < MaxElements; ++i)
        standartMap[i] = i * standartMap[i - 1];

    for (const auto& v : standartMap)
        std::cout << v.first << " " << v.second << std::endl;

    auto mapWithReservingAllocator = std::map<
        int,
        int,
        std::less<int>,
        reserving_allocator<std::pair<const int, int>, 10>
    >{};

    for (const auto& v : standartMap)
        mapWithReservingAllocator[v.first] = v.second;

    for (const auto& v : mapWithReservingAllocator)
        std::cout << v.first << " " << v.second << std::endl;

    return 0;
}
