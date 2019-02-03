//
//  Autocorrector.cpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#include "Autocorrector.hpp"
#include <fstream>
#include <algorithm>
#include <list>
#include <math.h>
#include <exception>

autocorrector::autocorrector(){
    m_dictionary = loadWords(pathToDictionary);
}
autocorrector::autocorrector(const std::string& path){
    try {
        m_dictionary = loadWords(path);
    } catch (std::exception ex) {
        std::cerr << "provided file cannot be opened, intialising autocorrector with default dictionary" << std::endl;
        m_dictionary = loadWords(pathToDictionary);
    }
}
autocorrector::autocorrector(const std::map<char,std::set<std::string>>& letterToWordMap){
    m_dictionary = std::move(letterToWordMap);
}
autocorrector autocorrector::operator=(autocorrector rhs){
    this->m_dictionary = rhs.m_dictionary;
    return *this;
}
const float autocorrector::getDistance2(const std::string & originalWord, const std::string & compareTo) const {

    
        if (originalWord.size() > compareTo.size()) {
            return getDistance2(compareTo, originalWord);
        }
    
        const size_t min_size = originalWord.size(), max_size = compareTo.size();
        std::vector<size_t> lev_dist(min_size + 1);
        
        for (size_t i = 0; i <= min_size; ++i) {
            lev_dist[i] = i;
        }
        
        for (size_t j = 1; j <= max_size; ++j) {
            size_t previous_diagonal = lev_dist[0], previous_diagonal_save;
            ++lev_dist[0];
            
            for (size_t i = 1; i <= min_size; ++i) {
                previous_diagonal_save = lev_dist[i];
                if (originalWord[i - 1] == compareTo[j - 1]) {
                    lev_dist[i] = previous_diagonal;
                } else {
                    lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
                }
                previous_diagonal = previous_diagonal_save;
            }
        }
        
        return lev_dist[min_size];
    }


const size_t autocorrector::getDistance(const std::string & originalWord, const std::string & compareTo) const{
    const size_t m(originalWord.length());
    const size_t n(compareTo.length());
    
    if( m==0 ) return n;
    if( n==0 ) return m;
    
    size_t *costs = new size_t[n + 1];
    
    for(size_t k = 0; k <= n; k++) costs[k] = k;
    
    size_t i = 0;
    for (std::string::const_iterator it1 = originalWord.begin(); it1 != originalWord.end(); ++it1, ++i)
    {
        costs[0] = i+1;
        size_t corner = i;
        
        size_t j = 0;
        for (std::string::const_iterator it2 = compareTo.begin(); it2 != compareTo.end(); ++it2, ++j)
        {
            size_t upper = costs[j+1];
            if(*it1 == *it2)
            {
                costs[j + 1] = corner;
            }
            else
            {
                size_t t(upper < corner ? upper : corner);
                costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
            }
            
            corner = upper;
        }
    }
    
    size_t result = costs[n];
    delete [] costs;
    
    return result;
}
/**
 * Building dictionary char to set, keys of the map are letters of alphabet;
 * value of the key is set of words (to prevent duplicites).
 *
 */

std::map<char,std::set<std::string>> autocorrector::loadWords(const std::string path){
    std::map<char,std::set<std::string>> letterToWordMap;
    std::string line;
    std::fstream file(path, std::fstream::in | std::fstream::out);
    if(!file){
        throw std::invalid_argument("file could not be opened");
    }
    while (std::getline(file, line)) {
        auto it = letterToWordMap.find(line[0]);
        //if keys is in the dictionary
        if (it == letterToWordMap.end()) {
            std::set<std::string> newSet;
            newSet.insert(line);
            letterToWordMap.insert(std::pair<char,std::set<std::string>>(line[0], newSet));
        }else{
            (*it).second.insert(line);
        }
        
    }
    file.close();
    return letterToWordMap;
}

autocorrector::vectorOfWords autocorrector::correctWord(std::string &word){
    char firstLetter = word[0];
    auto it = m_dictionary.find(firstLetter);
    std::vector<std::string> possibleWords;
    if (it == m_dictionary.end()) {
        //throw exeption
        ;
    }else{
        //iterating through the set of words
        auto it2 = (*it).second.begin();
        size_t maxDistance = 3;
        
        while (it2 != (*it).second.end()) {
            size_t actualDistance = getDistance(word, *it2);
            if (actualDistance == 0){
                possibleWords.clear();
                return possibleWords;
            }
            else if (actualDistance < maxDistance) {
                maxDistance = actualDistance;
                possibleWords.clear();
                possibleWords.push_back(*it2);
            }
            else if(actualDistance == maxDistance){
                possibleWords.push_back(*it2);
            }
            it2++;
        }
    }
    return possibleWords;
}
autocorrector::vectorOfWords autocorrector::correctWord2(std::string &word){
    
    
    char firstLetter = word[0];
    auto it = m_dictionary.find(firstLetter);
    std::vector<std::string> possibleWords;
    if (it == m_dictionary.end()) {
        //throw exeption
        ;
    }else{
        //iterating through the set of words
        auto it2 = (*it).second.begin();
        float maxDistance = word.length();

        while (it2 != (*it).second.end()) {
            float actualDistance = getDistance2(word, *it2);
            if (actualDistance == 0){
                possibleWords.clear();
                return possibleWords;
            }
            else if (actualDistance < maxDistance) {
                maxDistance = actualDistance;
                possibleWords.clear();
                possibleWords.push_back(*it2);
            }
            else if(actualDistance == maxDistance){
                possibleWords.push_back(*it2);
            }
            it2++;
        }
    }
    return possibleWords;
}

autocorrector::vectorOfWords autocorrector::correctWord3(std::string &word){
    char firstLetter = word[0];
    auto it = m_dictionary.find(firstLetter);
    std::vector<std::string> possibleWords;
    if (it == m_dictionary.end()) {
        //throw exeption
        ;
    }else{
        //iterating through the set of words
        auto it2 = (*it).second.begin();
        size_t maxDistance = word.length();
        
        while (it2 != (*it).second.end()) {
            size_t actualDistance = getDistance3(word, *it2);
            if (actualDistance == 0){
                possibleWords.clear();
                return possibleWords;
            }
            else if (actualDistance < maxDistance) {
                maxDistance = actualDistance;
                possibleWords.clear();
                possibleWords.push_back(*it2);
            }
            else if(actualDistance == maxDistance){
                possibleWords.push_back(*it2);
            }
            it2++;
        }
    }
    return possibleWords;
}

void autocorrector::correctWordParallel(std::string &word, std::promise<vectorOfWords> promise){
    char firstLetter = word[0];
    auto it = m_dictionary.find(firstLetter);
    std::vector<std::string> possibleWords;
    if (it == m_dictionary.end()) {
        //throw exeption
        ;
    }else{
        //iterating through the set of words
        auto it2 = (*it).second.begin();
        size_t maxDistance = 3;
        
        while (it2 != (*it).second.end()) {
            size_t actualDistance = getDistance(word, *it2);
            if (actualDistance == 0){
                possibleWords.clear();
                break;
            }
            else if (actualDistance < maxDistance) {
                maxDistance = actualDistance;
                possibleWords.clear();
                possibleWords.push_back(*it2);
            }
            else if(actualDistance == maxDistance){
                possibleWords.push_back(*it2);
            }
            it2++;
        }
    }
    promise.set_value(possibleWords);
}

const size_t autocorrector::getDistance3( const std::string & s1, const std::string &s2){
    
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));
    
    d[0][0] = 0;
    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;
    
    for(unsigned int i = 1; i <= len1; ++i)
        for(unsigned int j = 1; j <= len2; ++j)
            // note that std::min({arg1, arg2, arg3}) works only in C++11,
            // for C++98 use std::min(std::min(arg1, arg2), arg3)
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
    return d[len1][len2];

}
