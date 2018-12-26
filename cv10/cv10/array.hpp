#ifndef ARRAY_HPP_INCLUDED
#define ARRAY_HPP_INCLUDED

#include <cstddef>
#include <memory>
#include <iostream>

using std::size_t;
template<typename D>
void copy_array(const D* from, const D* to, size_t size) {
    for (size_t i = 0; i < size; ++i) to[i] = from[i];
}

template<typename D>
void print_array(D arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}
template<typename D>
void resize_array(std::unique_ptr<D[]>& arr, size_t oldSize, size_t newSize) {
    auto newArr = std::make_unique<D[]>(newSize);
    size_t minSize = (oldSize < newSize) ? oldSize : newSize;
    copy_array(arr.get(), newArr.get(), minSize);
    newArr.swap(arr);
}


#endif
