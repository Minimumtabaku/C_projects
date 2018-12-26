#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#include "array.hpp"
#include <cstddef>
#include <memory>
#include <iterator>
#include <iostream>


template <typename T>
class vector {
public:
    vector();
    
    vector(const vector& rhs);
    vector& operator=(const vector& rhs);
    
    void reserve(size_t cap);
    void push_back(const T& val);
    
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    void clear();
    void swap(vector& rhs);
    
    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    
    using iterator = T*;
    using const_iterator = const T*;
    
    iterator begin() { return iterator(m_data.get()); }
    iterator end() { return iterator(m_data.get() + m_size); }
    
private:
    std::unique_ptr<T[]> m_data;
    size_t m_capacity;
    size_t m_size;
};

template <typename T>
vector<T>::vector() :
m_data(nullptr),
m_capacity(0),
m_size(0) {}

template <typename T>
vector<T>::vector(const vector& rhs) :
m_data(std::make_unique<T[]>(rhs.m_size)),
m_capacity(rhs.m_capacity),
m_size(rhs.m_size) {
    copy_array(rhs.m_data.get(), m_data.get(), m_size);
}


template <typename T>
vector<T>& vector<T>::operator=(const vector& rhs) {
    vector temp(rhs);
    swap(temp);
    return *this;
}

template <typename T>
void vector<T>::reserve(size_t cap) {
    if (m_capacity < cap) {
        resize_array(m_data, m_size, cap);
        m_capacity = cap;
    }
}

template <typename T>
void vector<T>::push_back(const T& val) {
    if (m_size == m_capacity) {
        reserve((m_capacity + 1) * 2);
    }
    
    m_data[m_size] = val;
    m_size++;
}

template <typename T>
void vector<T>::pop_back() {
    m_size--;
}

template <typename T>
size_t vector<T>::size() const {
    return m_size;
}

template <typename T>
size_t vector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
void vector<T>::clear() {
    m_size = 0;
}

template <typename T>
T& vector<T>::operator[](size_t i) {
    return m_data[i];
}

template <typename T>
const T& vector<T>::operator[](size_t i) const {
    return m_data[i];
}

template <typename T>
void vector<T>::swap(vector& rhs) {
    std::swap(m_data, rhs.m_data);
    std::swap(m_capacity, rhs.m_capacity);
    std::swap(m_size, rhs.m_size);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& v) {
    out << '(';
    if (v.size() != 0) {
        out << v[0];
    }
    for (size_t i = 1; i < v.size(); i++) {
        out << ", " << v[i];
    }
    return out << ')';
}

#endif
