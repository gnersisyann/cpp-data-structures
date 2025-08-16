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
    ~Vector() noexcept;

    void clear();
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    T& at(size_t index);
    const T& at(size_t index) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T* data();
	const T* data() const noexcept;

    Vector& push_back(const T& value);
    void pop_back();

    void reserve(size_t capacity);
    void shrink_to_fit();

    void swap(Vector& other) noexcept;

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

template <typename T>
Vector<T>::Vector() : capacity_(1), size_(0), array_(allocate(capacity_))
{
}

template <typename T>
Vector<T>::Vector(size_t size, const T& value)
    : capacity_(geq_power_of_two(size)), size_(size), array_(allocate(capacity_))
{
    for (size_t i = 0; i < size; i++)
    {
        array_[i] = value;
    }
}

template <typename T>
T* Vector<T>::allocate(size_t size)
{
    return reinterpret_cast<T*>(new char[sizeof(T) * size]);
}

template <typename T>
size_t Vector<T>::size() const noexcept
{
    return size_;
}

template <typename T>
size_t Vector<T>::capacity() const noexcept
{
    return capacity_;
}

template <typename T>
void Vector<T>::init_default(size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        new (array_ + i) T();
    }
}

template <typename T>
void Vector<T>::delete_array(size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        array_[i].~T();
    }
}

template <typename T>
void Vector<T>::clear()
{
    delete_array(0, size_);
    size_ = 0;
}

template <typename T>
Vector<T>::~Vector() noexcept
{
    clear();
    delete[] reinterpret_cast<char*>(array_);
}

template <typename T>
size_t Vector<T>::geq_power_of_two(size_t size)
{
    size_t cap = 1;
    while (cap < size) cap *= 2;
    return cap;
}

template <typename T>
Vector<T>::Vector(size_t size) : capacity_(geq_power_of_two(size)), size_(size), array_(allocate(capacity_))
{
    init_default(0, size_);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) : capacity_(other.capacity_), size_(other.size_), array_(allocate(capacity_))
{
    for (size_t i = 0; i < size_; i++)
    {
        array_[i] = other.array_[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : capacity_(other.capacity_), size_(other.size_), array_(other.array_)
{
    other.array_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) 
{
    size_ = init.size();
    capacity_ = geq_power_of_two(size_);
    array_ = allocate(capacity_);
    size_t i = 0;
    for (auto it = init.begin(); it != init.end(); it++) {
        new (array_ + i) T(*it);
        i++;
    }
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return array_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return array_[index];
}

template <typename T>
Vector<T>& Vector<T>::push_back(const T& value)
{
    if (size_ == capacity_)
    {
        size_t new_capacity = geq_power_of_two(size_ + 1);
        T* new_array = allocate(new_capacity);
        for (size_t i = 0; i < size_; i++)
        {
            new (new_array + i) T(std::move(array_[i]));
            array_[i].~T();
        }
        delete reinterpret_cast<char*>(array_);
        array_ = new_array;
        capacity_ = new_capacity;
    }
    new (array_ + size_) T(value);
    size_++;
    return *this;
}

template <typename T>
void Vector<T>::pop_back() 
{
    if (empty()) throw std::runtime_error("Vector is empty");
    array_[size_ - 1].~T();
    --size_;
}

template <typename T>
bool Vector<T>::empty() const noexcept
{
    return size_ == 0;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const
{
    if (size_ != other.size_) return false;
    for (size_t i = 0; i < size_; ++i)
    {
        if (array_[i] != other.array_[i]) return false;
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const
{
    return !(*this == other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        clear();
        delete[] reinterpret_cast<char*>(array_);

        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = allocate(capacity_);
        for (size_t i = 0; i < size_; ++i)
        {
    		new (array_ + i) T(other.array_[i]);
        }
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != &other)
    {
        clear();
        delete[] reinterpret_cast<char*>(array_);

        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = other.array_;

        other.array_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
T& Vector<T>::front()
{
	if (empty()) throw std::runtime_error("Vector is empty");
    return array_[0];
}

template <typename T>
const T& Vector<T>::front() const
{
	if (empty()) throw std::runtime_error("Vector is empty");
    return array_[0];
}

template <typename T>
T& Vector<T>::back()
{
	if (empty()) throw std::runtime_error("Vector is empty");
    return array_[size_ - 1];
}

template <typename T>
const T& Vector<T>::back() const
{
	if (empty()) throw std::runtime_error("Vector is empty");
    return array_[size_ - 1];
}

template <typename T>
T& Vector<T>::at(size_t index)
{
    if (index >= size_) throw std::out_of_range("Index out of range");
    return array_[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const
{
    if (index >= size_) throw std::out_of_range("Index out of range");
    return array_[index];
}

template <typename T>
T* Vector<T>::data()
{
    return array_;
}
template <typename T>

const T* Vector<T>::data() const noexcept 
{ 
	return array_; 
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) return;
    
    T* new_array = allocate(new_capacity);
    for (size_t i = 0; i < size_; i++) {
        new (new_array + i) T(std::move(array_[i]));
        array_[i].~T();
    }
    delete[] reinterpret_cast<char*>(array_);
    array_ = new_array;
    capacity_ = new_capacity;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ == size_) return;
    
    T* new_array = allocate(size_);
    for (size_t i = 0; i < size_; i++) {
        new (new_array + i) T(std::move(array_[i]));
        array_[i].~T();
    }
    delete[] reinterpret_cast<char*>(array_);
    array_ = new_array;
    capacity_ = size_;
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) noexcept
{
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
}

template <typename T>
template <typename... Args>
T& Vector<T>::emplace_back(Args&&... args)
{
    if (size_ == capacity_)
    {
        size_t newCapacity = geq_power_of_two(size_ + 1);
        T* new_array = allocate(newCapacity);

        for (size_t i = 0; i < size_; i++)
        {
            new (new_array + i) T(std::move(array_[i]));
            array_[i].~T();
        }

        delete[] reinterpret_cast<char*>(array_);

        array_ = new_array;
        capacity_ = newCapacity;
    }
    new (array_ + size_) T(std::forward<Args>(args)...);
    size_++;

    return array_[size_ - 1];
}