#include<cstddef>
#include<iterator>
#include<memory>
#include<initializer_list>
#include<utility>
#include<stdexcept>

template<typename T, typename Allocator = std::allocator<T>>
class list
{
private:
	struct Node{
		T data;
		Node* next;
		Node* prev;

	template<typename... Args>
	explicit Node(Args&&... args): data(std::forward<Args>(args)...), prev(nullptr), next(nullptr) {}
	
	};

	using NodeAlloc = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using AllocTraits = std::allocator_traits<NodeAlloc>;

	NodeAlloc alloc;
	Node* sentinel;
	size_t cur_size;

	void deallocate(Node* ptr){
		AllocTraits::deallocate(alloc, ptr, 1);
	}

	void destroy_node(Node* ptr){
		AllocTraits::destroy(alloc, ptr);
		deallocate(ptr);
	}

	Node* alloc_node(){
		return AllocTraits::allocate(alloc, 1);
	}

	template<typename... Args>
	Node* make_node(Args&&... args){
		Node* ptr = alloc_node();

		AllocTraits::construct(alloc, ptr, std::forward<Args>(args)...);

		return ptr;
	}

	void init_sentinel(){
		sentinel = this->alloc_node();
		sentinel->prev = sentinel; 
		sentinel->next = sentinel;
	}

	void unlink(Node* n){
		n->prev->next = n->next;
		n->next->prev = n->prev;
		--cur_size;
	}

	void link_before(Node* pos, Node* n){
		n->next = pos;
		n->prev = pos->prev;
		pos->prev = n;
		n->prev->next = n;
		++cur_size;
	}

public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

	class const_iterator{
	protected:
		Node* cur;
		explicit const_iterator(Node* ptr): cur(ptr) {}
		friend class list;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		reference operator*()const noexcept{ return cur -> data;}
		pointer operator->() const noexcept {return &cur->data; }

		const_iterator& operator++() noexcept {cur = cur->next; return *this;}
		const_iterator operator++(int) noexcept {auto t = *this; ++*this; return t;}

		const_iterator& operator--() noexcept {cur = cur->prev; return *this;}
		const_iterator operator--(int) noexcept {auto t = *this; --*this; return t;}

		bool operator==(const_iterator o) const noexcept {return cur == o.cur;}
		bool operator!=(const_iterator o) const noexcept {return cur != o.cur;}
	};

	class iterator: public const_iterator{
		explicit iterator(Node* p) :const_iterator(p) {}
		friend class list;

	public:
		using pointer = T*;
		using reference = T&;

		reference  operator*()  const noexcept { return  this->cur->data; }
        	pointer    operator->() const noexcept { return &this->cur->data; }
        	iterator& operator++() noexcept { this->cur = this->cur->next; return *this; }
        	iterator  operator++(int) noexcept { auto t = *this; ++*this; return t; }
        	iterator& operator--() noexcept { this->cur = this->cur->prev; return *this; }
        	iterator  operator--(int) noexcept { auto t = *this; --*this; return t; }
    };

    	using reverse_iterator       = std::reverse_iterator<iterator>;
    	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
	list();
    	explicit list(const Allocator& alloc);
    	explicit list(size_type count, const T& value = T(), const Allocator& alloc = Allocator());

    	list(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    	list(const list& other);

    	list(const list& other, const Allocator& alloc);

    	list(list&& other) noexcept;

    	list(list&& other, const Allocator& alloc);
    	~list();


public:
	list& operator=(const list& other);
    	list& operator=(list&& other) noexcept;
    	list& operator=(std::initializer_list<T> ilist);

    	void assign(size_type count, const T& value);
    	template<typename InputIt>
    	void assign(InputIt first, InputIt last);
    	void assign(std::initializer_list<T> ilist);

    	allocator_type get_allocator() const noexcept;

public:
	reference       front();
    	const_reference front() const;
    	reference       back();
    	const_reference back()  const;

public:
	iterator               begin()   noexcept;
    	const_iterator         begin()   const noexcept;
    	const_iterator         cbegin()  const noexcept;
    	iterator               end()     noexcept;
    	const_iterator         end()     const noexcept;
    	const_iterator         cend()    const noexcept;
    	reverse_iterator       rbegin()  noexcept;
    	const_reverse_iterator rbegin()  const noexcept;
    	const_reverse_iterator crbegin() const noexcept;
    	reverse_iterator       rend()    noexcept;
    	const_reverse_iterator rend()    const noexcept;
    	const_reverse_iterator crend()   const noexcept;

public:

	bool empty()    const noexcept;
    	size_type size()     const noexcept;
    	size_type max_size() const noexcept;

public:

	void clear() noexcept;

    	iterator insert(const_iterator pos, const T& value);
    	iterator insert(const_iterator pos, T&& value);
    	iterator insert(const_iterator pos, size_type count, const T& value);
    	template<typename InputIt>
    	iterator insert(const_iterator pos, InputIt first, InputIt last);
    	iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    	template<typename... Args>
    	iterator emplace(const_iterator pos, Args&&... args);

    	iterator erase(const_iterator pos);
    	iterator erase(const_iterator first, const_iterator last);

    	void push_back(const T& value);
    	void push_back(T&& value);
    	template<typename... Args>
    	reference emplace_back(Args&&... args);

    	void push_front(const T& value);
    	void push_front(T&& value);
    	template<typename... Args>
    	reference emplace_front(Args&&... args);

    	void pop_back()  noexcept;
    	void pop_front() noexcept;

    	void resize(size_type count);
    	void resize(size_type count, const T& value);

    	void swap(list& other) noexcept;


};


#include"list.tpp"
