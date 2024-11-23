#include "../include/ForwardList.h"

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
ForwardList<T>::ForwardList(int size) : head(nullptr)
{
    for (size_t i = 0; i < size; ++i)
    {
        push_front(T());
    }
}

template <typename T>
ForwardList<T>::ForwardList(int size, const T& value) : head(nullptr)
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
