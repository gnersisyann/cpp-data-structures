#pragma once

#include <initializer_list>
#include <iostream>

class Set
{
   private:
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node* parent;
        bool color;

        Node(int val);
    };

    Node* root_;
    int size_;

    bool compareNodes(Node* node1, Node* node2) const;

   public:
    Set();
    Set(const Set& right);
    Set(std::initializer_list<int> li);
    ~Set();

    class iterator
    {
       private:
        Node* current;

       public:
        iterator(Node* current);

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int*;
        using reference = int&;

        const int& operator*();

        iterator& operator++();
        iterator operator++(int);

        bool operator==(const iterator& right) const;
        bool operator!=(const iterator& right) const;

        Node* min(Node* node);

        Node* getCurrent();
    };

    Set& operator=(const Set& right);

    bool operator==(const Set& right) const;
    bool operator!=(const Set& right) const;

    void clear(Node* node);

    void rotateLeft(Node* node);
    void rotateRight(Node* node);

    void balanceInsertion(Node* node);
    void balanceErase(Node* node);

    Node* min(Node* node);
    Node* copyTree(const Node* node, Node* parent);

    void transplant(Node* u, Node* v);

    void insert(int element);
    void erase(int element);
    bool contains(int element) const;
    bool empty() const noexcept;
    int size() const noexcept;

    iterator begin();
    iterator end();
    iterator find(int element);
    void erase(iterator it);
    iterator lower_bound(int value);
    iterator upper_bound(int value);
};
