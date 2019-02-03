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
    /**
     * Used to store relation between same character in different positions
     * c1 and c2 in the input strings.
     */
    struct offset{
        const int char1;
        const int char2;
        bool trans;
        
        offset(const int c1, const int c2, const bool trans) : char1(c1) , char2(c2), trans(trans) {};
        
    };
    
public:
    using vectorOfWords = std::vector<std::string>;
    autocorrector();
    autocorrector(const std::string& path);
    autocorrector(const std::map<char,std::set<std::string>>& letterToWordMap);
    autocorrector operator=(autocorrector);
    const size_t getDistance(const std::string&, const std::string&) const;
    const float getDistance2(const std::string&, const std::string&) const;
    const  size_t getDistance3(const std::string&,const std::string&) ;
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

