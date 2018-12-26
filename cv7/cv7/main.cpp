//
//  main.cpp
//  cv7
//
//  Created by Yevgen Ponomarenko on 11/13/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

///TEMPLATE

#include <iostream>

template<typename T>
void print(T a, T b){
    std::cout << a <<"  T" << b << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    print<int>(30.00,30);
    return 0;
}
