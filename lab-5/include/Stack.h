#ifndef STACK_H
#define STACK_H

#include <memory>
#include "Stack_Iterator.h"

template <typename T, typename Allocator = std::allocator<T>>
class Stack {
public:
    using iterator = StackIterator<T>;

    explicit Stack(std::size_t capacity, const Allocator& alloc = Allocator())
        : capacity_(capacity), size_(0), allocator_(alloc) {
        data_ = allocator_.allocate(capacity_);
    }

    ~Stack() {
        clear();
        allocator_.deallocate(data_, capacity_);
    }

    void push(const T& value) {
        if (size_ >= capacity_) {
            throw std::runtime_error("Stack overflow");
        }
        std::allocator_traits<Allocator>::construct(allocator_, &data_[size_], value);
        ++size_;
    }

    void pop() {
        if (size_ == 0) {
            throw std::runtime_error("Stack underflow");
        }
        --size_;
        std::allocator_traits<Allocator>::destroy(allocator_, &data_[size_]);
    }

    T& top() {
        if (size_ == 0) {
            throw std::runtime_error("Stack is empty");
        }
        return data_[size_ - 1];
    }

    std::size_t get_size() const {
        return size_;
    }

    void clear() {
        while (size_ > 0) {
            pop();
        }
    }

    iterator begin() { return iterator(data_); }

    iterator end() { return iterator(data_ + size_); }

private:
    T* data_;
    std::size_t capacity_;
    std::size_t size_;
    Allocator allocator_;
};

#endif
