//
//  main.cpp
//  5cv
//
//  Created by Yevgen Ponomarenko on 10/30/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#include <iostream>
#include "time.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Time a = Time(10,10);
    Time b = Time(20,20);
    
    Time c = a + b;
    std::cout << c.minutes << " minutes " << c.hours << " hours " << std::endl;
    
    return 0;
}
