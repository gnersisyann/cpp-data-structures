#include "../include/List.h"

template <typename T>
List<T>::const_iterator::const_iterator(const iterator& other) : current(other.cur())
{
}

template <typename T>
std::size_t List<T>::getSize()
{
    return size_;
}

template <typename T>
void List<T>::swap(T& left, T& right)
{
    T temp = left;
    left = right;
    right = temp;
}

template <typename T>
void List<T>::sort()
{
    auto it = begin();
    auto jt = it;
    while (it != end())
    {
        it++;
        jt = it;
        it--;
        while (jt != end())
        {
            if (*it > *jt)
            {
                swap(*it, *jt);
            }
            jt++;
        }
        it++;
    }
}

template <typename T>
void List<T>::merge(List<T>& list)
{
    auto it1 = begin();
    auto it2 = list.begin();

    List<T> newList;

    while (it1 != end() && it2 != list.end())
    {
        if (*it2 < *it1)
        {
            newList.push_back(*it2);
            ++it2;
        }
        else
        {
            newList.push_back(*it1);
            ++it1;
        }
    }

    while (it2 != list.end())
    {
        newList.push_back(*it2);
        ++it2;
    }
    while (it1 != end())
    {
        newList.push_back(*it1);
        ++it1;
    }

    clear();
    for (auto& value : newList)
    {
        push_back(value);
    }

    list.clear();
}

template <typename T>
typename List<T>::Node* List<T>::iterator::get_current() const
{
    return current.value_or(nullptr);
}

template <typename T>
std::optional<typename List<T>::Node*> List<T>::iterator::cur() const
{
    return current;
}

template <typename T>
List<T>* List<T>::iterator::lis() const
{
    return list_;
}

template <typename T>
T* List<T>::iterator::operator->()
{
    if (!current.has_value() || !current.value())
    {
        throw std::runtime_error("Dereferencing invalid iterator");
    }
    return &(current.value()->data);
}

template <typename T>
const T* List<T>::const_iterator::operator->()
{
    if (!current.has_value() || !current.value())
    {
        throw std::runtime_error("Dereferencing invalid iterator");
    }
    return &(current.value()->data);
}

template <typename T>
void List<T>::insert(const List<T>::iterator& it, const T& value)
{
    if (it == end())
    {
        push_back(value);
        return;
    }

    if (it == begin())
    {
        push_front(value);
        return;
    }

    Node* newNode = new Node(value);
    Node* currentNode = it.get_current();

    if (!currentNode)
    {
        return;
    }

    newNode->next = currentNode;
    newNode->previous = currentNode->previous;

    if (currentNode->previous)
    {
        currentNode->previous->next = newNode;
    }
    else
    {
        head = newNode;
    }

    currentNode->previous = newNode;
    size_++;
}

template <typename T>
void List<T>::erase(const List<T>::iterator& it)
{
    Node* currentNode = it.get_current();

    if (!currentNode)
    {
        return;
    }

    if (it == end())
    {
        pop_back();
        return;
    }

    if (it == begin())
    {
        pop_front();
        return;
    }

    if (currentNode->previous)
    {
        currentNode->previous->next = currentNode->next;
    }
    if (currentNode->next)
    {
        currentNode->next->previous = currentNode->previous;
    }
    delete currentNode;
    size_--;
}

template <typename T>
template <typename inputIt>
List<T>::List(inputIt begin, inputIt end) : head(nullptr), tail(nullptr), size_(0)
{
    while (begin != end)
    {
        push_back(*begin);
        begin++;
    }
}

template <typename T>
List<T>::List(std::initializer_list<T> init) : head(nullptr), tail(nullptr), size_(0)
{
    for (auto it = init.begin(); it != init.end(); it++)
    {
        push_back(*it);
    }
}

template <typename T>
const T& List<T>::const_reverse_iterator::operator*()
{
    if (current)
        return current.value()->data;
    else
        throw std::bad_optional_access();
}

template <typename T>
bool List<T>::const_reverse_iterator::operator==(const const_reverse_iterator& right)
{
    return current == right.current;
}

template <typename T>
bool List<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& right)
{
    return !(*this == right);
}

template <typename T>
typename List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator--()
{
    if (!current)
    {
        current = std::optional<Node*>(list_->head);
    }
    else
    {
        Node* nextNode = current.value()->next;
        if (nextNode)
            current = std::optional<Node*>(nextNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator++()
{
    if (current)
    {
        Node* prevNode = current.value()->previous;
        if (prevNode)
            current = std::optional<Node*>(prevNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::crbegin() const
{
    return List<T>::const_reverse_iterator(this, tail);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::crend() const
{
    return List<T>::const_reverse_iterator(this, std::nullopt);
}

template <typename T>
void List<T>::const_iterator::operator=(const List<T>::iterator& right)
{
    current = right.cur();
    list_ = right.lis();
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator& right)
{
    return current == right.current;
}

template <typename T>
bool List<T>::const_iterator::operator==(const iterator& right)
{
    return current == right.cur();
}

template <typename T>
bool List<T>::const_iterator::operator!=(const iterator& right)
{
    return !(*this == right);
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& right)
{
    return !(*this == right);
}

template <typename T>
const T& List<T>::const_iterator::operator*()
{
    if (current)
        return current.value()->data;
    else
        throw std::bad_optional_access();
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const
{
    return const_iterator(this, head);
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const
{
    // return const_iterator(this, head);
    return const_iterator(this, std::nullopt);
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    if (current)
    {
        Node* nextNode = current.value()->next;
        if (nextNode)
            current = std::optional<Node*>(nextNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    if (!current)
    {
        current = std::optional<Node*>(list_->tail);
    }
    else
    {
        Node* prevNode = current.value()->previous;
        if (prevNode)
            current = std::optional<Node*>(prevNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
T& List<T>::reverse_iterator::operator*()
{
    if (current)
        return current.value()->data;
    else
        throw std::bad_optional_access();
}

template <typename T>
bool List<T>::reverse_iterator::operator==(const reverse_iterator& right)
{
    return current == right.current;
}

template <typename T>
bool List<T>::reverse_iterator::operator!=(const reverse_iterator& right)
{
    return !(*this == right);
}

template <typename T>
typename List<T>::reverse_iterator& List<T>::reverse_iterator::operator--()
{
    if (!current)
    {
        current = std::optional<Node*>(list_->head);
    }
    else
    {
        Node* nextNode = current.value()->next;
        if (nextNode)
            current = std::optional<Node*>(nextNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator++(int)
{
    reverse_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::reverse_iterator& List<T>::reverse_iterator::operator++()
{
    if (current)
    {
        Node* prevNode = current.value()->previous;
        if (prevNode)
            current = std::optional<Node*>(prevNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator--(int)
{
    reverse_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::rbegin()
{
    return List<T>::reverse_iterator(this, tail);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::rend()
{
    return List<T>::reverse_iterator(this, std::nullopt);
}

template <typename T>
T& List<T>::iterator::operator*()
{
    if (current)
        return current.value()->data;
    else
        throw std::bad_optional_access();
}

template <typename T>
bool List<T>::iterator::operator==(const iterator& right)
{
    return current == right.current;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator& right) const
{
    return current == right.current;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator& right)
{
    return !(*this == right);
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    if (current)
    {
        Node* nextNode = current.value()->next;
        if (nextNode)
            current = std::optional<Node*>(nextNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    if (!current)
    {
        current = std::optional<Node*>(list_->tail);
    }
    else
    {
        Node* prevNode = current.value()->previous;
        if (prevNode)
            current = std::optional<Node*>(prevNode);
        else
            current = std::nullopt;
    }
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
    return List<T>::iterator(this, head);
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
    return List<T>::iterator(this, std::nullopt);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return List<T>::const_iterator(this, head);
}

template <typename T>
typename List<T>::iterator List<T>::end() const
{
    return List<T>::iterator(this, std::nullopt);
}

template <typename T>
typename List<T>::iterator List<T>::before_begin()
{
    return List<T>::iterator(this, std::nullopt);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& right)
{
    if (this == &right) return *this;
    clear();

    Node* element = right.head;
    while (element)
    {
        push_back(element->data);
        element = element->next;
    }
    return *this;
}

template <typename T>
bool List<T>::operator==(const List<T>& right)
{
    Node* l = this->head;
    Node* r = right.head;
    while (l && r)
    {
        if (l->data != r->data) return false;
        l = l->next;
        r = r->next;
    }
    return l == nullptr && r == nullptr;
}

template <typename T>
bool List<T>::operator!=(const List<T>& right)
{
    return !(*this == right);
}

template <typename T>
List<T>::List(const List<T>& copy)
{
    Node* element = copy.head;
    while (element)
    {
        push_back(element->data);
        element = element->next;
    }
}

template <typename T>
void List<T>::clear()
{
    while (size_) pop_front();
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
std::size_t List<T>::size() const
{
    return size_;
}

template <typename T>
List<T>::List(int size, const T& value) : head(nullptr), tail(nullptr), size_(0)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        push_back(value);
    }
}

template <typename T>
const T& List<T>::front() const
{
    return head->data;
}

template <typename T>
T& List<T>::front()
{
    return head->data;
}

template <typename T>
const T& List<T>::back() const
{
    return tail->data;
}

template <typename T>
T& List<T>::back()
{
    return tail->data;
}

template <typename T>
void List<T>::pop_front()
{
    if (!head) return;
    Node* old = head;
    head = head->next;
    if (head)
    {
        head->previous = nullptr;
    }
    else
    {
        tail = nullptr;
    }
    delete old;
    --size_;
}

template <typename T>
void List<T>::pop_back()
{
    if (!tail) return;
    Node* old = tail;
    tail = tail->previous;
    if (tail)
    {
        tail->next = nullptr;
    }
    else
    {
        head = nullptr;
    }
    delete old;
    --size_;
}

template <typename T>
void List<T>::push_back(const T& value)
{
    Node* newNode = new Node(value);
    if (!tail)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    ++size_;
}

template <typename T>
void List<T>::push_front(const T& value)
{
    Node* newNode = new Node(value);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }
    ++size_;
}

template <typename T>
List<T>::Node::Node(const T& value) : data(value), next(nullptr), previous(nullptr)
{
}

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0)
{
}

template <typename T>
List<T>::List(std::size_t size) : head(nullptr), tail(nullptr), size_(0)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        push_back(T());
    }
}

template <typename T>
bool List<T>::empty()
{
    return size_ == 0;
}