#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void siftDown(It begin, It end, It i, Compare compare = Compare())
{
    while (true)
    {
        It largest = i;
        It left = begin + (std::distance(begin, i) * 2 + 1);
        It right = begin + (std::distance(begin, i) * 2 + 2);

        if (left < end && compare(*largest, *left)) largest = left;

        if (right < end && compare(*largest, *right)) largest = right;

        if (largest != i)
        {
            std::iter_swap(i, largest);
            i = largest;
        }
        else
        {
            break;
        }
    }
}

template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void siftUp(It begin, It i, Compare compare = Compare())
{
    while (i > begin)
    {
        It parent = begin + (std::distance(begin, i) - 1) / 2;
        if (compare(*parent, *i))
        {
            std::iter_swap(i, parent);
            i = parent;
        }
        else
        {
            break;
        }
    }
}

template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void makeHeap(It begin, It end, Compare compare = Compare())
{
    if (begin == end) return;
    auto n = std::distance(begin, end);
    if (n <= 1) return;
	for (auto i = begin + (n / 2 - 1); i >= begin; --i)
    {
        siftDown(begin, end, i, compare);
    }
}

template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void popHeap(It begin, It end, Compare compare = Compare())
{
    if (begin == end || std::distance(begin, end) == 1) return;
    std::iter_swap(begin, end - 1);
    siftDown(begin, end - 1, begin, compare);
}

template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void pushHeap(It begin, It end, Compare compare = Compare())
{
    if (begin == end || std::distance(begin, end) == 1) return;
    siftUp(begin, end - 1, compare);
}