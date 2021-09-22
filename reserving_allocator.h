#pragma once

#include"memory_manager.h"
#include <cstdio>
#include <memory>

template<typename T, size_t S>
struct reserving_allocator {
    using value_type = T;

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

    value_type* allocate(std::size_t n) {
        if (n > S)
            throw std::bad_alloc();

        auto addr = m_memoryMng.GetFreeMemory(n);
        if (nullptr == addr)
            throw std::bad_alloc();
        return addr;
    }

    void deallocate(value_type* p, std::size_t n) {
        m_memoryMng.SetMemoryState(p, n, MemoryStates::eFree);
    }
    
    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        ((value_type*)p)->~T();
    }
};