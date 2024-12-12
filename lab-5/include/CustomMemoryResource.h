#ifndef CUSTOM_MEMORY_RESOURCE_H
#define CUSTOM_MEMORY_RESOURCE_H

#include <memory_resource>
#include <vector>
#include <cstddef>
#include <cassert>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    explicit CustomMemoryResource(std::size_t total_size)
        : buffer_(total_size), offset_(0) {}

    ~CustomMemoryResource() {
        buffer_.clear();
        allocations_.clear();
        free_list_.clear();
    }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        for (auto it = free_list_.begin(); it != free_list_.end(); ++it) {
            if (it->second >= bytes) {
                void* ptr = it->first;
                free_list_.erase(it);
                return ptr;
            }
        }

        std::size_t current_offset = align_offset(offset_, alignment);
        if (current_offset + bytes > buffer_.size()) {
            throw std::bad_alloc();
        }
        void* ptr = buffer_.data() + current_offset;
        offset_ = current_offset + bytes;
        allocations_.push_back(ptr);
        return ptr;
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        free_list_.emplace_back(p, bytes);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    std::vector<char> buffer_;
    std::size_t offset_;
    std::vector<void*> allocations_;
    std::vector<std::pair<void*, std::size_t>> free_list_;

    std::size_t align_offset(std::size_t offset, std::size_t alignment) const {
        std::size_t misalignment = offset % alignment;
        if (misalignment == 0) {
            return offset;
        }
        return offset + (alignment - misalignment);
    }
};

#endif
