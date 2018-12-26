#include "array.hpp"
#include <iostream>

void copy_array(const double* from, double* to, size_t size) {
    for (size_t i = 0; i < size; ++i) to[i] = from[i];
}

void print_array(const double* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

void resize_array(std::unique_ptr<double[]>& arr, size_t oldSize, size_t newSize) {
    auto newArr = std::make_unique<double[]>(newSize);
    size_t minSize = (oldSize < newSize) ? oldSize : newSize;
    copy_array(arr.get(), newArr.get(), minSize);
    newArr.swap(arr);
}
