#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class my_unique {
    T* _ptr;

    using reference = T&;

public:

    my_unique() = delete;

    my_unique(T* value): _ptr(value) {}

    my_unique(const my_unique&) = delete;

    my_unique(my_unique&& ptr) noexcept: _ptr(ptr.release())  {}

    explicit my_unique(T&& ptr) {
        if (ptr)
            _ptr = ptr;
    }

    my_unique& operator=(const T&) = delete;

    my_unique& operator=(my_unique&& ptr) {
        if (this != &ptr) {
            delete _ptr;
            _ptr = ptr._ptr;
            ptr._ptr = nullptr;
        }
        return *this;
    }

    reference operator*() { 
        return *_ptr;
    }

    T* release() {
        T* temp = _ptr;
        _ptr = nullptr;
        return temp;
    }
   
    T* get() {
        return _ptr;
    }
   
    ~my_unique() {
        delete _ptr;
        _ptr = nullptr;
    }
};

int main() {   
    int* ptr = new int(4);
    
    my_unique<int> s(ptr);

    std::cout << *s;

    return 0;
}