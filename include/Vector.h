#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>


template <typename T>
class Vector
{
   public:
    Vector();
    explicit Vector(size_t size);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(size_t size, const T& value);
    Vector(std::initializer_list<T> init);
    ~Vector();

    void clear();
    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    T& at(size_t index);
    const T& at(size_t index) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T* data();

    Vector& push_back(const T& value);
    void pop_back();

    void reserve(size_t capacity);
    void shrink_to_fit();

    void swap(Vector& other);

    template <typename... Args>
    T& emplace_back(Args&&... args);

   public:
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

   private:
    T* allocate(size_t start);

    // init with default constructor
    void init_default(size_t start, size_t end);

    // free allocated memory
    void delete_array(size_t start, size_t end);

    size_t geq_power_of_two(size_t n);

   private:
    size_t capacity_;
    size_t size_;
    T* array_;
};