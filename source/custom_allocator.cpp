#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <map>


template<typename T>
struct custom_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = custom_allocator<U>;
    };

    custom_allocator() = delete;

    custom_allocator(size_t size) : m_size(size) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    //custom_allocator(const custom_allocator&) = delete;
    ~custom_allocator() = default;

    template<typename U> 
    custom_allocator(const custom_allocator<U>& alloc) noexcept : m_size(alloc.m_size)  {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    template<typename U>
    custom_allocator(const custom_allocator<U>&& alloc) noexcept : m_size(alloc.m_size), m_memory(alloc.m_memory) {
        alloc.m_memory = nullptr;
        alloc.m_size = 0;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    pointer allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << "[m_size = " << m_size << "]" << std::endl;
        
        if (n > m_size)
            throw std::bad_alloc();

        void* p = nullptr;
        static bool isInit = false;
        if (!isInit) {
            p = std::malloc(m_size * sizeof(value_type));
            if (!p)
                throw std::bad_alloc();
            m_memory = reinterpret_cast<pointer>(p);
            return m_memory;
        }
        else {
            return m_memory + n;
        }
    }

    void deallocate(pointer p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U* p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }

    size_t m_size = 0;
    pointer m_memory = nullptr;
};

int main(int, char *[]) {
    custom_allocator<int> customAllocator{5};
    std::vector<int, custom_allocator<int>> v{ std::move(customAllocator) };
    // v.reserve(5);
    for (int i = 0; i < 6; ++i) {
        std::cout << "vector capacity: " << v.capacity() << "\t" << "vector size = " << v.size() << std::endl;
        v.emplace_back(i);
        std::cout << std::endl;
    }

    // std::cout << "\n\n\n\nAfter creation\n\n\n\n" << std::endl;
    // auto v2 = v;

    /*auto m = std::map<
        int,
        float,
        std::less<int>,
        custom_allocator<
            std::pair<
                const int, float
            >
        >
    >{};

    for (int i = 0; i < 1; ++i) {
        m[i] = static_cast<float>(i);
    }*/

    return 0;
}
