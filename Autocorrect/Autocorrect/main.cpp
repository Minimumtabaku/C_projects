//
//  main.cpp
//  Autocorrect
//
//  Created by Yevgen Ponomarenko on 1/23/19.
//  Copyright © 2019 Yevgen Ponomarenko. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <stack>
#include "Autocorrector.hpp"
#include "termcolor.hpp"
#include "utils.hpp"

int main(int argc, const char * argv[]) {
    autocorrector ac = autocorrector();
    
    std::string test = "Car w:as mo.ving dir,ectly into the voi, nevtheles;s I ws dru'nk";
    std::string w;
    std::stringstream ss(test);
    std::vector<std::string> words;
    std::vector<std::string> wordsPunc;
    std::vector<std::stack<std::string>> results;
    
    while (ss >> w) {
        wordsPunc.push_back(w);
        utils::removePunctuation(w);
        words.push_back(w);
    }
    std::cout << test << std::endl;
    
    for (auto word : words) {
        auto ret = ac.correctWord(word);
        std::stack<std::string> temp{ {ret.begin(),ret.end()} } ;
        results.push_back(temp);
    }
    int count = 0;
    int counter = 0;
    while (true) {
        if (count == results.size()) {
            break;
        }else{
            count = 0;
        }
        
        for (auto it = results.begin(); it != results.end() ; it++, counter++) {
        
            if ((*it).size() == 0) {
                std::cout << utils::makeWhitespaces(wordsPunc[counter].length() + 1) ;
                count++;
            }else{
                std::cout << (*it).top() << " ";
                (*it).pop();
            }
            //last element
            
            if (std::next(it) == results.end()) {
                std::cout << std::endl;
            }
            
        }
    }
   
    
    
    
//
    return 0;
}
