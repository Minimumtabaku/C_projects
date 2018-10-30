//
//  time.cpp
//  5cv
//
//  Created by Yevgen Ponomarenko on 10/30/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#include "time.hpp"

Time::Time(unsigned int h, unsigned int m){
    hours = h + m/60;
    minutes = m % 60;
    
}

void Time::addHour(unsigned int h){
    hours += h;
}
void Time::addMinute(unsigned int m){
    unsigned int tmp = minutes + m;
    minutes = tmp%60;
    hours += tmp/60;
}

Time Time::operator+(const Time &x) const{
    return Time( hours + x.hours, minutes + x.minutes);
}

Time& Time::operator+=(const Time &x) {
    addHour(x.hours);
    addMinute(x.minutes);
    return *this;
}

bool Time::operator==(const Time &x) const{
    return (minutes == x.minutes) && (hours == x.hours) ;
}
unsigned int Time::operator[](const int a) const{
    if( a == 0){
        return minutes;
    }else{
        return hours;
    }
}

std::ostream& operator<<(std::ostream &os, const Time &x){
    return os << minutes <<" minutes" << hours << "hours" << std::endl;
}

Time Time::operator++(const Time &x) const{
    return Time( hours + x.hours, minutes + x.minutes);
}
