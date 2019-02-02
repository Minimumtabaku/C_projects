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
#include <future>


class autocorrector{
    
public:
    using vectorOfWords = std::vector<std::string>;
    autocorrector();
    const size_t getDistance(const std::string&, const std::string&) const;
    const size_t getDistance2(const std::string&, const std::string&) const;
     size_t getDistance3(std::string&, const std::string&) ;
    vectorOfWords correctWord(std::string& word);
    vectorOfWords correctWord2(std::string& word);
    vectorOfWords correctWord3(std::string& word);
    void correctWordParallel(std::string& word, std::promise<vectorOfWords> promise);
    static void removePunctuation(std::string& word);
private:
    const std::string pathToDictionary = "engmix.txt";
     std::map<char, std::set<std::string>> m_dictionary;
     std::map<char, std::set<std::string>> loadWords(std::string pathToFile);
    
};

#endif /* Autocorrector_hpp */

