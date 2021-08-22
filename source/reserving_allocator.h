#pragma once

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

    const size_t MaxBlockSize = S;

    reserving_allocator() = default;
    ~reserving_allocator() = default;

    template<typename U>
    reserving_allocator(const reserving_allocator<U, S>&) {

    }

    T* allocate(std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        auto p = std::malloc(n * sizeof(T));
        if (p == nullptr)
            throw std::bad_alloc();
        return reinterpret_cast<T*>(p);
    }

    void deallocate(T* p, std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
#ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T* p) {
#ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~T();
    }
};