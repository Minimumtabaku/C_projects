//
//  part2.cpp
//  4cv
//
//  Created by Yevgen Ponomarenko on 10/23/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#include "part2.hpp"
#include <cmath>

Complex::Complex(){
    real = 1;
    imaginary = -1;
}

Complex::Complex(int r, int i) : real(r),imaginary(i){
   
}

void Complex::print() const{
    std::cout << "real part" << real << ", imaginary part" << imaginary << std::endl;
}

Complex Complex::add(Complex const& first, Complex const& second){
    return Complex(real=first.real + second.real, imaginary = second.imaginary + second.imaginary);
}

Complex Complex::diff(Complex const& first, Complex const& second){
    return Complex(real=first.real - second.real, imaginary = second.imaginary - second.imaginary);
}
