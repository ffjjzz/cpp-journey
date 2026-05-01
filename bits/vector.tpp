#pragma once

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


template<typename T, typename Allocator>
bool vector<T, Allocator>::empty() const noexcept {
	return size_ == 0;
}

template<typename T, typename Allocator>
vector<T, Allocator>::size_type vector<T, Allocator>::size() const noexcept {
	return size_;
}

template<typename T, typename Allocator>
vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const noexcept {
	return capacity_;
}

template<typename T, typename Allocator>
vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const noexcept {
	return allocator_;
}


template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type pos){
	return data_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type pos)const {
	return data_[pos];
}


template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos){
	if (pos >= size_){
		throw std::out_of_range("vector pos out of range");
	}
	return data_[pos];
}


template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const {
	if (pos >= size_){
		throw std::out_of_range("vector pos out of range");
	}
	return data_[pos];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front() noexcept{
	return data_[0];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const noexcept{
	return data_[0];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() noexcept{
	return data_[size_ - 1];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const noexcept{
	return data_[size_ - 1];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::pointer vector<T, Allocator>::data() noexcept{
	return data_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_pointer vector<T, Allocator>::data() const noexcept{
	return data_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() noexcept{
	return data_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const noexcept{
	return data_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cbegin()const noexcept{
	return data_;
}
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() noexcept{
	return data_ + size_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const noexcept{
	return data_ + size_;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cend()const noexcept{
	return data_ + size_;
}
//reverse iterators
template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() noexcept{
	return reverse_iterator(end());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const noexcept{
	return const_reverse_iterator(cend());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::crbegin()const noexcept{
	return const_reverse_iterator(cend());
}
template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() noexcept{
	return reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const noexcept{
	return const_reverse_iterator(cbegin());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::crend()const noexcept{
	return const_reverse_iterator(cbegin());
}

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

template<typename T, typename Allocator>
void vector<T, Allocator>::clear() noexcept {
	if (data_){
		for (size_type i = 0; i < size_; ++i){
			traits::destroy(allocator_, data_ + i);
		}
	}
	size_ = 0;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::deallocate(size_type capacity) noexcept {
	if (data_){
		traits::deallocate(allocator_, data_, capacity);
		capacity_ = 0;
		data_ = nullptr;
	}
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::pointer 
vector<T, Allocator>::allocate(size_type capacity){
	return traits::allocate(allocator_, capacity);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::zero() noexcept {
	capacity_ = 0;
	size_ = 0;
	data_ = nullptr;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type new_capacity){
	if (new_capacity <= capacity_){return ;}

	pointer new_data = allocate(new_capacity);
	if (data_){
		for (size_type i = 0; i < size_; ++i){
			traits::construct(allocator_, new_data + i, std::move(data_[i]));
		}
	}
	size_type tmp_size = size_;
	clear();
	deallocate(capacity_);

	capacity_ = new_capacity;
	size_ = tmp_size;
	data_ = new_data;
}


template<typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit(){
	if (capacity_ == size_){return ;}
	
	size_type new_capacity = size_;
	pointer new_data = allocate(new_capacity);

	for (size_type i = 0; i < size_; ++i){
		traits::construct(allocator_, new_data + i, std::move(data_[i]));
	}

	clear();
	deallocate(capacity_);

	data_ = new_data;
	size_ = new_capacity;
	capacity_ = new_capacity;
}


