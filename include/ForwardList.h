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
	ForwardList(size_t size);
	ForwardList(size_t size, const T& value);
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

template <typename T>
ForwardList<T>::iterator::iterator(Node* node) : current(node)
{
}

template <typename T>
ForwardList<T>::iterator::iterator(Node* node, Node* head_) : current(node), head(head_)
{
}

template <typename T>
T& ForwardList<T>::iterator::operator*()
{
    if (!current) throw std::out_of_range("Dereferencing end iterator");
    return current->data;
}

template <typename T>
bool ForwardList<T>::iterator::operator!=(const iterator& other) const
{
    return current != other.current;
}

template <typename T>
bool ForwardList<T>::iterator::operator==(const iterator& other) const
{
    return current == other.current;
}

template <typename T>
typename ForwardList<T>::iterator& ForwardList<T>::iterator::operator++()
{
    if (current == nullptr)
        current = head;
    else
        current = current->next;
    return *this;
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::iterator::operator++(int)
{
    iterator tmp = *this;
    if (current == nullptr)
        current = head;
    else
        current = current->next;
    return tmp;
}

template <typename T>
T* ForwardList<T>::iterator::operator->()
{
    return &(current->data);
}

template <typename T>
ForwardList<T>::const_iterator::const_iterator(const Node* node) : current(node)
{
}

template <typename T>
ForwardList<T>::const_iterator::const_iterator(const iterator& it) : current(it.current)
{
}

template <typename T>
const T& ForwardList<T>::const_iterator::operator*() const
{
    if (!current) throw std::out_of_range("Dereferencing end iterator");
    return current->data;
}

template <typename T>
const T* ForwardList<T>::const_iterator::operator->() const
{
    return &(current->data);
}

template <typename T>
bool ForwardList<T>::const_iterator::operator!=(const const_iterator& other) const
{
    return current != other.current;
}

template <typename T>
bool ForwardList<T>::const_iterator::operator==(const const_iterator& other) const
{
    return current == other.current;
}

template <typename T>
typename ForwardList<T>::const_iterator& ForwardList<T>::const_iterator::operator++()
{
    if (current) current = current->next;
    return *this;
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::const_iterator::operator++(int)
{
    const_iterator tmp = *this;
    if (current) current = current->next;
    return tmp;
}

template <typename T>
ForwardList<T>::ForwardList() : head(nullptr)
{
}

template <typename T>
ForwardList<T>::ForwardList(size_t size) : head(nullptr)
{
    for (size_t i = 0; i < size; ++i)
    {
        push_front(T());
    }
}

template <typename T>
ForwardList<T>::ForwardList(size_t size, const T& value) : head(nullptr)
{
    for (size_t i = 0; i < size; ++i)
    {
        push_front(value);
    }
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList<T>& other) : head(nullptr)
{
    Node* tmp = other.head;
    Node* prev = nullptr;
    while (tmp)
    {
        Node* newNode = new Node(tmp->data);
        if (prev)
            prev->next = newNode;
        else
            head = newNode;
        prev = newNode;
        tmp = tmp->next;
    }
}

template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> init) : head(nullptr)
{
    for (auto it = init.end(); it != init.begin();)
    {
        --it;
        emplace_front(*it);
    }
}

template <typename T>
template <typename InputIt>
ForwardList<T>::ForwardList(InputIt begin, InputIt end) : head(nullptr)
{
    ForwardList<T> temp;
    while (begin != end)
    {
        temp.push_front(*begin);
        ++begin;
    }

    Node* tmp = temp.head;
    while (tmp)
    {
        push_front(tmp->data);
        tmp = tmp->next;
    }
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    clear();
}

template <typename T>
bool ForwardList<T>::operator==(const ForwardList<T>& other) const
{
    Node* tmp1 = head;
    Node* tmp2 = other.head;
    while (tmp1 && tmp2)
    {
        if (tmp1->data != tmp2->data) return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return tmp1 == nullptr && tmp2 == nullptr;
}

template <typename T>
bool ForwardList<T>::operator!=(const ForwardList<T>& other) const
{
    return !(*this == other);
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
    if (this == &other) return *this;

    clear();

    Node* tmp = other.head;
    Node* prev = nullptr;
    while (tmp)
    {
        Node* newNode = new Node(tmp->data);
        if (prev)
            prev->next = newNode;
        else
            head = newNode;
        prev = newNode;
        tmp = tmp->next;
    }

    return *this;
}

template <typename T>
void ForwardList<T>::push_front(const T& value)
{
    Node* tmp = new Node(value);
    tmp->next = head;
    head = tmp;
}

template <typename T>
void ForwardList<T>::pop_front()
{
    if (head)
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <typename T>
void ForwardList<T>::insert_after(const ForwardList<T>::iterator& it, const T& value)
{
    Node* tmp = new Node(value);
    if (it.get_current() == nullptr)
    {
        tmp->next = head;
        head = tmp;
    }
    else
    {
        tmp->next = it.get_current()->next;
        it.get_current()->next = tmp;
    }
}

template <typename T>
void ForwardList<T>::erase_after(const ForwardList<T>::iterator& it)
{
    if (it.get_current() == nullptr)
    {
        if (head != nullptr)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        return;
    }

    Node* tmp = it.get_current()->next;

    if (tmp != nullptr)
    {
        it.get_current()->next = tmp->next;
        delete tmp;
    }
}

template <typename T>
template <typename... Args>
void ForwardList<T>::emplace_front(Args&&... args)
{
    Node* tmp = new Node(T(std::forward<Args>(args)...));
    tmp->next = head;
    head = tmp;
}

template <typename T>
bool ForwardList<T>::empty() const
{
    return head == nullptr;
}

template <typename T>
T& ForwardList<T>::front()
{
    if (head)
    {
        return head->data;
    }
    throw std::out_of_range("List is empty");
}

template <typename T>
const T& ForwardList<T>::front() const
{
    if (head)
    {
        return head->data;
    }
    throw std::out_of_range("List is empty");
}

template <typename T>
void ForwardList<T>::clear()
{
    while (head)
    {
        pop_front();
    }
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::before_begin()
{
    return iterator(nullptr, head);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::begin() const
{
    return const_iterator(head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::end() const
{
    return const_iterator(nullptr);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cend() const
{
    return const_iterator(nullptr);
}
