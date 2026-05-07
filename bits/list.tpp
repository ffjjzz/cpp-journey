#pragma once

//constructors ready
template<typename T, typename Allocator>
list<T, Allocator>::list(): alloc(Allocator()), cur_size(0) { init_sentinel(); }


template<typename T, typename Allocator>
list<T, Allocator>::list(const Allocator& alloc):
	alloc(alloc),
	cur_size(0)
{ init_sentinel(); }

template<typename T, typename Allocator>
list<T, Allocator>::list(size_type count, const T& value, const Allocator& alloc):
	alloc(alloc),
	cur_size(0)
{
	init_sentinel();
	for (size_type i = 0; i < count; ++i){
		push_back(value);
	}
}

template<typename T, typename Allocator>
list<T, Allocator>::list(std::initializer_list<T> init, const Allocator& alloc): 
	alloc(alloc),
	cur_size(0) {
	init_sentinel();
	
	for (const T& value: init){
		push_back(value);
	}
}


template<typename T, typename Allocator>
list<T, Allocator>::list(const list& other):
	alloc(AllocTraits::select_on_container_copy_construction(other.alloc)),
	cur_size(0){

	init_sentinel();
	for (const T& value: other)
		push_back(value);
	}


template<typename T, typename Allocator>
list<T, Allocator>::list(const list& other, const Allocator& alloc):
	alloc(alloc),
	cur_size(0){
	init_sentinel();

	for (const T& value: other)
		push_back(value);
	}


template<typename T, typename Allocator>
list<T, Allocator>::list(list&& other) noexcept: 
	alloc(std::move(other.alloc)),
	cur_size(other.cur_size),
	sentinel(other.sentinel) {
		other.init_sentinel();
		other.cur_size = 0;
	}



template<typename T, typename Allocator>
list<T, Allocator>::list(list&& other, const Allocator& alloc): 
	alloc(other.alloc),
	cur_size(other.cur_size),
	sentinel(other.sentinel) {
		other.init_sentinel();
		other.cur_size = 0;
	}


template<typename T, typename Allocator>
list<T, Allocator>::~list(){
	clear();
	AllocTraits::deallocate(alloc, sentinel, 1);
}


//copy
template<typename T, typename Allocator>
list<T, Allocator>&
list<T, Allocator>::operator=(const list& other) {
    if (this == &other) {
        return *this;
    }

    list tmp(other);
    swap(tmp);
    return *this;
}

template<typename T, typename Allocator>
list<T, Allocator>&
list<T, Allocator>::operator=(list&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();
    AllocTraits::deallocate(alloc, sentinel, 1);

    alloc = std::move(other.alloc);
    sentinel = other.sentinel;
    cur_size = other.cur_size;

    other.init_sentinel();
    other.cur_size = 0;

    return *this;
}


template<typename T, typename Allocator>
list<T, Allocator>&
list<T, Allocator>::operator=(std::initializer_list<T> ilist) {
    list tmp(ilist, alloc);
    swap(tmp);
    return *this;
}

template<typename T, typename Allocator>
typename list<T, Allocator>::allocator_type
list<T, Allocator>::get_allocator() const noexcept {
    return alloc;
}


//getters
template<typename T, typename Allocator>
typename list<T, Allocator>::reference
list<T, Allocator>::front() {
    return sentinel->next->data;
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_reference
list<T, Allocator>::front() const {
    return sentinel->next->data;
}

template<typename T, typename Allocator>
typename list<T, Allocator>::reference
list<T, Allocator>::back() {
    return sentinel->prev->data;
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_reference
list<T, Allocator>::back() const {
    return sentinel->prev->data;
}

//iterators
template<typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::begin() noexcept {
    return iterator(sentinel->next);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::begin() const noexcept {
    return const_iterator(sentinel->next);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::cbegin() const noexcept {
    return const_iterator(sentinel->next);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::end() noexcept {
    return iterator(sentinel);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::end() const noexcept {
    return const_iterator(sentinel);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::cend() const noexcept {
    return const_iterator(sentinel);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::reverse_iterator
list<T, Allocator>::rbegin() noexcept {
    return reverse_iterator(end()); 
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::crbegin() const noexcept {
    return const_reverse_iterator(cend());
}


template<typename T, typename Allocator>
typename list<T, Allocator>::reverse_iterator
list<T, Allocator>::rend() noexcept {
    return reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::crend() const noexcept {
    return const_reverse_iterator(cbegin());
}

//sup
template<typename T, typename Allocator>
bool list<T, Allocator>::empty() const noexcept{
    return cur_size == 0;
}


template<typename T, typename Allocator>
typename list<T, Allocator>::size_type
list<T, Allocator>::size() const noexcept{
    return cur_size;
}

//other
template<typename T, typename Allocator>
void list<T, Allocator>::clear() noexcept{
	size_type sz = cur_size;
	for (size_type i = 0; i < sz; ++i){
		Node* tmp = sentinel->next;
		unlink(tmp);
		destroy_node(tmp);
	}
}


template<typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator pos, const T& value) {
    	Node* n  = make_node(value);
	link_before(pos.cur, n);
	return iterator(n);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator pos, T&& value) {
    	Node* n  = make_node(std::move(value));
	link_before(pos.cur, n);
	return iterator(n);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator pos,size_type count, const T& value) {
	if (count == 0) return iterator(pos.cur);

	Node* first_inserted = nullptr;

	for (size_type i = 0; i < count; ++i){
    		Node* n  = make_node(value);
		link_before(pos.cur, n);
		if(!first_inserted){
			first_inserted = n;
		}
	}
	return iterator(first_inserted);
}

template<typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> init) {
	if (init.size() ==0 ) return iterator(pos.cur);
	Node* first_inserted = nullptr;

	for (const T& value: init){
    		Node* n  = make_node(value);
		link_before(pos.cur, n);
		if(!first_inserted){
			first_inserted = n;
		}
	}
	return iterator(first_inserted);
}


template<typename T, typename Allocator>
template<typename... Args>
typename list<T, Allocator>::reference
list<T, Allocator>::emplace_back(Args&&... args){
	Node* n = make_node(std::forward<Args>(args)...);
	link_before(sentinel, n);
	return n->data;
}

template<typename T, typename Allocator>
template<typename... Args>
typename list<T, Allocator>::reference
list<T, Allocator>::emplace_front(Args&&... args){
	Node* n = make_node(std::forward<Args>(args)...);
	link_before(sentinel->next, n);
	return n->data;
}

template<typename T, typename Allocator>
void list<T, Allocator>::push_back(const T& value) {
	Node* n = make_node(value);
	link_before(sentinel, n);
}

template<typename T, typename Allocator>
void list<T, Allocator>::push_back(T&& value) {
	Node* n = make_node(std::move(value));
	link_before(sentinel, n);
}



template<typename T, typename Allocator>
void list<T, Allocator>::push_front(const T& value) {
	Node* n = make_node(value);
	link_before(sentinel->next, n);
}

template<typename T, typename Allocator>
void list<T, Allocator>::push_front(T&& value) {
	Node* n = make_node(std::move(value));
	link_before(sentinel->next, n);
}


template<typename T, typename Allocator>
void list<T, Allocator>::resize(size_type count) {
    if (count < cur_size) {
        while (cur_size > count) {
            pop_back();
        }
    } else if (count > cur_size) {
        while (cur_size < count) {
            emplace_back();
        }
    }
}

template<typename T, typename Allocator>
void list<T, Allocator>::resize(size_type count, const T& value) {
    if (count < cur_size) {
        while (cur_size > count) {
            pop_back();
        }
    } else if (count > cur_size) {
        while (cur_size < count) {
            push_back(value);
        }
    }
}

template<typename T, typename Allocator>
void list<T, Allocator>::swap(list& other) noexcept {
    using std::swap;
    swap(sentinel, other.sentinel);
    swap(cur_size, other.cur_size);
    swap(alloc, other.alloc);
}

