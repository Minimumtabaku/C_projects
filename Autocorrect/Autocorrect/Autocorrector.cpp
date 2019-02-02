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

autocorrector::autocorrector(){
    m_dictionary = loadWords(pathToDictionary);
}

const size_t autocorrector::getDistance2(const std::string & originalWord, const std::string & compareTo) const {
    if (originalWord.length() == 0) {
        return compareTo.length();
    }
    
    if (compareTo.length() == 0) {
        return originalWord.length();
    }
    
    size_t l1 = originalWord.length();
    size_t l2 = compareTo.length();
    
    int c1 = 0;  //cursor for string 1
    int c2 = 0;  //cursor for string 2
    int lcss = 0;  //largest common subsequence
    int local_cs = 0; //local common substring
    int trans = 0;  //number of transpositions ('ab' vs 'ba')
    
    // offset pair array, for computing the transpositions
    std::list<offset> offset_arr;
    
    while ((c1 < l1) && (c2 < l2)) {
        if (originalWord[c1] == compareTo[c2]) {
            local_cs++;
            bool is_trans = false;
            // see if current match is a transposition
            auto it = offset_arr.begin();
            while (it != offset_arr.end()) {
                
                if (c1 <= (*it).char1 || c2 <= (*it).char2) {
                    // when two matches cross, the one considered a
                    // transposition is the one with the largest difference
                    // in offsets
                    is_trans = abs(c2 - c1) >= abs((*it).char2 - (*it).char1);
                    if (is_trans) {
                        
                        trans++;
                    } else {
                        if (!(*it).trans) {
                            (*it).trans = true;
                            trans++;
                        }
                    }
                    
                    break;
                } else {
                    if (c1 > (*it).char2 && c2 > (*it).char1) {
                        offset_arr.erase(it);
                    } else {
                        it++;
                    }
                }
            }
            offset_arr.push_back({offset(c1, c2, is_trans)});
            
        } else {
            
            // originalWord.charAt(c1) != compareTo.charAt(c2)
            lcss += local_cs;
            local_cs = 0;
            if (c1 != c2) {
                //using min allows the computation of transpositions
                c1 = std::min(c1, c2);
                c2 = c1;
            }
            
            // if matching characters are found, remove 1 from both cursors
            // (they get incremented at the end of the loop)
            // so that we can have only one code block handling matches
            for (int i = 0; i < 10 && (c1 + i < l1 || c2 + i < l2); i++) {
                
                if ((c1 + i < l1) && (originalWord[c1 + i] == compareTo[c2])) {
                    c1 += i - 1;
                    c2--;
                    break;
                }
                
                if ((c2 + i < l2) && (originalWord[c1] == compareTo[c2 + i])) {
                    c1--;
                    c2 += i - 1;
                    break;
                }
            }
        }
        c1++;
        c2++;
        // this covers the case where the last match is on the last token
        // in list, so that it can compute transpositions correctly
        if ((c1 >= l1) || (c2 >= l2)) {
            lcss += local_cs;
            local_cs = 0;
            c1 = std::min(c1, c2);
            c2 = c1;
        }
    }
    lcss += local_cs;
    // add the cost of transpositions to the final result
    return round(std::max(l1, l2) - lcss + trans);

//    const size_t _maxOffset = originalWord.length();
//    const size_t m(originalWord.length());
//    const size_t n(compareTo.length());
//
//    if( m==0 ) return n;
//    if( n==0 ) return m;
//
//    int c = 0;
//    int offset1 = 0;
//    int offset2 = 0;
//    int lcs = 0;
//    while ((c + offset1 < originalWord.length())
//           && (c + offset2 < compareTo.length()))
//    {
//        if (originalWord[c + offset1] == compareTo[c + offset2]) lcs++;
//        else
//        {
//            offset1 = 0;
//            offset2 = 0;
//            if (originalWord[c] == compareTo[c])
//            {
//                c++;
//                continue;
//            }
//            for (int i = 1; i < _maxOffset; i++)
//            {
//                if ((c + i < originalWord.length())
//                    && (originalWord[c + i] == compareTo[c]))
//                {
//                    offset1 = i;
//                    break;
//                }
//                if ((c + i < compareTo.length())
//                    && (originalWord[c] == compareTo[c + i]))
//                {
//                    offset2 = i;
//                    break;
//                }
//            }
//        }
//        c++;
//    }
//    return (originalWord.length() + compareTo.length())/2 - lcs;
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
    std::fstream file(path);
    
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
        size_t maxDistance = word.length();

        while (it2 != (*it).second.end()) {
            size_t actualDistance = getDistance2(word, *it2);
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
            size_t actualDistance = getDistance2(word, *it2);
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

size_t autocorrector::getDistance3( std::string & a, const std::string &b){
//    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
//    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    
    std::vector<int> dist((a.length() + 1) * (b.length() + 1));
    
    for (int i = 0; i < (int)a.length() + 1; ++i)
    {
        dist[(b.length() + 1) * i] = i;
    }
    for (int j = 0; j < (int)b.length() + 1; ++j)
    {
        dist[j] = j;
    }
    
    for (int i = 1; i < (int)a.length() + 1; ++i)
    {
        for (int j = 1; j < (int)b.length() + 1; ++j)
        {
            int suppr_dist = dist[(b.length() + 1) * (i - 1) + j] + 1;
            int insert_dist = dist[(b.length() + 1) * i + j - 1] + 1;
            int subs_dist = dist[(b.length() + 1) * (i - 1) + j - 1];
            if (a[i - 1] != b[j - 1]) // word indexes are implemented differently.
            {
                subs_dist += 1;
            }
            int val = std::min(suppr_dist, std::min(insert_dist, subs_dist));
            if (((i >= 2) && (j >= 2)) && ((a[i - 1] == b[j - 2]) && (a[i - 2] == b[j - 1])))
            {
                val = std::min(dist[(b.length() + 1) * (i - 2) + j - 2] + 1, val);
            }
            dist[(b.length() + 1) * i + j] = val;
        }
    }
    return (dist[(a.length() + 1) * (b.length() + 1) - 1]);

}
