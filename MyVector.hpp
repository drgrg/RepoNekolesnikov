#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Any>
class MyVector {
private:
    Any* data_;
    size_t size_;
    size_t capacity_;

    void _increase_capacity_(size_t need) {
        if (need <= capacity_) {
            return;
        }

        size_t new_cap = 1;
        while (new_cap < need) {
            new_cap <<= 1;
        }

        Any* new_data = new Any[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move_if_noexcept(data_[i]);

        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    MyVector(size_t len) : data_(nullptr), size_(0), capacity_(0) {
        if (len > 0) {
            data_ = new Any[len];
            size_ = len;
            capacity_ = len;
            for (size_t i = 0; i < len; ++i) {
                data_[i] = Any();
            }
        }
        else if (len == 0) {
            return;
        }
        else {
            throw std::length_error("MyVector: size must be a positive number");
        }
    }

    MyVector(size_t len, const Any& data)
        : data_(nullptr), size_(0), capacity_(0) {
        if (len > 0) {
            data_ = new Any[len];
            size_ = len;
            capacity_ = len;
            for (size_t i = 0; i < len; ++i) {
                data_[i] = data;
            }
        }
        else if (len == 0) {
            return;
        }
        else {
            throw std::length_error("MyVector: size must be a positive number");
        }
    }

    MyVector(const MyVector& other) : data_(nullptr), size_(0), capacity_(0) {
        if (other.size_ > 0) {
            data_ = new Any[other.size_];
            size_ = other.size_;
            capacity_ = other.size_;
            for (size_t i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        else {
            return;
        }
    }

    MyVector(MyVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    ~MyVector() noexcept {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    Any& operator[](size_t index) noexcept { return data_[index]; }
    const Any& operator[](size_t index) const noexcept { return data_[index]; }

    Any& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("MyVector::at out of range");
        }
        return data_[index];
    }
    const Any& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("MyVector::at out of range");
        }
        return data_[index];
    }

    Any& front() { return data_[0]; }
    const Any& front() const { return data_[0]; }

    Any& back() { return data_[size_ - 1]; }
    const Any& back() const { return data_[size_ - 1]; }

    Any* data() noexcept { return data_; }
    const Any* data() const noexcept { return data_; }

    Any* begin() noexcept { return data_; }
    const Any* begin() const noexcept { return data_; }

    Any* end() noexcept { return data_ + size_; }
    const Any* end() const noexcept { return data_ + size_; }

    bool empty() const noexcept { return size_ == 0; }

    size_t size() const noexcept { return size_; }

    size_t capacity() const noexcept { return capacity_; }

    const Any* cbegin() const noexcept { return data_; }
    const Any* cend() const noexcept { return data_ + size_; }

    void resize(size_t n) { resize(n, Any()); }

    void resize(size_t n, const Any& value) {
        if (n < size_) {
            size_ = n;
        }
        else if (n > size_) {
            _increase_capacity_(n);
            for (size_t i = size_; i < n; ++i) {
                data_[i] = value;
            }
            size_ = n;
        }
    }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            _increase_capacity_(new_cap);
        }
    }
    void shrink_to_fit() {
        if (size_ == capacity_) {
            return;
        }
        if (size_ == 0) {
            delete[] data_;
            data_ = nullptr;
            capacity_ = 0;
            return;
        }
        Any* new_data = new Any[size_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move_if_noexcept(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }

    void clear() noexcept {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
    }

    void push_back(const Any& elem) {
        if (size_ >= capacity_) {
            _increase_capacity_(size_ + 1);
        }
        data_[size_] = elem;
        ++size_;
    }

    void push_back(Any&& elem) {
        _increase_capacity_(size_ + 1);
        data_[size_] = std::move(elem);
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void swap(MyVector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    template <class... Args>
    Any& emplace_back(Args&&... args) {
        _increase_capacity_(size_ + 1);
        data_[size_] = Any(std::forward<Args>(args)...);
        return data_[size_++];
    }
};