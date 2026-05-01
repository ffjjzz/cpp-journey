#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>
#include <stdexcept>
#include <concepts>
#include <iterator>



template<typename T, typename Allocator=std::allocator<T>>
class vector{
public:
	
	using value_type = T;
	using allocator_type = Allocator;

	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

	using iterator = pointer;
	using const_iterator = const_pointer;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	using traits = std::allocator_traits<Allocator>;



public: //constructors
	vector() noexcept;
	explicit vector(const Allocator& alloc) noexcept;

	explicit vector(size_type count, const Allocator& alloc=Allocator());
	vector(size_type count, const T& base_value, const Allocator& alloc=Allocator());

	vector(std::initializer_list<T> init, const Allocator& alloc=Allocator());

	vector(const vector& other);
	vector(const vector& other, const Allocator& alloc);
	vector(vector&& other) noexcept;
	vector(vector&& other, const Allocator& alloc);

	~vector() noexcept;

	vector& operator=(const vector& other);
	vector& operator=(vector&& other) noexcept;

	vector& operator=(std::initializer_list<T> ilist);

public: //done and checked
	reference operator[](size_type pos);
	const_reference operator[](size_type pos) const;

	reference at(size_type pos);
	const_reference at(size_type pos) const;
	
	reference front() noexcept;
	const_reference front() const noexcept;

	reference back() noexcept;
	const_reference back() const noexcept;

	pointer data() noexcept;
	const_pointer data() const noexcept;

public://done and checked
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

	reverse_iterator rbegin() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator crbegin() const noexcept;

	reverse_iterator rend() noexcept;
	const_reverse_iterator rend() const noexcept;
	const_reverse_iterator crend() const noexcept;

public://done and checked
	bool empty() const noexcept;
	size_type size() const noexcept;
	size_type capacity() const noexcept;

	void reserve(size_type new_capacity);
	void shrink_to_fit();

public:
	void clear() noexcept;

	iterator insert(const_iterator pos, const T& value);
	iterator insert(const_iterator pos, T&& value);
	iterator insert(const_iterator pos, size_type count, const T& value);

	iterator insert(const_iterator pos, std::initializer_list<T> ilist);

	template<typename... Args>
	iterator emplace(const_iterator pos, Args&&... args);

	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);

	void push_back(const T& value);
	void push_back(T&& value);

	template <typename... Args>
	reference emplace_back(Args&&... args);

	void pop_back();

	void resize(size_type count);
	void resize(size_type count, const value_type& value);

	void swap(vector& other) noexcept;

public: //done
	allocator_type get_allocator() const noexcept;

private:
	pointer data_;
	size_type size_;
	size_type capacity_;
	allocator_type allocator_;


private: //done and checked
	void deallocate(size_type count) noexcept;
	pointer allocate(size_type capacity);
	void zero() noexcept;
};

#include"vector.tpp"
