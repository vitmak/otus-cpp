#pragma once

#include"memory_manager.h"
#include <cstdio>

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
        if (n > S)
            throw std::bad_alloc();

        auto addr = m_memoryMng.GetFreeMemory(n);
        if (nullptr == addr)
            throw std::bad_alloc();
        return addr;
    }

    void deallocate(pointer p, std::size_t n) {
        m_memoryMng.SetMemoryState(p, n, MemoryStates::eFree);
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        ((pointer)p)->~T();
    }
};