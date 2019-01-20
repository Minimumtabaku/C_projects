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

    // Speciální member funkce se chovají běžným stylem

    flat_set() : m_comp(Comparator()) {};

    flat_set(Comparator const &cmp) {
        m_comp = cmp;
    }

    flat_set(flat_set const &rhs) {
        m_data = std::vector<T>(rhs.m_data);
        m_comp = rhs.m_comp;
    }

    flat_set(flat_set &&rhs) {
        m_data = std::move(rhs.m_data);
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

    // Konstruktory co vytvoří flat_set z prvků definovaných jako
    // [first, last). Alokují pouze jednou pokud je to možné.
    template<typename InputIterator>
    flat_set(InputIterator first, InputIterator last) {
        insert(first, last);
    };

    // Vloží prvek do setu, buďto pomocí kopie, nebo pomocí přesunu.
    template<typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const &cmp) {
        m_comp = cmp;
        insert(first, last);
    }

    std::pair<iterator, bool> insert(T const &v) {
        iterator lowerBound = flat_set::lower_bound(v);
        if (lowerBound == end()) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, v), true);
        } else if (lowerBound != end() && m_comp(v, *lowerBound)) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, v), true);
        } else {
            return std::pair<iterator, bool>(lowerBound, false);
        }
    };

    std::pair<iterator, bool> insert(T &&v) {
        iterator lowerBound = flat_set::lower_bound(v);
        if (lowerBound == end()) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, std::move(v)), true);
        } else if (lowerBound != end() && m_comp(v, *lowerBound)) {
            return std::pair<iterator, bool>(m_data.insert(lowerBound, std::move(v)), true);
        } else {
            return std::pair<iterator, bool>(lowerBound, false);
        }
    };


    //     Inserts [first, last) range of elements

    template<typename Iterator>
    void insert(Iterator first, Iterator last) {
        reserve(size() + std::distance(first,last));
        while (first != last) {
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


    // Smaže prvek na který ukazuje i, vrátí iterátor k dalšímu prvku
    iterator erase(const_iterator i) {
        auto ret = flat_set::find(*i);
        m_data.erase(i);
        return ret;
    };

    // Smaže všechny prvky z [from, to), vrátí iterátor k dalšímu prvku
    iterator erase(const_iterator first, const_iterator last) {
        return m_data.erase(first, last);
    };

    // Smaže prvek rovný klíči pokud existuje.
    // Vrátí kolik prvků bylo smazáno
    size_type erase(value_type const &key) {
        if (find(key) == end()) {
            return 0;
        } else {
            erase(find(key));
            return 1;
        }
    };

    // Běžné funkce k vytvoření iterátorů

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


    bool empty() const {
        return m_data.empty();
    };

    size_type size() const {
        return m_data.size();
    };

    size_type capacity() const {
        return m_data.capacity();
    };

    // Zajistí, aby se do instance flat_setu dalo vložit c prvků
    // aniž by byla potřeba realokace
    void reserve(size_type c) {
        m_data.reserve(c);
    };

    // Vymaže všechny prvky ze setu
    void clear() {
        m_data.clear();
    };

    // Vrátí iterátor ukazující na prvek ekvivalentní s v, nebo end(),
    // pokud takový prvek není uvnitř setu

    iterator find(T const &v) {
        auto cmp = [&v, this](T const &f) {
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

    // Vrátí iterátor k prvnímu prvku, který není menší nežli t,nebo end() pokud takový prvek neexistuje.

    iterator lower_bound(T const &t) {

        return std::lower_bound(begin(), end(), t, m_comp);;
    };

    const_iterator lower_bound(T const &t) const {
        return std::lower_bound(begin(), end(), t, m_comp);
    };

    // Vrátí iterátor k prvnímu prvku, který je větší nežli t, nebo end() pokud takový prvek neexistuje.

    iterator upper_bound(T const &t) {
        return std::upper_bound(begin(), end(), t, m_comp);
    };

    const_iterator upper_bound(T const &t) const {
        return upper_bound(t);
    };
    // Prohodí obsah dvou setů (včetně komparátoru)
    void swap(flat_set &rhs) {
        auto tmp_data = m_data;
        auto tmp_comp = m_comp;
        m_data = rhs.m_data;
        m_comp = rhs.m_comp;
        rhs.m_comp = tmp_comp;
        rhs.m_data = tmp_data;
    };

    // porovnání probíhá lexikograficky

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

// Prohodí obsah dvou setů (včetně komparátoru)
template<typename T>
void swap(flat_set<T> const &lhs, flat_set<T> const &rhs) {
    lhs.swap(rhs);
}


