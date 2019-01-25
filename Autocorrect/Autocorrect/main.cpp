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
    
    std::string test = "man";
    for (auto x : ac.correct(test)) {
        std::cout << x << std::endl;
    }
    return 0;
}
