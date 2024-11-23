#pragma once

#include <iterator>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <type_traits>

template <typename T>
class ForwardList
{
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& value) : data(value), next(nullptr) {}
	};
	Node* head;
public:
	class iterator {
	private:
		Node* current;
		Node* head;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator(Node* node);
		iterator(Node* node, Node* head_);
		iterator& operator++();
		iterator operator++(int);
		T& operator*();
		bool operator!=(const iterator& other) const;
		bool operator==(const iterator& other) const;
		T* operator->();

		Node* get_current() const { return current; }

		friend class const_iterator;
	};

	class const_iterator {
	private:
		const Node* current;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = const T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		const_iterator(const Node* node);
		const_iterator(const iterator& it);
		const_iterator& operator++();
		const_iterator operator++(int);
		const T& operator*() const;
		bool operator!=(const const_iterator& other) const;
		bool operator==(const const_iterator& other) const;
		const T* operator->() const;
	};

	//constructors
	ForwardList();
	ForwardList(int size);
	ForwardList(int size, const T& value);
	ForwardList(const ForwardList<T>& other);
	ForwardList(std::initializer_list<T> init);
	template <typename InputIt>
	ForwardList(InputIt begin, InputIt end);
	~ForwardList();

	//
	void push_front(const T& value);
	void pop_front();
	template <typename... Args>
	void emplace_front(Args&&... args);
	void insert_after(const iterator& it, const T& value);
	void erase_after(const ForwardList<T>::iterator& it);

	//operators
	bool operator==(const ForwardList<T>& other) const;
	bool operator!=(const ForwardList<T>& other) const;
	ForwardList<T>& operator=(const ForwardList<T>& other);

	//funcs
	bool empty() const;
	const T& front() const;
	T& front();
	void clear();

	//iterators
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	iterator before_begin();
};
