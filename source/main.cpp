#include "custom_list.h"
#include "reserving_allocator.h"
#include <iostream>
#include <map>



int main() {

    //std::list<int>stdList;
    //auto it = stdList.begin();
    //std::cout << *it << std::endl;
    List<int> myList;
    for (auto i = 0; i < 5; ++i) {
        myList.push_back(i);
    }

    //1. 
    List<int>::iterator iter;
    //2. 
    List<int>::iterator iter2 = myList.begin();
    //3.
    std::cout << *iter2 << std::endl;
    //4.
    *iter2 = 9;
    std::cout << *iter2 << std::endl;

    //5.
    ++iter2;
    std::cout << *iter2 << std::endl;

    //7.
    std::cout << "Show all container ..." << std::endl;
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Tests with allocator
    //8.
    List<int, std::allocator<int>> arrWithAlloc1;
    arrWithAlloc1.push_back(1);
    //9.
    List<int, reserving_allocator<int, 10>> arrWithResAlloc;
    for (auto i = 9; i < 18; ++i) {
        arrWithResAlloc.push_back(i);
    }

    for (const auto& v : arrWithResAlloc) {
        std::cout << v << std::endl;
    }


    //
    ////for (List<int>::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    //List<int>::iterator iter = myList.begin();
    //std::cout << *iter << std::endl;
    //++iter;

    //std::cout << *iter << std::endl;
    //++iter;

    //std::cout << *iter << std::endl;
    //++iter;

    //std::cout << *iter << std::endl;
    ////}
    
    //// Fill standart map
    //const auto MaxElements = 10;
    //auto standartMap = std::map<int, int>{};
    //standartMap[0] = 1;
    //for (auto i = 1; i < MaxElements; ++i)
    //    standartMap[i] = i * standartMap[i - 1];

    //for (const auto& v : standartMap)
    //    std::cout << v.first << " " << v.second << std::endl;

    //auto mapWithReservingAllocator = std::map<
    //    int,
    //    int,
    //    std::less<int>,
    //    reserving_allocator<std::pair<const int, int>, 10>
    //>{};

    //for (const auto& v : standartMap)
    //    mapWithReservingAllocator[v.first] = v.second;

    ////--
    //auto itFind = mapWithReservingAllocator.find(4);
    //if (itFind != mapWithReservingAllocator.end()) {
    //    std::cout << "Delete element from map..." << std::endl;
    //    mapWithReservingAllocator.erase(itFind);
    //    std::cout << "Insert new element to map..." << std::endl;
    //    mapWithReservingAllocator.insert(std::make_pair(11, 111));
    //}

    //for (auto i = 22; i < 31; ++i)
    //    mapWithReservingAllocator.insert(std::make_pair(i, i*10));
    ////--

    //for (const auto& v : mapWithReservingAllocator)
    //    std::cout << v.first << " " << v.second << std::endl;

    //mapWithReservingAllocator.clear();

    ///*auto ar = std::vector<int, reserving_allocator<int, 10>>{};
    //ar.reserve(5);
    //for (auto i = 0; i < 12; ++i) {
    //    ar.emplace_back(i);
    //}

    //for (auto v : ar) {
    //    std::cout << v << std::endl;
    //}*/

    return 0;
}
