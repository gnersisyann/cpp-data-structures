#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <optional>
#pragma once

template <typename T>
class List
{
   private:
    struct Node
    {
        T data;
        Node* next;
        Node* previous;
        Node(const T& value);
    };
    Node* head;
    Node* tail;
    std::size_t size_;

   public:
    class iterator
    {
       private:
        std::optional<Node*> current;
        List<T>* list_;

       public:
        explicit iterator(List<T>* list, std::optional<Node*> node) : list_(list), current(node) {}
        explicit iterator(const List<T>* list, std::optional<Node*> node) : list_(list), current(node) {}

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator& right);
        bool operator==(const iterator& right) const;
        bool operator!=(const iterator& right);
        T& operator*();
        T* operator->();
        Node* get_current() const;
        std::optional<Node*> cur() const;
        List<T>* lis() const;
    };

    class reverse_iterator
    {
       private:
        std::optional<Node*> current;
        List<T>* list_;

       public:
        explicit reverse_iterator(List<T>* list, std::optional<Node*> node) : list_(list), current(node) {}

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        reverse_iterator& operator++();
        reverse_iterator operator++(int);
        reverse_iterator& operator--();
        reverse_iterator operator--(int);
        bool operator==(const reverse_iterator& right);
        bool operator!=(const reverse_iterator& right);
        T& operator*();
    };

    class const_iterator
    {
       private:
        std::optional<Node*> current;
        const List<T>* list_;

       public:
        explicit const_iterator(const List<T>* list, std::optional<Node*> node) : list_(list), current(node) {}
        const_iterator(const iterator& other);

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator& right);
        bool operator==(const iterator& right);
        bool operator!=(const const_iterator& right);
        bool operator!=(const iterator& right);
        const T& operator*();
        const T* operator->();
        void operator=(const iterator& right);
    };

    class const_reverse_iterator
    {
       private:
        std::optional<Node*> current;
        const List<T>* list_;

       public:
        explicit const_reverse_iterator(const List<T>* list, std::optional<Node*> node) : list_(list), current(node) {}

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_reverse_iterator& operator++();
        const_reverse_iterator operator++(int);
        const_reverse_iterator& operator--();
        const_reverse_iterator operator--(int);
        bool operator==(const const_reverse_iterator& right);
        bool operator!=(const const_reverse_iterator& right);
        const T& operator*();
    };

    List();
    List(std::size_t size);
    List(int size, const T& value);
    List(const List<T>& copy);
    List(std::initializer_list<T> init);
    template <typename inputIt>
    List(inputIt begin, inputIt end);
    ~List();

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    iterator begin();
    iterator end();
    const_iterator begin() const;
    iterator end() const;
    iterator before_begin();

    std::size_t getSize();

    bool empty();
    std::size_t size() const;
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();

    void insert(const iterator& it, const T& value);
    void erase(const iterator& it);
    void merge(List<T>& list);
    void sort();
    void swap(T& left, T& right);

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_front();
    void pop_back();
    void clear();

    bool operator==(const List& right);
    bool operator!=(const List& right);
    List& operator=(const List& right);
};

