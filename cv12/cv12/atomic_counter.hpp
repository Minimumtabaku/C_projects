//
//  atomic_counter.hpp
//  cv12
//
//  Created by Yevgen Ponomarenko on 12/18/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#ifndef atomic_counter_hpp
#define atomic_counter_hpp

#include <iostream>
#include <mutex>
class atomic_counter{
private:
    int counter;
    std::mutex mutex;
    
public:
    void increment();
    void decrement();
    int value();
    bool increment_if_less_than(int);
    
};

#endif /* atomic_counter_hpp */
