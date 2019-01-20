#pragma once

#include <cstdlib>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T, typename Comparator = std::less<T>>
class flat_set {
private:
    std::vector<T> m_data;
    Comparator m_comp;
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using size_type = std::size_t;
    using value_type = T;
    
    // Speciální member funkce se chovají běžným stylem
    flat_set() : m_comp(Comparator()){};
    flat_set(Comparator const& cmp){
        m_comp = cmp;
    }
    flat_set(flat_set const& rhs){
        m_data = rhs.m_data;
        m_comp = rhs.m_comp;
    }
    flat_set(flat_set && rhs) : m_data(rhs.m_data),m_comp(rhs.m_comp){
    }
    flat_set& operator=(flat_set const& rhs);
    flat_set& operator=(flat_set && rhs);
    ~flat_set() = default;
    
    // Konstruktory co vytvoří flat_set z prvků definovaných jako
    // [first, last). Alokují pouze jednou pokud je to možné.
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last);
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp);
    
    
    // Vloží prvek do setu, buďto pomocí kopie, nebo pomocí přesunu.
    std::pair<iterator, bool> insert(T const& v){
        iterator lowerBound = flat_set::lower_bound(v);
        if (lowerBound == end() && !m_comp(*lowerBound,v)) {
            return std::pair<iterator, bool>(end(),false);
        }else{
            //TODO: probably something different from lowerBound
            return std::pair<iterator,bool>(m_data.insert(lowerBound, v),true);
        }
    }
    std::pair<iterator, bool> insert(T&& v){
        iterator lowerBound = flat_set::lower_bound(v);
        if (lowerBound == end() && !m_comp(*lowerBound,v)) {
            return std::pair<iterator, bool>(end(),false);
        }else{
            return std::pair<iterator,bool>(m_data.insert(lowerBound, v),true);
        }
    }
    // Vloží prvky z [first, last), alokuje pouze jednou pokud je to možné
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last){
        
    }
    
    // Smaže prvek na který ukazuje i, vrátí iterátor k dalšímu prvku
    iterator erase(const_iterator i){
        auto ret = flat_set::find(*i);
        m_data.erase(i);
        return ret;
    }
    // Smaže všechny prvky z [from, to), vrátí iterátor k dalšímu prvku
    iterator erase(const_iterator from, const_iterator to){
        return m_data.erase(from, to);
    }
    // Iterátory předané dovnitř erase odkazují dovnitř setu.
    
    // Smaže prvek rovný klíči pokud existuje.
    // Vrátí kolik prvků bylo smazáno
    size_type erase(value_type const& key){
        auto it = find(key);
        if (it != end()) {
            m_data.erase(it);
            return 1;
        }else{
            return 0;
        }
    }
    
    // Běžné funkce k vytvoření iterátorů
    iterator begin() noexcept{
        iterator it = m_data.begin();
        return it;
    }
    iterator end() noexcept{
        iterator it = m_data.end();
        return it;
    }
    const_iterator begin() const noexcept{
        const_iterator cit = m_data.begin();
        return cit;
    }
    const_iterator end() const noexcept{
        const_iterator cit = m_data.end();
        return cit;
    }
    const_iterator cbegin() const noexcept{
        const_iterator cit = m_data.cbegin();
        return cit;
    }
    const_iterator cend() const noexcept{
        const_iterator cit = m_data.cend();
        return cit;
    }
    
    bool empty() const{
        return m_data.empty();
    }
    size_type size() const{
        return m_data.size();
    }
    size_type capacity() const{
        return m_data.capacity();
    }
    
    // Zajistí, aby se do instance flat_setu dalo vložit c prvků
    // aniž by byla potřeba realokace
    void reserve(size_type c){
        m_data.reserve(c);
    }
    
    // Vymaže všechny prvky ze setu
    void clear(){
        m_data.clear();
    }
    
    // Vrátí iterátor ukazující na prvek ekvivalentní s v, nebo end(),
    // pokud takový prvek není uvnitř setu
     iterator find(T const& v){
        //using binary search algorithm
        auto it = flat_set::lower_bound(v);
        
        if(it != end()){
            //return iterator pointing to the index of equal or smaller element
            return it;
        }else{
            return end();
        }
    }
    
    const_iterator find(T const& v) const{
        auto it = flat_set::lower_bound(v);
        
        if(it != end()){
            //return ilerator pointing to the index of equal or smaller element
        }else{
            return end();
        }
    }
    
    // Vrátí iterátor k prvnímu prvku, který není menší nežli t,
    // nebo end() pokud takový prvek neexistuje.
    iterator lower_bound(T const& t){
        return std::lower_bound(begin(), end(), t);
    }
    const_iterator lower_bound(T const& t) const{
        return std::lower_bound(begin(), end(), t);
    }
    
    // Vrátí iterátor k prvnímu prvku, který je větší nežli t,
    // nebo end() pokud takový prvek neexistuje.
    iterator upper_bound(T const& t){
        return std::upper_bound(begin(), end(), t);
    }
    const_iterator upper_bound(T const& t) const{
        return std::upper_bound(begin(), end(), t);
    }
    
    // Prohodí obsah dvou setů (včetně komparátoru)
    void swap(flat_set& o);
    
};
// porovnání probíhá lexikograficky
template <typename T>
bool operator==(flat_set<T> const& a, flat_set<T> const& b);
template <typename T>
bool operator!=(flat_set<T> const& a, flat_set<T> const& b);
template <typename T>
bool operator< (flat_set<T> const& a, flat_set<T> const& b);
template <typename T>
bool operator<=(flat_set<T> const& a, flat_set<T> const& b);
template <typename T>
bool operator>=(flat_set<T> const& a, flat_set<T> const& b);
template <typename T>
bool operator> (flat_set<T> const& a, flat_set<T> const& b);

// Prohodí obsah dvou setů (včetně komparátoru)
template <typename T>
void swap(flat_set<T> const& a, flat_set<T> const& b);
