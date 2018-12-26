#include "list.hpp"

#include <utility>
#include <algorithm>
#include <iostream>

namespace pjc {
    
    ///const_iterator constructor
    list::const_iterator::const_iterator(node* ptr, const list* gen){
        current_ptr = ptr;
        o_list = gen;
    }
    ///const_ begin and such
    list::const_iterator list::begin() const{
        return list::const_iterator(head, this);
    }
    list::const_iterator list::end() const{
        return list::const_iterator(nullptr, this);
    }
    
    list::const_iterator list::cbegin() const{
        return list::const_iterator(head, this);
    }
    
    list::const_iterator list::cend() const{
       return list::const_iterator(nullptr, this);
    }
    ///const_iterator operators
    list::const_iterator& list::const_iterator::operator++(){ //prefix
        if (current_ptr->next != nullptr) {
            current_ptr = current_ptr->next;
        }else{
            ///TODO: CHECK IF ITS OK
            current_ptr = nullptr;
        }
        return *this;
    }
    list::const_iterator& list::const_iterator::operator--(){
        if (current_ptr != nullptr) {
            current_ptr = current_ptr->prev;
        }else{
            ///TODO: CHECK IF ITS OK
            current_ptr = o_list->tail;
        }
        return *this;
    }
    list::const_iterator list::const_iterator::operator++(int num){
        list::const_iterator cinterator = list::const_iterator(current_ptr, o_list);
        current_ptr = current_ptr->next;
        return cinterator;
    }
    list::const_iterator list::const_iterator::operator--(int num){
        list::const_iterator cinterator = list::const_iterator(current_ptr, o_list);
        if(current_ptr != nullptr){
            current_ptr = current_ptr->prev;
        } else {
            current_ptr = o_list->tail;
        }
        return cinterator;
    }
    list::const_iterator::reference list::const_iterator::operator*() const{
        return current_ptr->val;
        
    }
    list::const_iterator::pointer list::const_iterator::operator->() const{
        return &current_ptr->val;
    }
    bool list::const_iterator::operator==(const list::const_iterator& rhs)const{
        return current_ptr == rhs.current_ptr && o_list == rhs.o_list;
    }
    bool list::const_iterator::operator!=(const list::const_iterator& rhs)const{
        return !(current_ptr == rhs.current_ptr && o_list == rhs.o_list);
    }
    
    ///dynamic iterator
    list::iterator::iterator(node* ptr, const list* gen){
        current_ptr = ptr;
        o_list = gen;
    }
    list::iterator list::begin(){
        list::iterator iterator = list::iterator(head, this);
        return iterator;
    }
    list::iterator list::end(){
        list::iterator iterator = list::iterator(nullptr, this);
        return iterator;
    }
    bool list::iterator::operator==(const list::iterator& rhs)const{
        return current_ptr == rhs.current_ptr && o_list == rhs.o_list;
    }
    bool list::iterator::operator!=(const list::iterator& rhs)const{
        return current_ptr != rhs.current_ptr || o_list != rhs.o_list;
    }
    list::iterator& list::iterator::operator++(){ //prefix
        if (current_ptr != nullptr) {
            current_ptr = current_ptr->next;
        }else{
            current_ptr = nullptr;
        }
        return *this;
    }
    list::iterator& list::iterator::operator--(){ //prefix
        if (current_ptr != nullptr) {
            current_ptr = current_ptr->prev;
        }else{
            current_ptr = o_list->tail;
        }
        return *this;
    }
    list::iterator list::iterator::operator++(int){ // postfix
        list::iterator iterator = list::iterator(current_ptr, o_list);
        current_ptr = current_ptr->next;
        return iterator;
        
    }
    list::iterator list::iterator::operator--(int){
        list::iterator iterator = list::iterator(current_ptr, o_list);
        if(current_ptr != nullptr){
            current_ptr = current_ptr->prev;
        } else {
             current_ptr = o_list->tail;
        }
        return iterator;
    }
    list::iterator::operator const_iterator() const {
        return list::const_iterator(current_ptr, o_list);
    }
    list::iterator::reference list::iterator::operator*() const{
        return current_ptr->val;
    }
    list::iterator::pointer list::iterator::operator->() const{
        return &current_ptr->val;
    }
    /// LIST THINGIES
    list::list(const list& rhs){
        for (auto element : rhs ) {
            push_back(element);
        }
    }
    list& list::operator=(const list& rhs){
        if(&rhs == this) return *this;
        while(num_elements != 0){
            pop_back();
        }
        for(auto x : rhs){
            push_back(x);
        }
        return *this;
        
    }
    list::list(list&& rhs){
        head=rhs.head;
        tail = rhs.tail;
        num_elements = rhs.num_elements;
        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.num_elements = 0;
    }
    list& list::operator=(list&& rhs){
        while(num_elements != 0){
            pop_back();
        }
        head = std::move(rhs.head);
        tail = std::move(rhs.tail);
        num_elements = rhs.num_elements;
        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.num_elements = 0;
        return *this;
    }
    
    list::~list(){
        while (num_elements != 0) {
            pop_back();
        }
    }
    
    list::list(const std::vector<double>& vec){
        
        std::vector<double>::const_iterator it = vec.begin();
        
        while (it != vec.end()) {
            list::push_back(*it);
            *it++;
        }
    }
    
    void list::push_back(double elem){
        node* newNode = new node;
        newNode->val = elem;
        newNode->next = nullptr;
        
        //empty list head == nullptr & tail == nullptr
        if (num_elements == 0) {
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        num_elements++;
    }
    
    void list::pop_back(){
        
        if (num_elements == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            num_elements--;
            return;
        }

        node* toDelete = tail;
        tail = tail->prev;


        delete toDelete;
        tail->next = nullptr;
        num_elements--;
        
    }
    
    double& list::back(){
        if (tail != nullptr) {
            double& val = tail->val;
            return val;
        }else{
           
            return tail->val;
        }
        
    }
    
    double const& list::back() const{
        
        if (tail != nullptr) {
            const double& val = tail->val;
            return val;
        }else{
            ///TODO: test if this OK
            return tail->val;
        }
    }
    void list::push_front(double elem){
        node* newNode = new node;
        newNode->val = elem;
        newNode->prev = nullptr;
        
        if (num_elements == 0) {
            head = newNode;
            tail = newNode;
        }else{
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        num_elements++;
    }
    void list::pop_front(){
        node* toDelete = head;
        head = head->next;
        //list je prazdny
        if (head == nullptr) {
            tail = nullptr;
        }
        delete toDelete;
        num_elements--;
    }
    
    double& list::front(){
        if (tail != nullptr) {
            double& val = head->val;
            return val;
        }else{
            return head->val;
        }
    }
    double const& list::front() const{
        if (tail != nullptr) {
            const double& val = tail->val;
            return val;
        }else{
            return tail->val;
        }
    }
    void list::reverse(){
        if (num_elements < 2) {
            return;
        }
        node* l = head;
        node* r = tail;
        while(head != tail){
            double tmp = r->val;
            r->val = l->val;
            l->val = tmp;
            r = r->prev;
            if(r == l) break;
            l = l->next;
        }
    }
    
    size_t list::size() const{
        size_t t = num_elements;
        return t;
    }
    
    bool list::empty() const{
        return num_elements == 0;
    }
    
    void list::remove(double value){
        const_iterator cit = begin();
        while (cit != end()) {
            if (cit.current_ptr->val == value) {
                node* toDelete = cit.current_ptr;
                node* prev = cit.current_ptr->prev;
                node* next = cit.current_ptr->next;
                //removing head
                if (prev == nullptr && next == nullptr) {
                    cit++;
                    delete toDelete;
                    num_elements--;
                }
                // removing tail
                else if(next == nullptr){
                    prev->next = cit.current_ptr->next;
                    tail = prev;
                    cit++;
                    delete toDelete;
                    num_elements--;
                
                }
                else if(prev == nullptr){
                    next->prev = cit.current_ptr->prev;
                    head = next;
                    cit++;
                    delete toDelete;
                    num_elements--;
                }
                //middle of the list
                else{
                    prev->next = cit.current_ptr->next;
                    next->prev = cit.current_ptr->prev;
                    cit++;
                    delete toDelete;
                    num_elements--;
                }
            }else{
                cit++;
            }
            
        }
    }
    
    void list::swap(list& rhs){
        ;
    }
    
    bool list::operator==(const list& rhs) const{
        if (size() != rhs.size()) {
            return false;
        }

        list::const_iterator it = begin();
        for (auto element : rhs) {
            if (element != *it) {
                return false;
            }
            it++;
        }
        return true;
    }
    
    bool list::operator<(const list& rhs) const{
        list::const_iterator it1 = begin();
        list::const_iterator it2 = rhs.begin();
        if(size() == 0 && rhs.size() == 0){
            return false;
        }
        if(size() == 0 && rhs.size() > 0){
            return true;
        }
        
        for ( ; (it1 != end()) && (it2 != rhs.end()); ++it1, ++it2 ) {
            if (*it1 < *it2) return true;
            if (*it2 < *it1) return false;
        }
        
        return (it1 == end()) && (it2 != rhs.end());

    }
    
    std::pair<list, list> list::split(const_iterator place){
        
        list l1 = list();
        list l2 = list();
        
        list::const_iterator cit = begin();
        
        while (cit != place) {
            l1.push_back(*cit);
            cit++;
            pop_front();
        }
        //l1 je asi plnej
        while (cit != end()) {
            l2.push_back(*cit);
            cit++;
            pop_front();
        }
        return std::pair<list, list> (l1,l2);
    }
    
    void list::merge(list& rhs){
        list ret = list();
        while (!empty() || !rhs.empty()) {
            // one of the lists is empty, therefore we can just merge the rest
            if (head == nullptr && rhs.head != nullptr) {
                while (!rhs.empty()) {
                    ret.push_back(rhs.head->val);
                    rhs.pop_front();
                }
                break;
            }
            if (head != nullptr && rhs.head == nullptr) {
                while (!empty()) {
                    ret.push_back(head->val);
                    pop_front();
                }
                break;
            }

            if (head->val <= (rhs.head)->val) {
                ret.push_back(head->val);
                pop_front();
            }else{
                ret.push_back(rhs.head->val);
                rhs.pop_front();
            }
        }
        *this = ret;
    }
    
    void list::sort(){
        
        if(num_elements < 2)
        {
            return;
        }
        //this is for list spliting
        const_iterator cit = begin();
        std::advance(cit, (int) num_elements/2);
        std::pair<list, list> lists = split(cit);
        //getting actual parts
        list lhs = std::get<0>(lists);
        list rhs = std::get<1>(lists);
        
        lhs.sort();
        rhs.sort();
        
        lhs.merge(rhs);
        
        *this = lhs;
    }
    bool operator!=(const list& lhs, const list& rhs){
        return lhs == rhs ? false : true;
    }
    
    bool operator>(const list& lhs, const list& rhs){
        list::const_iterator it1 = lhs.begin();
        list::const_iterator it2 = rhs.begin();
        if(lhs.size() == 0 && rhs.size() == 0){
            return false;
        }
        if(lhs.size() == 0 && rhs.size() > 0){
            return false;
        }
        
        for ( ; (it1 != lhs.end()) && (it2 != rhs.end()); ++it1, ++it2 ) {
            if (*it1 < *it2) return false;
            if (*it2 < *it1) return true;
        }
        
        return (it1 != lhs.end()) && (it2 == rhs.end());
    }
    
    bool operator<=(const list& lhs, const list& rhs){
        return !(lhs > rhs);
    }
    
    bool operator>=(const list& lhs, const list& rhs){
        return !(lhs < rhs);
    }
    
    
    void swap(list& lhs, list& rhs){
    }

}// end namespace pjc
