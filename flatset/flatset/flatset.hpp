
#include <iostream>
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
        std::cout << "asda" << std::endl;
    }
    std::pair<iterator, bool> insert(T&& v);
    // Vloží prvky z [first, last), alokuje pouze jednou pokud je to možné
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last){
        
    }
    
    // Smaže prvek na který ukazuje i, vrátí iterátor k dalšímu prvku
    iterator erase(const_iterator i);
    // Smaže všechny prvky z [from, to), vrátí iterátor k dalšímu prvku
    iterator erase(const_iterator from, const_iterator to);
    // Iterátory předané dovnitř erase odkazují dovnitř setu.
    
    // Smaže prvek rovný klíči pokud existuje.
    // Vrátí kolik prvků bylo smazáno
    size_type erase(value_type const& key);
    
    // Běžné funkce k vytvoření iterátorů
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    
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
    void reserve(size_type c);
    
    // Vymaže všechny prvky ze setu
    void clear();
    
    // Vrátí iterátor ukazující na prvek ekvivalentní s v, nebo end(),
    // pokud takový prvek není uvnitř setu
    iterator find(T const& v);
    const_iterator find(T const& v) const;
    
    // Vrátí iterátor k prvnímu prvku, který není menší nežli t,
    // nebo end() pokud takový prvek neexistuje.
    iterator lower_bound(T const& t){
        typename std::vector<T>::iterator it = m_data.begin();
        while (it != m_data.end()) {
            if(*it == t){
                return it;
            }
        }
        return m_data.end();
    }
    const_iterator lower_bound(T const& t) const{
        typename std::vector<T>::const_iterator it = m_data.cbegin();
        while (it != m_data.cend()) {
            if(*it == t){
                return it;
            }
        }
        return m_data.cend();
    }
    
    // Vrátí iterátor k prvnímu prvku, který je větší nežli t,
    // nebo end() pokud takový prvek neexistuje.
    iterator upper_bound(T const& t);
    const_iterator upper_bound(T const& t) const;
    
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
