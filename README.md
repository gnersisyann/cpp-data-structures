## C++ Data Structures Implementation

A collection of custom implementations of fundamental data structures in C++, designed for educational purposes and demonstrating advanced C++ programming concepts.

### Project Structure

```
.
├── main.cpp              # Entry point (currently empty)
├── Makefile             # Build configuration
├── include/             # Header files
│   ├── ForwardList.h    # Singly-linked list implementation
│   ├── Heap.h           # Heap algorithms (make_heap, push_heap, etc.)
│   ├── List.h           # Doubly-linked list implementation
│   ├── RationalNumber.h # Template class for rational numbers
│   ├── Set.h            # Red-black tree based set
│   └── Vector.h         # Dynamic array implementation
└── src/
    └── Set.cpp          # Set implementation
```

### Implemented Data Structures

#### Vector
A dynamic array with automatic memory management featuring:
- Dynamic resizing with power-of-two capacity growth
- Move semantics support
- Exception-safe operations
- Standard container interface (push_back, pop_back, at, etc.)

#### List
A doubly-linked list with comprehensive iterator support:
- Bidirectional iterators
- Const iterators and reverse iterators
- Standard container operations
- Merge and sort functionality

#### ForwardList
A singly-linked list implementation:
- Forward iterators
- Memory-efficient single-direction linking
- Standard forward list operations

#### Set
A Red-Black tree based associative container:
- Self-balancing binary search tree
- O(log n) insertion, deletion, and search
- STL-compatible iterator interface
- Range queries (lower_bound, upper_bound)

#### Heap
Template-based heap algorithms:
- make_heap, push_heap, pop_heap operations
- Customizable comparison functions
- Works with any random access iterator

#### RationalNumber
A template class for representing rational numbers:
- Automatic simplification using GCD
- Arithmetic operations (+, -, *, /)
- Proper sign handling
- Generic type support

### Building the Project

```bash
# Compile the project
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Rebuild everything
make re
```

### Usage Examples

```cpp
#include "include/Vector.h"
#include "include/Set.h"
#include "include/RationalNumber.h"

// Vector usage
Vector<int> vec = {1, 2, 3, 4, 5};
vec.push_back(6);

// Set usage
Set mySet = {3, 1, 4, 1, 5, 9}; // Duplicates automatically handled
mySet.insert(2);

// RationalNumber usage
yourname::RationalNumber<int> r1(1, 2);  // 1/2
yourname::RationalNumber<int> r2(1, 3);  // 1/3
auto result = r1 + r2;  // 5/6
```

### Key Features

- **Template-based**: Most containers support generic types
- **STL-compatible**: Standard iterator interfaces and container methods
- **Memory-safe**: Proper RAII and exception safety
- **Performance-oriented**: Efficient algorithms and data structures

### Code Quality Issues to Address

1. **Inconsistent naming**: Mix of camelCase and snake_case (e.g., `size_` vs `getSize()`)
2. **Missing const correctness**: Some methods that should be const are not marked as such
3. **Iterator implementation**: Some iterator operators could be more robust
4. **Exception safety**: Some operations may not be fully exception-safe
5. **Documentation**: Missing inline documentation for complex algorithms
6. **Namespace usage**: RationalNumber uses `yourname` namespace, others don't use namespaces
7. **Header guards**: Some headers use `#pragma once`, consistency would be better

### Future Improvements

- Add unit tests for all data structures
- Implement move constructors and assignment operators where missing
- Add allocator support for containers
- Improve const correctness throughout the codebase
- Add comprehensive documentation
- Consider adding more STL-compatible features

### Requirements

- C++17 or later
- GCC compiler (configured in Makefile)

This project demonstrates advanced C++ concepts including template metaprogramming, RAII, iterator design patterns, and complex data structure algorithms.
