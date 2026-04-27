#pragma once


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

