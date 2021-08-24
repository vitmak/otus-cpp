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

        return m_memoryMng.GetFreeMemory();
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
//        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
        m_memoryMng.SetMemoryState(reinterpret_cast<pointer>(p), false);
    };

    template<typename U>
    void destroy(U* p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_memoryMng.SetMemoryState(reinterpret_cast<pointer>(p), true);
        ((pointer)p)->~T();
    }


    //template<typename ...Args>
    //void construct(pointer p, Args &&...args) {
    //    std::cout << __PRETTY_FUNCTION__ << std::endl;
    //    new(p) value_type(std::forward<Args>(args)...);
    //    m_memoryMng.SetMemoryState(U, false);
    //};

    //void destroy(T* p) {
    //    std::cout << __PRETTY_FUNCTION__ << std::endl;
    //    m_memoryMng.SetMemoryState(U, true);
    //    ((pointer)p)->~T();
    //}
};