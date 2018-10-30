//
//  part2.hpp
//  4cv
//
//  Created by Yevgen Ponomarenko on 10/23/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#ifndef part2_hpp
#define part2_hpp

#include <iostream>

#endif /* part2_hpp */

class Complex{
public:
    Complex();
    Complex(int, int);
    Complex add( Complex const& first,  Complex const& second);
    Complex diff(Complex const& first , Complex const& second);
    double abs(void);
    void print(void) const;
    
    int real;
    int imaginary;
    double absValue;
private:
    
};
