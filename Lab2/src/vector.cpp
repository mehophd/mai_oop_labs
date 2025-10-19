#include "vector.h"
#include <memory>
#include <algorithm>  

Vector::Vector() : size_(0), capacity_(0), data_(nullptr) {}

Vector::Vector(size_t count, const unsigned char& value)
    : size_(count), capacity_(count < 10 ? 10 : count), data_(allocator_.allocate(capacity_)) {
    size_t idx = 0;
    try {
        for (; idx < count; ++idx) {
            std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + idx, value);
        }
    } catch (...) {
        for (size_t j = 0; j < idx; ++j) {
            std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + j);
        }
        allocator_.deallocate(data_, capacity_);
        throw;
    }
}

Vector::Vector(const Vector& other)
    : allocator_(other.allocator_), size_(other.size_), capacity_(other.size_ < 10 ? 10 : other.size_), data_(allocator_.allocate(capacity_)) {
    try {
        std::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
    } catch (...) {
        allocator_.deallocate(data_, capacity_);
        throw;
    }
}

Vector::Vector(Vector&& other) noexcept
    : allocator_(std::move(other.allocator_)), size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector::Vector(std::initializer_list<unsigned char> init)
    : size_(init.size()), capacity_(init.size() < 10 ? 10 : init.size()), data_(allocator_.allocate(capacity_)) {
    size_t idx = 0;
    try {
        for (const auto& item : init) {
            std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + idx, item);
            ++idx;
        }
    } catch (...) {
        for (size_t j = 0; j < idx; ++j) {
            std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + j);
        }
        allocator_.deallocate(data_, capacity_);
        throw;
    }
}

unsigned char& Vector::Front() const noexcept {
    return data_[0];
}

unsigned char& Vector::Back() const noexcept {
    return data_[size_ - 1];
}

unsigned char* Vector::Data() const noexcept {
    return data_;
}

bool Vector::IsEmpty() const noexcept {
    return size_ == 0;
}

size_t Vector::Size() const noexcept {
    return size_;
}

size_t Vector::Capacity() const noexcept {
    return capacity_;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    unsigned char* new_data = allocator_.allocate(new_capacity);
    size_t idx = 0;
    try {
        for (; idx < size_; ++idx) {
            std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, new_data + idx, std::move_if_noexcept(data_[idx]));
        }
    } catch (...) {
        for (size_t j = 0; j < idx; ++j) {
            std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, new_data + j);
        }
        allocator_.deallocate(new_data, new_capacity);
        throw;
    }

    for (size_t j = 0; j < size_; ++j) {
        std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + j);
    }
    allocator_.deallocate(data_, capacity_);

    data_ = new_data;
    capacity_ = new_capacity;
}

void Vector::Clear() noexcept {
    for (size_t i = 0; i < size_; ++i) {
        std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + i);
    }
    size_ = 0;
}

void Vector::Insert(size_t pos, unsigned char value) {
    if (pos > size_) {
        return;
    }
    if (size_ + 1 > capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    for (size_t i = size_; i > pos; --i) {
        std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + i, std::move(data_[i - 1]));
        std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + i - 1);
    }

    std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + pos, std::move(value));
    ++size_;
}

void Vector::Erase(size_t begin_pos, size_t end_pos) {
    if (begin_pos > end_pos || begin_pos > size_) {
        return;
    }
    size_t diff = end_pos - begin_pos;
    if (diff == 0) {
        return;
    }

    for (size_t i = begin_pos; i < end_pos; ++i) {
        std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + i);
    }

    for (size_t i = end_pos; i < size_; ++i) {
        std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + begin_pos + (i - end_pos),
                                                                       std::move_if_noexcept(data_[i]));
        std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + i);
    }
    size_ -= diff;
}

void Vector::PushBack(unsigned char value) {
    if (size_ >= capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + size_, std::move(value));
    ++size_;
}

void Vector::PopBack() {
    --size_;
    std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + size_);
}

void Vector::Resize(size_t count, const unsigned char& value) {
    if (count > capacity_) {
        Reserve(count);
    }

    if (count > size_) {
        for (size_t i = size_; i < count; ++i) {
            std::allocator_traits<std::allocator<unsigned char>>::construct(allocator_, data_ + i, value);
        }
    } else {
        for (size_t i = count; i < size_; ++i) {
            std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + i);
        }
    }
    size_ = count;
}

Vector::~Vector() {
    for (size_t i = 0; i < size_; ++i) {
        std::allocator_traits<std::allocator<unsigned char>>::destroy(allocator_, data_ + i);
    }
    allocator_.deallocate(data_, capacity_);
}