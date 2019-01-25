//
//  main.cpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "Autocorrector.hpp"
int main(int argc, const char * argv[]) {
    autocorrector ac = autocorrector();
    
    std::string test = "Bostin";
    auto ret = ac.correct(test);
    if (ret.size() == 0) {
        std::cout << "\033nothing to see here, move along\033" << std::endl;
    }else{
        for (auto x : ac.correct(test)) {
            std::cout << x << std::endl;
        }
    }
   
    return 0;
}
