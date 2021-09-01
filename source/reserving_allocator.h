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

    // Тестовая реализация: работает только для одного блока памяти
    pointer allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;

        if (n > S)
            throw std::bad_alloc();

        auto freeMemory = m_memoryMng.GetFreeMemory();
        return freeMemory;
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U* p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_memoryMng.SetMemoryState(reinterpret_cast<pointer>(p), MemoryStates::eFree);
        ((pointer)p)->~T();
    }
};