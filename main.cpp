#include "custom_list.h"
#include "reserving_allocator.h"
#include <iostream>
#include <map>


int main() {
    // Create std::map
    const size_t MaxElements = 10;
    auto standartMap = std::map<int, int>{};
    standartMap[0] = 1;
    for (size_t i = 1; i < MaxElements; ++i)
        standartMap[i] = i * standartMap[i - 1];

    // Create map with reserved allocator
    auto mapWithReservingAllocator = std::map<
        int,
        int,
        std::less<int>,
        reserving_allocator<std::pair<const int, int>, MaxElements>
    >{};

    for (const auto& v : standartMap)
        mapWithReservingAllocator[v.first] = v.second;

    for (const auto& v : mapWithReservingAllocator)
        std::cout << v.first << " " << v.second << std::endl;

    List<int> customList;
    for (size_t i = 0; i < MaxElements; ++i) {
        customList.push_back(i);
    }

    List<int, reserving_allocator<int, MaxElements>> customListWithReservedAllocator;
    for (size_t i = 0; i < MaxElements; ++i) {
        customListWithReservedAllocator.push_back(i);
    }

    for (const auto& v : customListWithReservedAllocator) {
        std::cout << v << std::endl;
    }

    return 0;
}
