#pragma once


template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value)
{
	if (size_ == capacity_){reserve(capacity_ ==0 ? 1 : 2* capacity_);}


	traits::construct(allocator_, data_ + size_, value);
	size_++;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(T&& value)
{
	if (size_ == capacity_){reserve(capacity_ == 0 ? 1 : 2* capacity_);}

	traits::construct(allocator_, data_ + size_, std::move(value));
	size_++;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::pop_back()
{
	traits::destroy(allocator_, data_ + --size_);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count) {
    if (count < size_) {
        for (size_type i = count; i < size_; ++i) {
            traits::destroy(allocator_, data_ + i);
        }
    } else if (count > size_) {
        if (count > capacity_) {
            reserve(count);
        }
        for (size_type i = size_; i < count; ++i) {
            traits::construct(allocator_, data_ + i);
        }
    }
    size_ = count;
}


template<typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count, const value_type& value) {
    if (count < size_) {
        for (size_type i = count; i < size_; ++i) {
            traits::destroy(allocator_, data_ + i);
        }
    } else if (count > size_) {
        if (count > capacity_) {
            reserve(count);
        }
        for (size_type i = size_; i < count; ++i) {
            traits::construct(allocator_, data_ + i, value);
        }
    }
    size_ = count;
}


template<typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept{
	using std::swap;
	swap(capacity_, other.capacity_);
	swap(size_, other.size_);
	swap(allocator_, other.allocator_);
	swap(data_, other.data_);
}

template<typename T, typename Allocator>
template<typename... Args>
typename vector<T, Allocator>::reference
vector<T, Allocator>::emplace_back(Args&&... args){
	if (size_ == capacity_){
		reserve(capacity_ == 0 ? 1 : 2* capacity_);
	}
	traits::construct(allocator_, data_+ size_++, std::forward<Args>(args)...);

	return back();
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(const_iterator pos) {
    size_type index = pos - cbegin();

    for (size_type i = index; i + 1 < size_; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }

    traits::destroy(allocator_, data_ + (size_ - 1));
    --size_;

    return begin() + index;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
    if (first == last) {
        return begin() + (first - cbegin());
    }

    size_type start = first - cbegin();
    size_type finish = last - cbegin();
    size_type count = finish - start;

    for (size_type i = start; i + count < size_; ++i) {
        data_[i] = std::move(data_[i + count]);
    }

    for (size_type i = size_ - count; i < size_; ++i) {
        traits::destroy(allocator_, data_ + i);
    }

    size_ -= count;

    return begin() + start;
}



template<typename T, typename Allocator>
template<typename... Args>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::emplace(const_iterator pos, Args&&... args) {
    size_type index = pos - cbegin();

    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : 2 * capacity_);
    }

    if (index == size_) {
        traits::construct(allocator_, data_ + size_, std::forward<Args>(args)...);
        ++size_;
        return begin() + index;
    }

    traits::construct(allocator_, data_ + size_, std::move(data_[size_ - 1]));

    for (size_type i = size_ - 1; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }

    data_[index].~T();
    traits::construct(allocator_, data_ + index, std::forward<Args>(args)...);

    ++size_;
    return begin() + index;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, const T& value) {
    return emplace(pos, value);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, T&& value) {
    return emplace(pos, std::move(value));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, size_type count, const T& value) {
    size_type index = pos - cbegin();

    if (count == 0) {
        return begin() + index;
    }

    if (size_ + count > capacity_) {
        size_type new_cap = capacity_ == 0 ? count : capacity_;
        while (new_cap < size_ + count) {
            new_cap *= 2;
            if (new_cap == 0) {
                new_cap = count;
            }
        }
        reserve(new_cap);
    }

    for (size_type i = 0; i < count; ++i) {
        emplace(cbegin() + index + i, value);
    }

    return begin() + index;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
    size_type index = pos - cbegin();

    if (ilist.size() == 0) {
        return begin() + index;
    }

    if (size_ + ilist.size() > capacity_) {
        size_type new_cap = capacity_ == 0 ? ilist.size() : capacity_;
        while (new_cap < size_ + ilist.size()) {
            new_cap *= 2;
            if (new_cap == 0) {
                new_cap = ilist.size();
            }
        }
        reserve(new_cap);
    }

    size_type i = 0;
    for (const auto& elem : ilist) {
        emplace(cbegin() + index + i, elem);
        ++i;
    }

    return begin() + index;
}


#include "support_tools.ipp"
