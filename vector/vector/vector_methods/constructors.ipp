#pragma once
#include<iostream>

template<typename T, typename Allocator>
vector<T, Allocator>::vector() noexcept :
    size_(0), 
    capacity_(0), 
    allocator_(Allocator()), 
    data_(nullptr){}


template<typename T, typename Allocator>
vector<T, Allocator>::vector(const Allocator& alloc) noexcept :
    size_(0), 
    capacity_(0),
    allocator_(alloc),
    data_(nullptr){}


template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_type count, const T& base_value, const Allocator& alloc) :
    data_(nullptr),
    size_(count), 
    capacity_(count), 
    allocator_(alloc) {
    data_ = allocate(capacity_);
    for (size_type i=0; i < capacity_; ++i){
        traits::construct(allocator_, data_+ i, base_value);
    }
}



template<typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> init, const Allocator& alloc) :
    data_(nullptr),
    size_(init.size()),
    capacity_(init.size()),
    allocator_(alloc) {
    data_ = allocate(capacity_);

    size_type i = 0;
    for (const auto& value : init){
        traits::construct(allocator_, data_ + i, value);
        ++i;
    }
}


template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other) :
    size_(other.size_),
    capacity_(other.capacity_),
    allocator_(other.allocator_),
    data_(nullptr) {
    data_ = allocate(capacity_);
    for (size_type i = 0; i < size_; ++i){
        traits::construct(allocator_, data_ + i, *(other.data_ + i));
    }
}


template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other, const Allocator& alloc) :
    size_(other.size_),
    capacity_(other.capacity_),
    allocator_(alloc),
    data_(nullptr) {
    data_ = allocate(capacity_);
    for (size_type i = 0; i < size_; ++i){
        traits::construct(allocator_, data_ + i, *(other.data_ + i));
    }
}


template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept :
    size_(other.size_),
    capacity_(other.capacity_),
    allocator_(other.allocator_),
    data_(other.data_) {
    other.zero();
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other, const Allocator& alloc) :
    size_(other.size_),
    capacity_(other.capacity_),
    allocator_(alloc),
    data_(other.data_) {
    other.zero();
}

template<typename T, typename Allocator>
vector<T, Allocator>::~vector() noexcept {
    clear();
    deallocate(capacity_);
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    deallocate(capacity_);

    data_ = nullptr;
    size_ = other.size_;
    capacity_ = other.capacity_;
    allocator_ = other.allocator_;

    if (capacity_ > 0) {
        data_ = allocate(capacity_);
        for (size_type i = 0; i < size_; ++i) {
            traits::construct(allocator_, data_ + i, *(other.data_ + i));
        }
    }

    return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();
    deallocate(capacity_);

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    allocator_ = other.allocator_;

    other.zero();

    return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> ilist) {
    clear();
    deallocate(capacity_);

    capacity_ = ilist.size();
    size_ = ilist.size();
    allocator_ = Allocator();

    data_ = nullptr;
    if (capacity_ > 0) {
        data_ = allocate(capacity_);
        size_type i = 0;
        for (const auto& value : ilist) {
            traits::construct(allocator_, data_ + i, value);
            ++i;
        }
    }

    return *this;
}
#include"support_tools.ipp"
