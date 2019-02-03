//
//  Autocorrector.cpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko.



#include "Autocorrector.hpp"
#include <fstream>
#include <algorithm>
#include <math.h>
#include <exception>
///constructors
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
/**
 * Algorithm to find Levenstein distance used in prallel computation, the rusl is the same as in the standrad one,
 * but this implementation is not optimised for the single threaded approach.
 *
 * @param originalWord : word to be compared
 * @param compareTo : word to be compared with
 * @return size_t : distance bwtween words
 */
const size_t autocorrector::getDistanceParallel(const std::string & originalWord, const std::string & compareTo) const {

    
        if (originalWord.size() > compareTo.size()) {
            return getDistanceParallel(compareTo, originalWord);
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

/**
 * Slightly optimised algorithm for finding Levenstein distance between words.
 * Rougly 1-2ms faster than the one used in parallel approach.
 *
 * @param originalWord : word to be compared
 * @param compareTo : word to be compared with
 * @return size_t : distance bwtween words
 */
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
 * @param path : path to the file with words of the dictionary
 * @return dictionary{first lettter of the word : vector of words}
 */
std::map<char,std::set<std::string>> autocorrector::loadWords(const std::string& path){
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
/**
 *Finds the closest words in the dictionary.
 *
 *@param word : word to be corrected
 *@return vector of words : possible corrections
 */
autocorrector::vectorOfWords autocorrector::correctWord(std::string &word){
    char firstLetter = word[0];
    auto it = m_dictionary.find(firstLetter);
    std::vector<std::string> possibleWords;
    if (it == m_dictionary.end()) {
        throw std::invalid_argument("provided word not in the same alphabet");
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

/**
 *Finds the closest words in the dictionary and save them in the provided promise. This function is used in the parallel execution.
 *
 *@param word : word to be corrected
 */
void autocorrector::correctWordParallel(std::string &word, std::promise<vectorOfWords> promise){
    char firstLetter = word[0];
    auto it = m_dictionary.find(firstLetter);
    std::vector<std::string> possibleWords;
    if (it == m_dictionary.end()) {
       throw std::invalid_argument("provided word not in the same alphabet");
    }else{
        //iterating through the set of words
        auto it2 = (*it).second.begin();
        size_t maxDistance = 3;
        
        while (it2 != (*it).second.end()) {
            size_t actualDistance = getDistanceParallel(word, *it2);
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
