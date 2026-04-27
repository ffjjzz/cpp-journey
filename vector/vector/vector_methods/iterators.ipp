#pragma once
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


