#pragma once

#include"pretty.h"
#include"memory_manager.h"

template<typename T, size_t S>
struct reserving_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = reserving_allocator<U, S>;
    };

    MemoryManager<T, S> m_memoryMng;

    reserving_allocator() = default;
    ~reserving_allocator() = default;

    template<typename U>
    reserving_allocator(const reserving_allocator<U, S>&) {

    }

    pointer allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;

        if (n > S)
            throw std::bad_alloc();

        auto addr = m_memoryMng.GetFreeMemory(n);
        std::cout << "Get address: " << addr << std::endl;
        return addr;
    }

    void deallocate(pointer p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        std::cout << "Start address: " << p << std::endl;
        m_memoryMng.SetMemoryState(p, n, MemoryStates::eFree);
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U* p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << p << std::endl;
        ((pointer)p)->~T();
    }
};