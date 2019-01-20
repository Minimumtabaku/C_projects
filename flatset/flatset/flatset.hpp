#pragma once

#include <iterator>
#include <functional>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T, typename Comparator = std::less<T>>
class flat_set {
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using size_type = std::size_t;
    using value_type = T;
    
    // Special member functions
    
    flat_set() : m_comp(Comparator()) {};
    
    flat_set(Comparator const &cmp) {
        m_comp = cmp;
    }
    
    flat_set(flat_set const &rhs) {
        m_data = rhs.m_data;
        m_comp = rhs.m_comp;
    }
    
    flat_set(flat_set &&rhs) : m_data(rhs.m_data), m_comp(rhs.m_comp) {
    }
    
    flat_set &operator=(flat_set const &rhs) {
        m_data = std::vector<T>(rhs.m_data);
        return *this;
    };
    
    flat_set &operator=(flat_set &&rhs) {
        m_data = std::move(rhs.m_data);
        return *this;
    };
    
    ~flat_set() = default;
    // Constructs flat_set from elements in range [first, last)
    
    template<typename InputIterator>
    flat_set(InputIterator first, InputIterator last) {
        insert(first,last);
    };
    
    template<typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const &cmp){
         m_comp = cmp;
        insert(first,last);
    }
    
    std::pair<iterator, bool> insert(T const &v) {
        iterator lowerBound = flat_set::lower_bound(v);
        if (lowerBound == end()) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, v), true);
        } else if (lowerBound != end() && m_comp(v,*lowerBound)) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, v), true);
        }else{
            return std::pair<iterator, bool>(lowerBound, false);
        }
    };
    
    std::pair<iterator, bool> insert(T &&v) {
        iterator lowerBound = flat_set::lower_bound(v);
        if (lowerBound == end()) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, v), true);
        } else if (lowerBound != end() && m_comp(v,*lowerBound)) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, v), true);
        }else{
            return std::pair<iterator, bool>(lowerBound, false);
        }
    };
    
    
    //     Inserts [first, last) range of elements
    
    template<typename Iterator>
    void insert(Iterator first, Iterator last) {
//        reserve(size() + std::distance(first,last));
        while(first != last){
            insert(*first);
            first++;
        }
    };
    
        template<typename InputIterator>
        void insert(InputIterator first, InputIterator last, std::input_iterator_tag) {
            while (first != last) {
                insert(*first);
                first++;
            }
        };
    
        template<typename OutputIterator>
        void insert(OutputIterator first, OutputIterator last, std::output_iterator_tag) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }
    
        template<typename RandomAccessIterator>
        void insert(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }
    
        template<typename ForwardIterator>
        void insert(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }
    
        template<typename BidirectionalIterator>
        void insert(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }
    
    
    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    
    iterator erase(const_iterator i) {
        auto ret = flat_set::find(*i);
        m_data.erase(i);
        return ret;
    };
    
    // Deletes elements in range [first, last), returns iterator to the next element
    
    iterator erase(const_iterator first, const_iterator last) {
        return m_data.erase(first, last);
    };
    
    // Deletes element equal to key if it is present, returns how many elements were deleted
    
    size_type erase(value_type const &key) {
        if (find(key) == end()) {
            return 0;
        } else {
            erase(find(key));
            return 1;
        }
    };
    
    
    // Iterator member functions
    
    iterator begin() noexcept {
        return m_data.begin();
    };
    
    iterator end() noexcept {
        return m_data.end();
    };
    
    const_iterator begin() const noexcept {
        return m_data.cbegin();
    };
    
    const_iterator end() const noexcept {
        return m_data.cend();
    };
    
    const_iterator cbegin() const noexcept {
        return m_data.cbegin();
    };
    
    const_iterator cend() const noexcept {
        return m_data.cend();
    };
    
    
    // The usual queries
    
    bool empty() const {
        return m_data.empty();
    };
    
    size_type size() const {
        return m_data.size();
    };
    
    size_type capacity() const {
        return m_data.capacity();
    };
    
    void reserve(size_type c) {
        m_data.reserve(c);
    };
    
    void clear() {
        m_data.clear();
    };
    
    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    
    iterator find(T const &v) {
        auto cmp = [&v, this](T const& f) {
            return !m_comp(v, f) && !m_comp(f, v);
        };
        
        return std::find_if(begin(), end(), cmp);
        
    };
    
    const_iterator find(T const &v) const {
        auto it = std::find(m_data.begin(), m_data.end(), v);
        
        if (it != end()) {
            //return ilerator pointing to the index of equal or smaller element
            return it;
        } else {
            return end();
        }
    };
    
    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    
    iterator lower_bound(T const &t) {
      
        return std::lower_bound(begin(), end(), t, m_comp);;
    };
    
    const_iterator lower_bound(T const &t) const {
        return std::lower_bound(begin(), end(), t, m_comp);
    };
    
    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    
    iterator upper_bound(T const &t) {
        return std::upper_bound(begin(), end(), t, m_comp);
    };
    
    const_iterator upper_bound(T const &t) const {
        return upper_bound(t);
    };
    
    void swap(flat_set &rhs) {
        std::swap(*this,rhs);
    };
    
    // Lexicographical comparisons
    
    bool operator==(flat_set const &rhs) const &{
        return m_data == rhs.m_data;
    };
    
    bool operator!=(flat_set const &rhs) const &{
        return m_data != rhs.m_data;
    };
    
    bool operator<(flat_set const &rhs) const &{
        return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), m_comp);
    };
    
    bool operator<=(flat_set const &rhs) const &{
        return (*this < rhs) || (*this == rhs);
    };
    
    bool operator>=(flat_set const &rhs) const &{
        return !(*this < rhs);
    };
    
    bool operator>(flat_set const &rhs) const &{
        return (*this >= rhs) && (*this != rhs);
    };
private:
    std::vector<T> m_data;
    Comparator m_comp;
};

template<typename T>
void swap(flat_set<T> const &lhs, flat_set<T> const &rhs) {
    lhs.swap(rhs);
}


