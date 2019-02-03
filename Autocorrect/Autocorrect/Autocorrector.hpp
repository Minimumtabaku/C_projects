//
//  Autocorrector.hpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko.
//

#ifndef Autocorrector_hpp
#define Autocorrector_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <future>


class autocorrector{
public:
    using vectorOfWords = std::vector<std::string>;
    autocorrector();
    autocorrector(const std::string& path);
    autocorrector(const std::map<char,std::set<std::string>>& letterToWordMap);
    autocorrector operator=(autocorrector);
    const size_t getDistance(const std::string&, const std::string&) const;
    const size_t getDistanceParallel(const std::string&, const std::string&) const;
    vectorOfWords correctWord(std::string& word);
    void correctWordParallel(std::string& word, std::promise<vectorOfWords> promise);
private:
    const std::string pathToDictionary = "engmix.txt";
    std::map<char, std::set<std::string>> m_dictionary;
    std::map<char, std::set<std::string>> loadWords(const std::string& pathToFile);
    
};

#endif /* Autocorrector_hpp */

