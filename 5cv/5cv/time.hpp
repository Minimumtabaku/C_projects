//
//  time.hpp
//  5cv
//
//  Created by Yevgen Ponomarenko on 10/30/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#ifndef time_hpp
#define time_hpp

#include <iostream>

#endif /* time_hpp */

class Time{
public:
    Time(unsigned int h,unsigned int m);
    Time operator+(const Time &x) const;
    Time& operator+=(const Time &x);
    bool operator==(const Time &x)const;
    unsigned operator[](int a) const;
    //Time operator<<(const Time &x)const;
    friend std::ostream& operator<< (std::ostream &os, const Time &x);
   // Time operator++(const Time &x)const;
    unsigned int hours;
    unsigned int minutes;
    
private:
    
    void addHour(unsigned int);
    void addMinute(unsigned int);
};


