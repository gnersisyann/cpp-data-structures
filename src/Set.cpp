#include "../include/Set.h"

#include <initializer_list>

Set::Node::Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), color(true) {}

Set::Set() : root_(nullptr), size_(0){};

Set::~Set() { clear(root_); }

bool Set::empty() const { return !root_; }

int Set::size() const { return size_; }

Set& Set::operator=(const Set& other)
{
    if (this != &other)
    {
        clear(root_);
        root_ = nullptr;
        size_ = 0;

        if (other.root_)
        {
            root_ = copyTree(other.root_, nullptr);
            size_ = other.size_;
        }
    }
    return *this;
}

bool Set::compareNodes(Node* node1, Node* node2) const
{
    if (node1 == nullptr && node2 == nullptr) return true;
    if (node1 == nullptr || node2 == nullptr) return false;

    if (node1->value != node2->value || node1->color != node2->color) return false;

    return compareNodes(node1->left, node2->left) && compareNodes(node1->right, node2->right);
}

bool Set::operator==(const Set& other)
{
    if (this->root_ == other.root_) return true;

    if (this->root_ == nullptr || other.root_ == nullptr) return false;

    return compareNodes(this->root_, other.root_);
}

bool Set::operator!=(const Set& other) { return !(*this == other); }

Set::Node* Set::copyTree(const Node* node, Node* parent)
{
    if (!node) return nullptr;

    Node* newNode = new Node(node->value);
    newNode->color = node->color;
    newNode->parent = parent;

    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);

    return newNode;
}

Set::Set(const Set& other) : root_(nullptr), size_(0)
{
    if (other.root_)
    {
        root_ = copyTree(other.root_, nullptr);
        size_ = other.size_;
    }
}

Set::Set(std::initializer_list<int> li) : root_(nullptr), size_(0)
{
    for (const auto& it : li) insert(it);
}

void Set::clear(Node* node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

bool Set::contains(int element) const
{
    if (!root_) return false;
    Node* search = root_;
    while (search)
    {
        if (element > search->value)
            search = search->right;
        else if (element < search->value)
            search = search->left;
        else
            return true;
    }
    return false;
}

void Set::insert(int element)
{
    if (contains(element)) return;
    Node* t = new Node(element);
    if (!root_)
    {
        root_ = t;
        t->color = false;
        size_++;
        return;
    };
    Node* p = root_;
    Node* q = nullptr;
    while (p != nullptr)
    {
        q = p;
        if (p->value < t->value)
            p = p->right;
        else
            p = p->left;
    }
    t->parent = q;
    if (q->value < t->value)
        q->right = t;
    else
        q->left = t;
    balanceInsertion(t);
    size_++;
}

void Set::balanceInsertion(Node* t)
{
    if (t == root_)
    {
        t->color = false;
        return;
    }
    while (t->parent && t->parent->color)
    {
        if (t->parent == t->parent->parent->left)
        {
            if (t->parent->parent == nullptr) break;
            Node* uncle = t->parent->parent->right;
            if (uncle && uncle->color)
            {
                t->parent->color = false;
                uncle->color = false;
                t->parent->parent->color = true;
                t = t->parent->parent;
            }
            else
            {
                if (t == t->parent->right)
                {
                    t = t->parent;
                    rotateLeft(t);
                }
                t->parent->color = false;
                t->parent->parent->color = true;
                rotateRight(t->parent->parent);
            }
        }
        else
        {
            Node* uncle = t->parent->parent->left;
            if (uncle && uncle->color)
            {
                t->parent->color = false;
                uncle->color = false;
                t->parent->parent->color = true;
                t = t->parent->parent;
            }
            else
            {
                if (t == t->parent->left)
                {
                    t = t->parent;
                    rotateRight(t);
                }
                t->parent->color = false;
                t->parent->parent->color = true;
                rotateLeft(t->parent->parent);
            }
        }
    }
    root_->color = false;
}

void Set::erase(int element)
{
    Node* node = root_;
    while (node && node->value != element)
    {
        if (element < node->value)
            node = node->left;
        else
            node = node->right;
    }
    if (!node) return;

    Node* target = node;
    Node* replacement = nullptr;
    bool targetOriginalColor = target->color;

    if (!node->left && !node->right)
    {
        transplant(node, nullptr);
    }
    else if (!node->left)
    {
        replacement = node->right;
        transplant(node, node->right);
    }
    else if (!node->right)
    {
        replacement = node->left;
        transplant(node, node->left);
    }
    else
    {
        target = min(node->right);
        targetOriginalColor = target->color;
        replacement = target->right;

        if (target->parent == node)
        {
            if (replacement) replacement->parent = target;
        }
        else
        {
            transplant(target, target->right);
            target->right = node->right;
            if (target->right) target->right->parent = target;
        }

        transplant(node, target);
        target->left = node->left;
        if (target->left) target->left->parent = target;
        target->color = node->color;
    }
    delete node;

    if (!targetOriginalColor) balanceErase(replacement);
    size_--;
}

void Set::balanceErase(Node* node)
{
    if (!node) node = root_;
    while (node != root_ && (!node || node->color == false))
    {
        if (node == node->parent->left)
        {
            Node* brother = node->parent->right;

            if (!brother)
            {
                node = node->parent;
                continue;
            }

            if (brother && brother->color == true)
            {
                brother->color = false;
                node->parent->color = true;
                rotateLeft(node->parent);
                brother = node->parent->right;
            }
            if ((!brother->left || brother->left->color == false) &&
                (!brother->right || brother->right->color == false))
            {
                brother->color = true;
                node = node->parent;
            }
            else
            {
                if (!brother->right || brother->right->color == false)
                {
                    if (brother->left) brother->left->color = false;
                    brother->color = true;
                    rotateRight(brother);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = false;
                if (brother->right) brother->right->color = false;
                rotateLeft(node->parent);
                node = root_;
            }
        }
        else
        {
            Node* brother = node->parent->left;

            if (!brother)
            {
                node = node->parent;
                continue;
            }

            if (brother && brother->color == true)
            {
                brother->color = false;
                node->parent->color = true;
                rotateRight(node->parent);
                brother = node->parent->left;
            }
            if ((!brother->left || brother->left->color == false) &&
                (!brother->right || brother->right->color == false))
            {
                brother->color = true;
                node = node->parent;
            }
            else
            {
                if (!brother->left || brother->left->color == false)
                {
                    if (brother->right) brother->right->color = false;
                    brother->color = true;
                    rotateLeft(brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = false;
                if (brother->left) brother->left->color = false;
                rotateRight(node->parent);
                node = root_;
            }
        }
    }
    if (node) node->color = false;
}

void Set::rotateLeft(Node* x)
{
    if (!x || !x->right) return;

    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root_ = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void Set::rotateRight(Node* x)
{
    if (!x || !x->left) return;

    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root_ = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

Set::Node* Set::iterator::min(Node* node)
{
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

Set::Node* Set::min(Node* node)
{
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

void Set::transplant(Node* u, Node* v)
{
    if (u->parent == nullptr)
        root_ = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr) v->parent = u->parent;
}

Set::iterator::iterator(Node* current_) : current(current_) {}

const int& Set::iterator::operator*() { return current->value; };

Set::iterator Set::begin() { return iterator(min(this->root_)); }

Set::iterator Set::end() { return iterator(nullptr); }

Set::iterator Set::find(int element)
{
    Node* tmp = this->root_;
    while (tmp)
    {
        if (element > tmp->value)
            tmp = tmp->right;
        else if (element < tmp->value)
            tmp = tmp->left;
        else
            return iterator(tmp);
    }
    return end();
}

bool Set::iterator::operator==(const Set::iterator& right) { return current == right.current; }

bool Set::iterator::operator!=(const Set::iterator& right) { return current != right.current; }

Set::iterator& Set::iterator::operator++()
{
    if (this->current == nullptr) return *this;
    if (current->right)
    {
        current = min(current->right);
    }
    else
    {
        Node* parentNode = current->parent;
        while (parentNode != nullptr && current == parentNode->right)
        {
            current = parentNode;
            parentNode = parentNode->parent;
        }
        current = parentNode;
    }

    return *this;
}
Set::iterator Set::iterator::operator++(int)
{
    if (this->current == nullptr) return *this;
    Set::iterator tmp = *this;
    if (current->right)
    {
        current = min(current->right);
    }
    else
    {
        Node* parentNode = current->parent;
        while (parentNode != nullptr && current == parentNode->right)
        {
            current = parentNode;
            parentNode = parentNode->parent;
        }
        current = parentNode;
    }

    return tmp;
}

Set::Node* Set::iterator::getCurrent() { return current; }

void Set::erase(Set::iterator it)
{
    if (it != end()) erase(it.getCurrent()->value);
}

Set::iterator Set::lower_bound(int value)
{
    Node* current = root_;
    Node* result = nullptr;

    while (current != nullptr)
    {
        if (current->value >= value)
        {
            result = current;
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return iterator(result);
}

Set::iterator Set::upper_bound(int value)
{
    Node* current = root_;
    Node* result = nullptr;

    while (current != nullptr)
    {
        if (current->value > value)
        {
            result = current;
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return iterator(result);
}
