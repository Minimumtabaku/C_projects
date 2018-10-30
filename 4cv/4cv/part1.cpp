//
//  part1.cpp
//  4cv
//
//  Created by Yevgen Ponomarenko on 10/23/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#include "part1.hpp"


void MyClass::printf(){
    std::cout << "hi bitch " << x << std::endl;
}

//to za dvouteckou je konstruktor, fakt divny
MyClass::MyClass() : x(20){
    
}
