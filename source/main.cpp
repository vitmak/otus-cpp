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

    //--
    auto itFind = mapWithReservingAllocator.find(4);
    if (itFind != mapWithReservingAllocator.end()) {
        std::cout << "Delete element from map..." << std::endl;
        mapWithReservingAllocator.erase(itFind);
        std::cout << "Insert new element to map..." << std::endl;
        mapWithReservingAllocator.insert(std::make_pair(11, 111));
    }

    for (auto i = 22; i < 31; ++i)
        mapWithReservingAllocator.insert(std::make_pair(i, i*10));
    //--

    for (const auto& v : mapWithReservingAllocator)
        std::cout << v.first << " " << v.second << std::endl;

    mapWithReservingAllocator.clear();

    /*auto ar = std::vector<int, reserving_allocator<int, 10>>{};
    ar.reserve(5);
    for (auto i = 0; i < 12; ++i) {
        ar.emplace_back(i);
    }

    for (auto v : ar) {
        std::cout << v << std::endl;
    }*/

    return 0;
}
