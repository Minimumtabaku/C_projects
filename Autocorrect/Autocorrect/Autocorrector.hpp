//
//  Autocorrector.hpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#ifndef Autocorrector_hpp
#define Autocorrector_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>



class autocorrector{
public:
    autocorrector();
    const size_t getDistance(const std::string&, const std::string&) const;
    std::vector<std::string> correct(std::string& word);
private:
    const std::string pathToDictionary = "engmix.txt";
    std::map<char, std::set<std::string>> m_dictionary;
    std::map<char, std::set<std::string>> loadWords(std::string pathToFile);
    
};

#endif /* Autocorrector_hpp */

