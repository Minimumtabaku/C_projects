//
//  atomic_counter.cpp
//  cv12
//
//  Created by Yevgen Ponomarenko on 12/18/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#include "atomic_counter.hpp"

void atomic_counter::increment(){
    std::unique_lock<std::mutex> l(mutex);
    counter++;
}
void atomic_counter::decrement(){
    std::unique_lock<std::mutex> l(mutex);
    counter--;
}
int atomic_counter::value(){
    std::unique_lock<std::mutex> l(mutex);
    return counter;
}
bool atomic_counter::increment_if_less_than(int num){
    std::unique_lock<std::mutex> l(mutex);
    if (counter < num) {
        counter++;
        return true;
    }else{
        return false;
    }
    
}
