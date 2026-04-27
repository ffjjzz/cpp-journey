#pragma once

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


