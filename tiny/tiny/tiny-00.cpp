//
//  tiny-00.cpp
//  tiny
//
//  Created by Yevgen Ponomarenko on 10/10/18.
//  Copyright © 2018 Yevgen Ponomarenko. All rights reserved.
//

#include "tiny-00.hpp"
#include <iostream>
#include <limits>
#include <iomanip>


void write_stats(std::vector<double> const& data, std::ostream& out){
    std::vector<double>::const_iterator it;
    double min =  std::numeric_limits<double>::max(), max = - std::numeric_limits<double>::max() , sum = 0;
    
    for (it = data.begin(); it != data.end(); ++it) {
        
        if (min > *it) {
            min = *it;
        }
         if(max < *it){
            max = *it;
        }
        sum += *it;
    }
    out << "min: " << std::fixed << std::setprecision(2) <<  min << "\n"
    << "max: "  << max << "\n"
    << "mean: " << sum/data.size() << "\n";
}

